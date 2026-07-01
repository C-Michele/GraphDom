#ifndef GRAPHDOM_EDGE_ENDPOINT_H
#define GRAPHDOM_EDGE_ENDPOINT_H

#include "../graph.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::edge_endpoint {
        public:
            edge_endpoint() = delete;
            edge_endpoint(const edge_endpoint&) = delete;
            edge_endpoint(edge_endpoint&&) = delete;
            explicit edge_endpoint(const VertexContainerPointerType ptr) : vertex_container_ptr(ptr){}

            ~edge_endpoint() = default;

            VertexContainerPointerType vertex_container_ptr;
    };
}

#endif //GRAPHDOM_EDGE_ENDPOINT_H