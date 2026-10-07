/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_HANDLE_HASH_H
#define GRAPHDOM_VERTEX_HANDLE_HASH_H

#include <cstddef>

#include "../graph.h"
#include "vertex_handle.h"
#include "vertex_const_handle.h"
#include "../multiset_graph.h"
#include "multiset_graph_vertex_handle.h"

namespace graphdom {
    template <typename VertexType>
    class graph<VertexType>::vertex_handle_hash {
        public:
            constexpr std::size_t operator()(const graphdom::graph<VertexType>::vertex_handle& to_hash) const;
            constexpr std::size_t operator()(const graphdom::graph<VertexType>::vertex_const_handle& to_hash) const;
            constexpr std::size_t operator()(const typename graphdom::multiset_graph<VertexType>::vertex_handle& to_hash) const;
    };
}

#include "impl/vertex_handle_hash.h"

#endif //GRAPHDOM_VERTEX_HANDLE_HASH_H