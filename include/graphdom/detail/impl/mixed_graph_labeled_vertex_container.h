/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_IMPL_H
#define GRAPHDOM_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_IMPL_H

#include "../../graph.h"
#include "../mixed_graph_vertex_container.h"
#include "../mixed_graph_labeled_vertex_container.h"

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
mixed_graph_labeled_vertex_container(const VertexType& v, const VertexLabelType& vl) :
    mixed_graph_vertex_container<VertexContainerPointerType>(v),
    vertex_label(vl) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
mixed_graph_labeled_vertex_container(const VertexType& v, VertexLabelType&& vl) :
    mixed_graph_vertex_container<VertexContainerPointerType>(v),
    vertex_label(std::move(vl)) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
mixed_graph_labeled_vertex_container(VertexType&& v, const VertexLabelType& vl) :
    mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
    vertex_label(vl) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename VertexLabelType>
graphdom::graph<VertexType>::mixed_graph_labeled_vertex_container<VertexContainerPointerType,VertexLabelType>::
mixed_graph_labeled_vertex_container(VertexType&& v, VertexLabelType&& vl) :
    mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
    vertex_label(std::move(vl)) {}

#endif //GRAPHDOM_MIXED_GRAPH_LABELED_VERTEX_CONTAINER_IMPL_H