/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_LABELED_EDGE_MIXED_GRAPH_IMPL_H
#define GRAPHDOM_LABELED_EDGE_MIXED_GRAPH_IMPL_H

#include "../labeled_edge_mixed_graph.h"

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
graphdom::labeled_edge_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_mixed_graph() : edges_labeller() {}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
graphdom::labeled_edge_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_mixed_graph(const EdgeLabellerType& el) : edges_labeller(el) {}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
graphdom::labeled_edge_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_mixed_graph(EdgeLabellerType&& el) : edges_labeller(std::move(el)) {}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
constexpr const EdgeLabellerType& graphdom::labeled_edge_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::get_edges_labeller() const {
    return edges_labeller;
}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
void graphdom::labeled_edge_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& first_endpoint,
    const typename graph<VertexType>::vertex_const_handle& second_endpoint,
    edge_type et) {
    insert_edge(first_endpoint,second_endpoint,et,edges_labeller(first_endpoint,second_endpoint,et));
}

#endif //GRAPHDOM_LABELED_EDGE_MIXED_GRAPH_IMPL_H