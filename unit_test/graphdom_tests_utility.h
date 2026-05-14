#ifndef GRAPHDOM_GRAPHDOM_TESTS_UTILITY_H
#define GRAPHDOM_GRAPHDOM_TESTS_UTILITY_H

#include <functional>
#include <utility>

namespace graphdom_tests {
    template <typename T>
    class heap_value {
        public:
            heap_value() : pointer(nullptr) {}
            heap_value(const T& value) : pointer( new T( value ) ) {}
            heap_value(T&& value) : pointer( new T( std::move(value) ) ) {}
            heap_value(const heap_value<T>& other) : pointer( new T( *(other.pointer) ) ) {}
            heap_value(heap_value<T>&& other) noexcept : pointer( other.pointer ) {
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
        static constexpr std::less<T> less_functor = std::less<T>();
        static constexpr std::equal_to<T> equality_functor = std::equal_to<T>();

        T* pointer;
    };
}

#endif //GRAPHDOM_GRAPHDOM_TESTS_UTILITY_H