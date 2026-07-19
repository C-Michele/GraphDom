/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_IMPL_H
#define GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_IMPL_H

#include "../../graph.h"
#include "../adj_list_base_iterator.h"
#include "../adj_list_iterator.h"
#include "../../multiset_graph.h"
#include "../multiset_graph_adj_list_iterator.h"

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list_iterator::adj_list_iterator(const adj_list_iterator& other) :
graphdom::graph<VertexType>::template adj_list_base_iterator< typename graph<VertexType>::vertex_container*  >( other ){}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list_iterator::adj_list_iterator(const typename graph<VertexType>::adj_list_iterator& other) :
graphdom::graph<VertexType>::template adj_list_base_iterator< typename graph<VertexType>::vertex_container*  >(
    other.iterator_owner_graph,
    other.iterator_owner_graph_edges_type,
    static_cast< typename graph<VertexType>::vertex_container* >( nullptr ),
    other.edges_type_restriction,
    other.inner_iterator_edge_current_type
) {
    if ( dynamic_cast< const graphdom::multiset_graph<VertexType>* >( this->iterator_owner_graph ) == nullptr ) {
        throw std::runtime_error("Convertion error"); //TODO: write a better message
    }
    this->edge_begin_point_vertex_container = const_cast< typename graph<VertexType>::vertex_container* >( other.edge_begin_point_vertex_container );
    this->inner_iterator = other.inner_iterator;
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle graphdom::multiset_graph<VertexType>::adj_list_iterator::operator->() const {
    return *this;
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle graphdom::multiset_graph<VertexType>::adj_list_iterator::operator*() const {
    return graphdom::multiset_graph<VertexType>::vertex_handle(
        this->iterator_owner_graph,
        this->iterator_owner_graph_edges_type,
        ( *( std::get< typename graphdom::graph<VertexType>::template adj_set<typename graphdom::graph<VertexType>::vertex_container*>::iterator >( this->inner_iterator ) ) )->vertex_container_ptr
    );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator& graphdom::multiset_graph<VertexType>::adj_list_iterator::operator=(const adj_list_iterator& other) {
    if ( this != &other ) {
        this->iterator_owner_graph = other.iterator_owner_graph;
        this->iterator_owner_graph_edges_type = other.iterator_owner_graph_edges_type;
        this->edge_begin_point_vertex_container = other.edge_begin_point_vertex_container;
        this->edges_type_restriction = other.edges_type_restriction;
        this->inner_iterator_edge_current_type = other.inner_iterator_edge_current_type;
        this->inner_iterator = other.inner_iterator;
    }
    return *this;
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator& graphdom::multiset_graph<VertexType>::adj_list_iterator::operator++() {
    this->internal_single_increment();
    return *this;
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator graphdom::multiset_graph<VertexType>::adj_list_iterator::operator++(int) {
    auto to_return = *this;
    ++(*this);
    return to_return;
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list_iterator::adj_list_iterator(const typename graph<VertexType>::template adj_list_base_iterator<typename graph<VertexType>::vertex_container*>& other) :
graphdom::graph<VertexType>::template adj_list_base_iterator< typename graph<VertexType>::vertex_container*  >( other ){}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graph<VertexType>* const iterator_owner_pointer,
    const typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    typename graph<VertexType>::vertex_container* const edge_begin_point_vertex_container,
    const typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type) :
graphdom::graph<VertexType>::template adj_list_base_iterator< typename graph<VertexType>::vertex_container* >(
    iterator_owner_pointer,
    iterator_owner_graph_edges_type,
    edge_begin_point_vertex_container,
    edges_type_restriction,
    inner_iterator_edge_current_type
) {}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graph<VertexType> *iterator_owner_pointer,
    const typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    typename graph<VertexType>::vertex_container* const edge_begin_point_vertex_container,
    const typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type,
    const typename graph<VertexType>::template adj_set<typename graph<VertexType>::vertex_container* >::iterator& inner_iterator) :
graphdom::graph<VertexType>::template adj_list_base_iterator< typename graph<VertexType>::vertex_container* >(
    iterator_owner_pointer,
    iterator_owner_graph_edges_type,
    edge_begin_point_vertex_container,
    edges_type_restriction,
    inner_iterator_edge_current_type,
    inner_iterator
) {}

#endif //GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_IMPL_H
