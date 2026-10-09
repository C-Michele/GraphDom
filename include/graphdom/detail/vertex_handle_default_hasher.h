/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_HANDLE_DEFAULT_HASHER_H
#define GRAPHDOM_VERTEX_HANDLE_DEFAULT_HASHER_H

#include "graphdom/graph.h"

template <typename VertexType>
class graphdom::graph<VertexType>::vertex_handle_default_hasher {
    public:
        std::size_t operator()(const void* to_hash) const;
};

#include "impl/vertex_handle_default_hasher.h"

#endif //GRAPHDOM_VERTEX_HANDLE_DEFAULT_HASHER_H