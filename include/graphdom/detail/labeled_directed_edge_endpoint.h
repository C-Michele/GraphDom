#ifndef GRAPHDOM_LABELED_DIRECT_EDGE_ENDPOINT_H
#define GRAPHDOM_LABELED_DIRECT_EDGE_ENDPOINT_H

#include "../graph.h"
#include "edge_endpoint.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType, typename EdgeLabelType>
    class graph<VertexType>::labeled_directed_edge_endpoint final : public edge_endpoint<VertexContainerPointerType> {
        public:
            labeled_directed_edge_endpoint() = delete;
            labeled_directed_edge_endpoint(const labeled_directed_edge_endpoint&) = delete;
            labeled_directed_edge_endpoint(labeled_directed_edge_endpoint&&) = delete;
            labeled_directed_edge_endpoint(const VertexContainerPointerType ptr, const EdgeLabelType& edge) :
                edge_endpoint<VertexContainerPointerType>(ptr),
                edge_label(edge) {}
            labeled_directed_edge_endpoint(const VertexContainerPointerType ptr, EdgeLabelType&& edge) :
                edge_endpoint<VertexContainerPointerType>(ptr),
                edge_label(std::move(edge)) {}

            ~labeled_directed_edge_endpoint() = default;

            mutable EdgeLabelType edge_label;
    };
}

#endif //GRAPHDOM_LABELED_DIRECT_EDGE_ENDPOINT_H