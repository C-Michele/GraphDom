/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_EDGE_ENDPOINT_H
#define GRAPHDOM_EDGE_ENDPOINT_H

#include <type_traits>

#include "../graph.h"
#include "vertex_container.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::edge_endpoint {
        public:
            static_assert(
                std::is_same< VertexContainerPointerType , graphdom::graph<VertexType>::vertex_container* >::value ||
                std::is_same< VertexContainerPointerType , const graphdom::graph<VertexType>::vertex_container* >::value
                ,
                "The typename 'VertexContainerPointerType' of 'graphdom::graph<VertexType>::edge_endpoint<VertexContainerPointerType>' class must be a pointer to graphdom::graph<VertexType>::vertex_container"
            );

            edge_endpoint() = delete;
            edge_endpoint(const edge_endpoint&) = delete;
            edge_endpoint(edge_endpoint&&) = delete;
            explicit edge_endpoint(VertexContainerPointerType ptr);

            ~edge_endpoint() = default;

            VertexContainerPointerType vertex_container_ptr;
    };
}

#include "impl/edge_endpoint.h"

#endif //GRAPHDOM_EDGE_ENDPOINT_H