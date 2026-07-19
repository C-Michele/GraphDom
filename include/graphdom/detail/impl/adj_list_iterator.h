/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_ADJ_LIST_ITERATOR_IMPL_H
#define GRAPHDOM_ADJ_LIST_ITERATOR_IMPL_H

#include "../../graph.h"
#include "../adj_list_base_iterator.h"
#include "../adj_list_iterator.h"

template <typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(const adj_list_iterator& other_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container*  >( other_iterator ){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(const typename multiset_graph<VertexType>::adj_list_iterator& other_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container*  >(
    other_iterator.iterator_owner_graph,
    other_iterator.iterator_owner_graph_edges_type,
    other_iterator.edge_begin_point_vertex_container,
    other_iterator.edges_type_restriction,
    other_iterator.inner_iterator_edge_current_type,
    std::get< typename graph<VertexType>::adj_set<graph<VertexType>::vertex_container*>::iterator >( other_iterator.inner_iterator )
){}

/*
template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(const typename multiset_graph<VertexType>::adj_list_iterator& other_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container*  >(
){}
*/

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::operator typename multiset_graph<VertexType>::adj_list_iterator() const {
    return graphdom::multiset_graph<VertexType>::adj_list_iterator(*this);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::adj_list_iterator::operator->() const {
    return *this;
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::adj_list_iterator::operator*() const {
    return graphdom::graph<VertexType>::vertex_handle(
        this->iterator_owner_graph,
        this->iterator_owner_graph_edges_type,
        ( std::holds_alternative< typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator >( this->inner_iterator ) ) ?
        ( ( *( std::get< typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator >( this->inner_iterator ) ) )->vertex_container_ptr ) :
        ( ( *( std::get< typename graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator >( this->inner_iterator ) ) )->vertex_container_ptr )
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator& graphdom::graph<VertexType>::adj_list_iterator::operator=(const adj_list_iterator& other) {
    if ( this != &other ) {
        this->iterator_owner_graph = other.iterator_owner_graph;
        this->iterator_owner_graph_edges_type = other.iterator_owner_graph_edges_type;
        this->edge_begin_point_vertex_container = other.edge_begin_point_vertex_container;
        this->edges_type_restriction = other.edges_type_restriction;
        this->inner_iterator_edge_current_type;
        this->inner_iterator = other.inner_iterator;
    }
    return (*this);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator& graphdom::graph<VertexType>::adj_list_iterator::operator++() {
    this->internal_single_increment();
    return *this;
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator graphdom::graph<VertexType>::adj_list_iterator::operator++(int) {
    auto to_return = *this;
    ++(*this);
    return to_return;
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(const typename graph<VertexType>::adj_list_base_iterator<const typename graph<VertexType>::vertex_container*>& other) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container*  >( other ){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graph<VertexType>* const iterator_owner_pointer,
    const typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    const typename graph<VertexType>::vertex_container* const edge_begin_point_vertex_container,
    const typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container* >(
    iterator_owner_pointer,
    iterator_owner_graph_edges_type,
    edge_begin_point_vertex_container,
    edges_type_restriction,
    inner_iterator_edge_current_type
){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graph<VertexType>* const iterator_owner_pointer,
    const typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    const typename graph<VertexType>::vertex_container* const edge_begin_point_vertex_container,
    const typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type,
    const typename graph<VertexType>::adj_set<typename graph<VertexType>::vertex_container*>::iterator& inner_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container* >(
    iterator_owner_pointer,
    iterator_owner_graph_edges_type,
    edge_begin_point_vertex_container,
    edges_type_restriction,
    inner_iterator_edge_current_type,
    inner_iterator
){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graph<VertexType>* const iterator_owner_pointer,
    const typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    const typename graph<VertexType>::vertex_container* const edge_begin_point_vertex_container,
    const typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type,
    const typename graph<VertexType>::adj_set<const typename graph<VertexType>::vertex_container*>::iterator& inner_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container* >(
    iterator_owner_pointer,
    iterator_owner_graph_edges_type,
    edge_begin_point_vertex_container,
    edges_type_restriction,
    inner_iterator_edge_current_type,
    inner_iterator
){}

#endif //GRAPHDOM_ADJ_LIST_ITERATOR_IMPL_H