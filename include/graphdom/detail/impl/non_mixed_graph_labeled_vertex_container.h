/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_NON_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_IMPL_H
#define GRAPHDOM_NON_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_IMPL_H

#include "../../graph.h"
#include "../non_mixed_graph_vertex_container.h"
#include "../non_mixed_graph_labeled_vertex_container.h"

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
non_mixed_graph_labeled_vertex_container(const VertexType& v, const VertexLabelType& vl) :
    non_mixed_graph_vertex_container<VertexContainerPointerType>(v),
    vertex_label(vl) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
non_mixed_graph_labeled_vertex_container(const VertexType& v, VertexLabelType&& vl) :
    non_mixed_graph_vertex_container<VertexContainerPointerType>(v),
    vertex_label(std::move(vl)) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
non_mixed_graph_labeled_vertex_container(VertexType&& v, const VertexLabelType& vl) :
    non_mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
    vertex_label(vl) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
non_mixed_graph_labeled_vertex_container(VertexType&& v, VertexLabelType&& vl) :
    non_mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
    vertex_label(std::move(vl)) {}

#endif //GRAPHDOM_NON_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_IMPL_H
