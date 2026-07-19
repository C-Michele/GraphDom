/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_EDGE_ENDPOINT_IMPL_H
#define GRAPHDOM_EDGE_ENDPOINT_IMPL_H

#include "../../graph.h"
#include "../edge_endpoint.h"

template <typename VertexType>
template <typename VertexContainerPointerType>
graphdom::graph<VertexType>::edge_endpoint<VertexContainerPointerType>::edge_endpoint(const VertexContainerPointerType ptr) : vertex_container_ptr(ptr) {}

#endif //GRAPHDOM_EDGE_ENDPOINT_IMPL_H