#ifndef GRAPHDOM_NON_MIXED_GRAPH_VERTEX_CONTAINER_H
#define GRAPHDOM_NON_MIXED_GRAPH_VERTEX_CONTAINER_H

#include "../graph.h"
#include "vertex_container.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::non_mixed_graph_vertex_container : public vertex_container {
        public:
            non_mixed_graph_vertex_container() = delete;
            non_mixed_graph_vertex_container(const non_mixed_graph_vertex_container&) = delete;
            non_mixed_graph_vertex_container(non_mixed_graph_vertex_container&&) = delete;
            explicit non_mixed_graph_vertex_container(const VertexType& v);
            explicit non_mixed_graph_vertex_container(VertexType&& v);

            ~non_mixed_graph_vertex_container() = default;

            mutable adj_set<VertexContainerPointerType> adj;
    };
}

#include "impl/non_mixed_graph_vertex_container.h"

#endif //GRAPHDOM_NON_MIXED_GRAPH_VERTEX_CONTAINER_H