/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_GRAPH_IMPL_H
#define GRAPHDOM_GRAPH_IMPL_H

#include "../graph.h"

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::vertex_handle_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    return graphdom::graph<VertexType>::vertex_handle(
        graph_ptr,
        ( non_mixed_graph_type == graphdom::edge_type::undirected ) ? graphdom::graph<VertexType>::graph_edges_type::undirected : graphdom::graph<VertexType>::graph_edges_type::directed,
        &vertex_container_reference
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::vertex_handle_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    return graphdom::graph<VertexType>::vertex_handle(
        graph_ptr,
        graphdom::graph<VertexType>::graph_edges_type::mixed,
        &vertex_container_reference
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::vertex_const_handle_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    return graphdom::graph<VertexType>::vertex_const_handle(
        graph_ptr,
        ( non_mixed_graph_type == graphdom::edge_type::undirected ) ? graphdom::graph<VertexType>::graph_edges_type::undirected : graphdom::graph<VertexType>::graph_edges_type::directed,
        &vertex_container_reference
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::vertex_const_handle_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    return graphdom::graph<VertexType>::vertex_const_handle(
        graph_ptr,
        graphdom::graph<VertexType>::graph_edges_type::mixed,
        &vertex_container_reference
    );
}

template<typename VertexType>
const graphdom::graph<VertexType>* graphdom::graph<VertexType>::get_owner_graph(
    const graphdom::graph<VertexType>::vertex_const_handle& ptr) {
    return ptr.vertex_container_owner_graph_pointer;
}

template<typename VertexType>
const typename graphdom::graph<VertexType>::vertex_container* graphdom::graph<VertexType>::get_vertex_container(
    const graphdom::graph<VertexType>::vertex_const_handle& ptr) {
    return ptr.vertex_container_pointer;
}

template<typename VertexType>
const graphdom::graph<VertexType>* graphdom::graph<VertexType>::get_owner_graph(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    return const_edge_itr.iterator_owner_graph;
}

template<typename VertexType>
const typename graphdom::graph<VertexType>::vertex_container* graphdom::graph<VertexType>::get_begin_point(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    return const_edge_itr.edge_begin_point_vertex_container;
}

#endif //GRAPHDOM_GRAPH_IMPL_H