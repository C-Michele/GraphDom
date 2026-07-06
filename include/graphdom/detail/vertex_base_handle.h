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
                std::is_same< VertexContainerPointerType , graphdom::graph<VertexType>::vertex_container* >::value ||
                std::is_same< VertexContainerPointerType , const graphdom::graph<VertexType>::vertex_container* >::value
                ,
                "The typename 'VertexContainerPointerType' of 'graphdom::graph<VertexType>::vertex_base_handle<VertexContainerPointerType>' class must be a pointer to graphdom::graph<VertexType>::vertex_container"
            );

            ~vertex_base_handle() = default;

            [[nodiscard]] constexpr auto* operator->() const;
            [[nodiscard]] constexpr auto& operator*() const;

            template<typename>
            friend class graph<VertexType>::vertex_base_handle;
            template<typename K>
            [[nodiscard]] constexpr bool operator==(const vertex_base_handle<K>& other_handle) const;
            template<typename K>
            [[nodiscard]] constexpr bool operator!=(const vertex_base_handle<K>& other_handle) const;

        protected:
            vertex_base_handle();
            vertex_base_handle(
                const graph<VertexType>* vertex_container_owner_ptr,
                graph_edges_type vertex_container_owner_et,
                VertexContainerPointerType vertex_container_ptr
            );

            const graph<VertexType>* vertex_container_owner_pointer;
            graph_edges_type vertex_container_owner_edges_type;
            VertexContainerPointerType vertex_container_pointer;
    };
}

#include "impl/vertex_base_handle.h"

#endif //GRAPHDOM_VERTEX_BASE_HANDLE_H