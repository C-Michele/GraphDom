#ifndef GRAPHDOM_ADJ_LIST_CONST_ITERATOR_IMPL_H
#define GRAPHDOM_ADJ_LIST_CONST_ITERATOR_IMPL_H

#include "../../graph.h"
#include "../adj_list_base_iterator.h"
#include "../adj_list_const_iterator.h"

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator() :
graphdom::graph<VertexType>::adj_list_base_iterator< const graphdom::graph<VertexType>::vertex_container* >(){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(const adj_list_const_iterator& other_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator< const graphdom::graph<VertexType>::vertex_container* >(
    other_iterator
){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(const typename graphdom::graph<VertexType>::adj_list_iterator& other_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator< const graphdom::graph<VertexType>::vertex_container* >(
    other_iterator
){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(const typename graphdom::multiset_graph<VertexType>::adj_list_iterator& other_iterator) :
graphdom::graph<VertexType>::adj_list_base_iterator<  const graph<VertexType>::vertex_container*  >(
    other_iterator.iterator_owner_graph,
    other_iterator.iterator_owner_graph_edges_type,
    other_iterator.edge_begin_point_vertex_container,
    other_iterator.edges_type_restriction,
    other_iterator.inner_iterator_edge_current_type,
    std::get< typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator >( other_iterator.inner_iterator )
){}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::adj_list_const_iterator::operator->() const {
    return *this;
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::adj_list_const_iterator::operator*() const {
    return graphdom::graph<VertexType>::vertex_const_handle(
        this->iterator_owner_graph,
        this->iterator_owner_graph_edges_type,
        ( std::holds_alternative< typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator >( this->inner_iterator ) ) ?
        ( ( *( std::get< typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator >( this->inner_iterator ) ) )->vertex_container_ptr ) :
        ( ( *( std::get< typename graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator >( this->inner_iterator ) ) )->vertex_container_ptr )
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator& graphdom::graph<VertexType>::adj_list_const_iterator::operator=(const adj_list_const_iterator& other) {
    if ( this != &other ) {
        this->iterator_owner_graph = other.iterator_owner_graph;
        this->iterator_owner_graph_edges_type = other.iterator_owner_graph_edges_type;
        this->edge_begin_point_vertex_container = other.edge_begin_point_vertex_container;
        this->edges_type_restriction = other.edges_type_restriction;
        this->inner_iterator = other.inner_iterator;
        this->inner_iterator_edge_current_type = other.inner_iterator_edge_current_type;
    }
    return *this;
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator& graphdom::graph<VertexType>::adj_list_const_iterator::operator++() {
    this->internal_single_increment();
    return *this;
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::adj_list_const_iterator::operator++(int) {
    auto to_return = *this;
    ++(*this);
    return to_return;
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(const typename graph<VertexType>::adj_list_base_iterator<const typename graph<VertexType>::vertex_container*>& other) :
graphdom::graph<VertexType>::adj_list_base_iterator< const graphdom::graph<VertexType>::vertex_container* >( other ){}

#endif //GRAPHDOM_ADJ_LIST_CONST_ITERATOR_IMPL_H
