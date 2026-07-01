#ifndef GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_H
#define GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_H

#include "../graph.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::custom_edge_endpoint_less {
        public:
            bool constexpr operator()(const edge_endpoint<VertexContainerPointerType>* const left, const edge_endpoint<VertexContainerPointerType>* const right) const {
                return less_functor( left->vertex_container_ptr , right->vertex_container_ptr );
            }

            using is_transparent = void;

            bool constexpr operator()(const edge_endpoint<VertexContainerPointerType>* const left, const vertex_container* const right) const {
                return less_functor( left->vertex_container_ptr , right );
            }

            bool constexpr operator()(const vertex_container* const left, const edge_endpoint<VertexContainerPointerType>* const right) const {
                return less_functor( left , right->vertex_container_ptr );
            }

            static constexpr std::less<const vertex_container*> less_functor = std::less<const vertex_container*>();
    };
}

#endif //GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_H