#ifndef GRAPHDOM_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_H
#define GRAPHDOM_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_H

#include "../graph.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType, typename VertexLabelType>
    class graph<VertexType>::mixed_graph_labeled_vertex_container final : public mixed_graph_vertex_container<VertexContainerPointerType> {
        public:
            mixed_graph_labeled_vertex_container() = delete;
            mixed_graph_labeled_vertex_container(const mixed_graph_labeled_vertex_container&) = delete;
            mixed_graph_labeled_vertex_container(mixed_graph_labeled_vertex_container&&) = delete;
            mixed_graph_labeled_vertex_container(const VertexType& v, const VertexLabelType& vl) :
                mixed_graph_vertex_container<VertexContainerPointerType>(v),
                vertex_label(vl) {}
            mixed_graph_labeled_vertex_container(const VertexType& v, VertexLabelType&& vl) :
                mixed_graph_vertex_container<VertexContainerPointerType>(v),
                vertex_label(std::move(vl)) {}
            mixed_graph_labeled_vertex_container(VertexType&& v, const VertexLabelType& vl) :
                mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
                vertex_label(vl) {}
            mixed_graph_labeled_vertex_container(VertexType&& v, VertexLabelType&& vl) :
                mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
                vertex_label(std::move(vl)) {}

            ~mixed_graph_labeled_vertex_container() = default;

            mutable VertexLabelType vertex_label;
    };
}

#endif //GRAPHDOM_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_H