/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_SET_GRAPH_IMPL_H
#define GRAPHDOM_SET_GRAPH_IMPL_H

#include "../set_graph.h"

template<typename VertexType>
typename graphdom::set_graph<VertexType>::adj_set::const_iterator
graphdom::set_graph<VertexType>::get_inner_iterator(
const typename graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    return std::get< typename graph<VertexType>::template adj_set<const typename graph<VertexType>::vertex_container*>::iterator >( const_edge_itr.inner_iterator );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::set_graph<VertexType>::adj_list_iterator_factory(
    const graphdom::set_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const non_mixed_graph_vertex_container* const edge_begin_point_ptr,
    const graphdom::edge_type edge_set_vertex_graph_owner_edges_type,
    const typename adj_set::iterator inner_itr) {
    return typename graphdom::graph<VertexType>::adj_list_iterator(
        edge_set_vertex_graph_owner_ptr,
        ( edge_set_vertex_graph_owner_edges_type == edge_type::undirected ) ?
            graph<VertexType>::graph_edges_type::undirected :
            graph<VertexType>::graph_edges_type::directed,
        edge_begin_point_ptr,
        graph<VertexType>::edges_type_selection_type::none,
        edge_set_vertex_graph_owner_edges_type,
        inner_itr
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::set_graph<VertexType>::adj_list_iterator_factory(
    const graphdom::set_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const mixed_graph_vertex_container* const edge_begin_point_ptr,
    const typename adj_set::iterator inner_itr,
    const graphdom::edge_type inner_itr_edge_type,
    const bool inner_itr_is_limited_by_edge_type) {
    return typename graphdom::graph<VertexType>::adj_list_iterator(
        edge_set_vertex_graph_owner_ptr,
        graph<VertexType>::graph_edges_type::mixed,
        edge_begin_point_ptr,
        inner_itr_is_limited_by_edge_type ?
            ( ( inner_itr_edge_type == graphdom::edge_type::undirected ) ?
                graph<VertexType>::edges_type_selection_type::undirected_edges :
                graph<VertexType>::edges_type_selection_type::directed_edges ) :
            graph<VertexType>::edges_type_selection_type::none,
        inner_itr_edge_type,
        inner_itr
    );
}

#endif //GRAPHDOM_SET_GRAPH_IMPL_H
