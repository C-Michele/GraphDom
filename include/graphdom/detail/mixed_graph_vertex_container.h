#ifndef GRAPHDOM_MIXED_GRAPH_VERTEX_CONTAINER_H
#define GRAPHDOM_MIXED_GRAPH_VERTEX_CONTAINER_H

#include "../graph.h"
#include "vertex_container.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::mixed_graph_vertex_container : public vertex_container {
        public:
            mixed_graph_vertex_container() = delete;
            mixed_graph_vertex_container(const mixed_graph_vertex_container&) = delete;
            mixed_graph_vertex_container(mixed_graph_vertex_container&&) = delete;
            explicit mixed_graph_vertex_container(const VertexType& v);
            explicit mixed_graph_vertex_container(VertexType&& v);

            ~mixed_graph_vertex_container() = default;

            mutable adj_set<VertexContainerPointerType> undirected_adj;
            mutable adj_set<VertexContainerPointerType> directed_adj;
    };
}

#include "impl/mixed_graph_vertex_container.h"

#endif //GRAPHDOM_MIXED_GRAPH_VERTEX_CONTAINER_H