#ifndef GRAPHDOM_TESTS_UTILITY_H
#define GRAPHDOM_TESTS_UTILITY_H

#include <functional>
#include <utility>
#include <vector>

namespace graphdom_tests {
    template <typename T>
    class heap_value {
        public:
            enum constructor_type : std::uint8_t {
                default_constructor,
                value_constructor,
                value_move_constructor,
                copy_constructor,
                move_constructor
            };

            heap_value() :
                pointer(nullptr),
                constructors_chain(get_vector_with_new_element_in_tail(std::vector<constructor_type>(), default_constructor)) {}
            heap_value(const T& value) :
                pointer( new T( value ) ),
                constructors_chain(get_vector_with_new_element_in_tail(std::vector<constructor_type>(), value_constructor)) {}
            heap_value(T&& value) :
                pointer( new T( std::move(value) ) ),
                constructors_chain(get_vector_with_new_element_in_tail(std::vector<constructor_type>(), value_move_constructor)) {}
            heap_value(const heap_value<T>& other) : pointer( new T( *(other.pointer) ) ),
                constructors_chain(get_vector_with_new_element_in_tail(other.constructors_chain, copy_constructor)) {}
            heap_value(heap_value<T>&& other) noexcept :
                pointer( other.pointer ),
                constructors_chain(get_vector_with_new_element_in_tail(other.constructors_chain, move_constructor)) {
                other.pointer = nullptr;
            }

            ~heap_value<T>() {
                delete pointer;
            }

            constexpr bool operator<(const heap_value<T>& other) const {
                return less_functor(*pointer,*(other.pointer));
            }
            constexpr bool operator>(const heap_value<T>& other) const {
                return less_functor(*(other.pointer),*pointer);
            }
            constexpr bool operator==(const heap_value<T>& other) const {
                return equality_functor(*pointer,*(other.pointer));
            }
            constexpr const T* get_as_pointer() const {
                return pointer;
            }
            constexpr const T& get_as_reference() const {
                return *pointer;
            }
            constexpr const std::vector<constructor_type>& get_constructors_chain() const {
                return constructors_chain;
            }

            constexpr heap_value<T>& operator=(const heap_value<T>& other) {
                if ( this != &other ) {
                    *pointer = *( other.pointer );
                }
                return *this;
            }
            constexpr heap_value<T>& operator=(heap_value<T>&& other) noexcept {
                if ( this != &other ) {
                    delete pointer;
                    pointer = other.pointer;
                    other.pointer = nullptr;
                }
                return *this;
            }
            constexpr T* get_as_pointer() {
                return pointer;
            }
            constexpr T& get_as_reference() {
                return *pointer;
            }
    private:
        template<typename U>
        static std::vector<U> get_vector_with_new_element_in_tail(
            const std::vector<U>& vector,
            const U& new_element ) {
            std::vector<U> new_vector(vector);
            new_vector.emplace_back( new_element );
            new_vector.shrink_to_fit();
            return new_vector;
        }
        template<typename U>
        static std::vector<U> get_vector_with_new_element_in_tail(
            std::vector<U>&& vector,
            const U& new_element ) {
            std::vector<U> new_vector(std::move(vector));
            new_vector.emplace_back( new_element );
            new_vector.shrink_to_fit();
            return new_vector;
        }

        static constexpr std::less<T> less_functor = std::less<T>();
        static constexpr std::equal_to<T> equality_functor = std::equal_to<T>();

        T* pointer;
        const std::vector<constructor_type> constructors_chain;
    };
}

#endif //GRAPHDOM_TESTS_UTILITY_H