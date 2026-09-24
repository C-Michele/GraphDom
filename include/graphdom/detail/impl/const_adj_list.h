/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_CONST_ADJ_LIST_IMPL_H
#define GRAPHDOM_CONST_ADJ_LIST_IMPL_H

#include "../../graph.h"
#include "../../set_graph.h"
#include "../base_adj_list.h"
#include "../const_adj_list.h"

template <typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(const const_adj_list& other) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >( other ),
adj_list_owner_graph_is_a_set_graph( other.adj_list_owner_graph_is_a_set_graph ) {}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(const typename graph<VertexType>::adj_list& other) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >(
    other.adj_list_owner_graph_pointer, //TODO: remove this line
    other.adj_list_owner_graph_edges_type,
    other.adj_list_common_begin_point_vertex_container_pointer,
    other.adj_list_edges_type_selection
),
adj_list_owner_graph_is_a_set_graph( other.adj_list_owner_graph_is_a_set_graph ) {}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(const typename multiset_graph<VertexType>::adj_list& other) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >(
    other.adj_list_owner_graph_pointer, //TODO: remove this line
    other.adj_list_owner_graph_edges_type,
    other.adj_list_common_begin_point_vertex_container_pointer,
    other.adj_list_edges_type_selection
),
adj_list_owner_graph_is_a_set_graph( false ) {}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::const_adj_list::begin() const {
    if ( adj_list_owner_graph_is_a_set_graph ) {
        return graphdom::graph<VertexType>::adj_list_const_iterator( this->template internal_begin<const graphdom::graph<VertexType>::vertex_container*>() );
    }
    return graphdom::graph<VertexType>::adj_list_const_iterator( this->template internal_begin<graphdom::graph<VertexType>::vertex_container*>() );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::const_adj_list::end() const {
    if ( adj_list_owner_graph_is_a_set_graph ) {
        return graphdom::graph<VertexType>::adj_list_const_iterator( this->template internal_end<const graphdom::graph<VertexType>::vertex_container*>() );
    }
    return graphdom::graph<VertexType>::adj_list_const_iterator( this->template internal_end<graphdom::graph<VertexType>::vertex_container*>() );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::const_adj_list::cbegin() const {
    return begin();
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::const_adj_list::cend() const {
    return end();
}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(
    const graphdom::graph<VertexType>* const adj_list_owner_graph_pointer,
    const typename graphdom::graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
    const typename graphdom::graph<VertexType>::vertex_container* const adj_list_common_begin_point_vertex_container_pointer,
    const typename graphdom::graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection ) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >(
    adj_list_owner_graph_pointer, //TODO: remove this line
    adj_list_owner_graph_edges_type,
    adj_list_common_begin_point_vertex_container_pointer,
    adj_list_edges_type_selection
),
adj_list_owner_graph_is_a_set_graph( dynamic_cast< const graphdom::set_graph<VertexType>* >( adj_list_owner_graph_pointer ) != nullptr ) {}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(
    const bool adj_list_owner_graph_is_a_set_graph,
    const typename graphdom::graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
    const typename graphdom::graph<VertexType>::vertex_container* const adj_list_common_begin_point_vertex_container_pointer,
    const typename graphdom::graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection ) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >(
    adj_list_owner_graph_edges_type,
    adj_list_common_begin_point_vertex_container_pointer,
    adj_list_edges_type_selection
),
adj_list_owner_graph_is_a_set_graph( adj_list_owner_graph_is_a_set_graph ) {}

#endif //GRAPHDOM_CONST_ADJ_LIST_IMPL_H
