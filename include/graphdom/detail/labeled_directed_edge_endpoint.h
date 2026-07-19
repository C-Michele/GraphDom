/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_LABELED_DIRECTED_EDGE_ENDPOINT_H
#define GRAPHDOM_LABELED_DIRECTED_EDGE_ENDPOINT_H

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
            labeled_directed_edge_endpoint(VertexContainerPointerType ptr, const EdgeLabelType& edge);
            labeled_directed_edge_endpoint(VertexContainerPointerType ptr, EdgeLabelType&& edge);

            ~labeled_directed_edge_endpoint() = default;

            mutable EdgeLabelType edge_label;
    };
}

#include "impl/labeled_directed_edge_endpoint.h"

#endif //GRAPHDOM_LABELED_DIRECTED_EDGE_ENDPOINT_H