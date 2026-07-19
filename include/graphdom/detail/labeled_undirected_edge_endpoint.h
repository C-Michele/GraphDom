/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_LABELED_UNDIRECTED_EDGE_ENDPOINT_H
#define GRAPHDOM_LABELED_UNDIRECTED_EDGE_ENDPOINT_H

#include "../graph.h"
#include "edge_endpoint.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType, typename EdgeLabelType>
    class graph<VertexType>::labeled_undirected_edge_endpoint final : public edge_endpoint<VertexContainerPointerType> {
        public:
            labeled_undirected_edge_endpoint() = delete;
            labeled_undirected_edge_endpoint(const labeled_undirected_edge_endpoint&) = delete;
            labeled_undirected_edge_endpoint(labeled_undirected_edge_endpoint&&) = delete;
            labeled_undirected_edge_endpoint(VertexContainerPointerType ptr, const EdgeLabelType& edge);
            labeled_undirected_edge_endpoint(VertexContainerPointerType ptr, EdgeLabelType&& edge);
            labeled_undirected_edge_endpoint(VertexContainerPointerType ptr, const std::shared_ptr<EdgeLabelType>& existent_edge_label_ptr);

            ~labeled_undirected_edge_endpoint() = default;

            mutable std::shared_ptr<EdgeLabelType> edge_label_ptr;
    };
}

#include "impl/labeled_undirected_edge_endpoint.h"

#endif //GRAPHDOM_LABELED_UNDIRECTED_EDGE_ENDPOINT_H