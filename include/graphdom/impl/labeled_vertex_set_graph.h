/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_LABELED_VERTEX_SET_GRAPH_IMPL_H
#define GRAPHDOM_LABELED_VERTEX_SET_GRAPH_IMPL_H

#include "../labeled_vertex_set_graph.h"

template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_set_graph() : vertices_labeller() {}

template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_set_graph(const VertexLabellerType& vl) : vertices_labeller(vl) {}

template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_set_graph(VertexLabellerType&& vl) : vertices_labeller(std::move(vl)) {}

template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
constexpr const VertexLabellerType& graphdom::labeled_vertex_set_graph<VertexType, VertexLabelType, VertexLabellerType>::get_vertices_labeller() const {
    return vertices_labeller;
}

template <typename VertexType, typename VertexLabelType, typename VertexLabellerType>
std::pair<typename graphdom::graph<VertexType>::vertex_handle,bool> graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(const VertexType& v_core) {
    return insert_vertex(v_core,vertices_labeller(v_core));
}

template <typename VertexType, typename VertexLabelType, typename VertexLabellerType>
std::pair<typename graphdom::graph<VertexType>::vertex_handle,bool> graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(VertexType&& v_core) {
    return insert_vertex(std::move(v_core),vertices_labeller(v_core));
}

#endif //GRAPHDOM_LABELED_VERTEX_SET_GRAPH_IMPL_H