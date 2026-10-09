/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_HANDLE_DEFAULT_HASHER_IMPL_H
#define GRAPHDOM_VERTEX_HANDLE_DEFAULT_HASHER_IMPL_H

#include "../vertex_handle_default_hasher.h"
#include "../../utility.h"

template <typename VertexType>
std::size_t graphdom::graph<VertexType>::vertex_handle_default_hasher::operator()(const void* const to_hash) const {
    return graphdom::utility::hash_pointer(to_hash);
}

#endif //GRAPHDOM_VERTEX_HANDLE_DEFAULT_HASHER_IMPL_H