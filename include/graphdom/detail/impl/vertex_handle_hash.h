/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_HANDLE_HASH_IMPL_H
#define GRAPHDOM_VERTEX_HANDLE_HASH_IMPL_H

#include <cstddef>

#include "../vertex_handle_hash.h"
#include "../../utility.h"

template <typename VertexType>
constexpr std::size_t graphdom::graph<VertexType>::vertex_handle_hash::operator()(const graphdom::graph<VertexType>::vertex_handle& to_hash) const {
    return graphdom::utility::hash_pointer( to_hash.vertex_container_pointer );
}

template <typename VertexType>
constexpr std::size_t graphdom::graph<VertexType>::vertex_handle_hash::operator()(const graphdom::graph<VertexType>::vertex_const_handle& to_hash) const {
    return graphdom::utility::hash_pointer( to_hash.vertex_container_pointer );
}

template <typename VertexType>
constexpr std::size_t graphdom::graph<VertexType>::vertex_handle_hash::operator()(const typename graphdom::multiset_graph<VertexType>::vertex_handle& to_hash) const {
    return graphdom::utility::hash_pointer( to_hash.vertex_container_pointer );
}

#endif //GRAPHDOM_VERTEX_HANDLE_HASH_IMPL_H