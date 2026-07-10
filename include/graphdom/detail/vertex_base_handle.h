#ifndef GRAPHDOM_VERTEX_BASE_HANDLE_H
#define GRAPHDOM_VERTEX_BASE_HANDLE_H

#include <type_traits>

#include "../graph.h"
#include "vertex_container.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::vertex_base_handle {
        public:
            static_assert(
                std::is_same< VertexContainerPointerType , graph<VertexType>::vertex_container* >::value ||
                std::is_same< VertexContainerPointerType , const graph<VertexType>::vertex_container* >::value
                ,
                "The typename 'VertexContainerPointerType' of 'graphdom::graph<VertexType>::vertex_base_handle<VertexContainerPointerType>' class must be a pointer to graphdom::graph<VertexType>::vertex_container"
            );

            vertex_base_handle() = delete;

            ~vertex_base_handle() = default;

            /**
             * If `*this` is valid then the expression `(*this)->...` is equal to `( &( *(*this) ) )->...`.<br>
             * If `*this` is invalid then the expression `(*this)->...` will cause undefined behavior.
             *
             * @return `&( *(*this) )`
             * @par Complexity
             * Constant.
             */
            [[nodiscard]] constexpr auto* operator->() const;
            /**
             * If `*this` is valid then `*(*this)` returns a reference to the core of the vertex identified by `*this`.<br>
             * If `*this` is invalid then `*(*this)` will cause undefined behavior.
             *
             * @return A reference to the core of the vertex identified by `*this`.
             * @par Complexity
             * Constant.
             */
            [[nodiscard]] constexpr auto& operator*() const;
            /**
             * Returns `true` if `*this` and @p other_handle are valid and identify the same vertex of the same graph.<br>
             * Returns `false` if `*this` and @p other_handle are valid, identify different vertices, and the vertices identified by `*this` and @p other_handle belong to the same graph.<br>
             * In other cases, `*this == other_handle` will cause undefined behavior.
             *
             * @param other_handle The object to compare with `*this`.
             * @return The comparison result.
             * @par Complexity
             * Constant.
             */
            template<typename K>
            [[nodiscard]] constexpr bool operator==(const vertex_base_handle<K>& other_handle) const;
            /**
             * `*this != other_handle` has the same behavior of `!( *this == other_handle)`.
             *
             * @param other_handle The object to compare with `*this`.
             * @return The same result of `!( *this == other_handle)`.
             * @par Complexity
             * Constant.
             */
            template<typename K>
            [[nodiscard]] constexpr bool operator!=(const vertex_base_handle<K>& other_handle) const;

            template<typename>
            friend class graph<VertexType>::vertex_base_handle;
        protected:
            vertex_base_handle(const vertex_base_handle&) = default;
            vertex_base_handle(
                const graph<VertexType>* vertex_container_owner_ptr,
                graph_edges_type vertex_container_owner_et,
                VertexContainerPointerType vertex_container_ptr
            );

            const graph<VertexType>* vertex_container_owner_graph_pointer;
            graph_edges_type vertex_container_owner_graph_edges_type;
            VertexContainerPointerType vertex_container_pointer;
    };
}

#include "impl/vertex_base_handle.h"

#endif //GRAPHDOM_VERTEX_BASE_HANDLE_H