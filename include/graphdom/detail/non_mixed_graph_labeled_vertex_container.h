#ifndef GRAPHDOM_NON_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_H
#define GRAPHDOM_NON_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_H

#include "../graph.h"
#include "non_mixed_graph_vertex_container.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType, typename VertexLabelType>
    class graph<VertexType>::non_mixed_graph_labeled_vertex_container final : public non_mixed_graph_vertex_container<VertexContainerPointerType> {
        public:
            non_mixed_graph_labeled_vertex_container() = delete;
            non_mixed_graph_labeled_vertex_container(const non_mixed_graph_labeled_vertex_container&) = delete;
            non_mixed_graph_labeled_vertex_container(non_mixed_graph_labeled_vertex_container&&) = delete;
            non_mixed_graph_labeled_vertex_container(const VertexType& v, const VertexLabelType& vl);
            non_mixed_graph_labeled_vertex_container(const VertexType& v, VertexLabelType&& vl);
            non_mixed_graph_labeled_vertex_container(VertexType&& v, const VertexLabelType& vl);
            non_mixed_graph_labeled_vertex_container(VertexType&& v, VertexLabelType&& vl);

            ~non_mixed_graph_labeled_vertex_container() = default;

            mutable VertexLabelType vertex_label;
    };
}

#include "impl/non_mixed_graph_labeled_vertex_container.h"

#endif //GRAPHDOM_NON_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_H