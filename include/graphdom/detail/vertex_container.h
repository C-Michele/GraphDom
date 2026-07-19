/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_CONTAINER_H
#define GRAPHDOM_VERTEX_CONTAINER_H

#include "../graph.h"

namespace graphdom {
    template <typename VertexType>
    class graph<VertexType>::vertex_container {
        public:
            vertex_container() = delete;
            vertex_container(const vertex_container&) = delete;
            vertex_container(vertex_container&&) = delete;
            explicit vertex_container(const VertexType& v);
            explicit vertex_container(VertexType&& v);

            ~vertex_container() = default;

            VertexType vertex;
    };
}

#include "impl/vertex_container.h"

#endif //GRAPHDOM_VERTEX_CONTAINER_H