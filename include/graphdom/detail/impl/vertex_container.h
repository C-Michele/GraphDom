/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_CONTAINER_IMPL_H
#define GRAPHDOM_VERTEX_CONTAINER_IMPL_H

#include "../../graph.h"
#include "../vertex_container.h"

template<typename VertexType>
graphdom::graph<VertexType>::vertex_container::vertex_container(const VertexType& v) : vertex(v) {}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_container::vertex_container(VertexType&& v) : vertex( std::move(v) ) {}

#endif //GRAPHDOM_VERTEX_CONTAINER_IMPL_H