#ifndef GRAPHDOM_ADJ_LIST_IMPL_H
#define GRAPHDOM_ADJ_LIST_IMPL_H

#include "../../graph.h"
#include "../vertex_container.h"
#include "../base_adj_list.h"
#include "../adj_list.h"
#include "../../multiset_graph.h"
#include "../multiset_graph_adj_list.h"

template <typename VertexType>
graphdom::graph<VertexType>::adj_list::adj_list(const adj_list& other) :
graphdom::graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >( other ){}

template <typename VertexType>
graphdom::graph<VertexType>::adj_list::adj_list(const typename graphdom::multiset_graph<VertexType>::adj_list& other) :
graphdom::graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >(
    other.adj_list_owner_graph_pointer,
    other.adj_list_owner_graph_edges_type,
    other.adj_list_common_begin_point_vertex_container_pointer,
    other.adj_list_edges_type_selection
){}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list::operator typename multiset_graph<VertexType>::adj_list() const {
    return graphdom::multiset_graph<VertexType>::adj_list( *this );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator graphdom::graph<VertexType>::adj_list::begin() const {
    //TODO: implementation
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator graphdom::graph<VertexType>::adj_list::end() const {
    //TODO: implementation
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::adj_list::cbegin() const {
    return begin();
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::adj_list::cend() const {
    return end();
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list::adj_list(
    const graphdom::graph<VertexType>* const adj_list_owner_graph_pointer,
    const typename graphdom::graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
    const typename graphdom::graph<VertexType>::vertex_container* const adj_list_common_begin_point_vertex_container_pointer,
    const typename graphdom::graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection) :
graphdom::graph<VertexType>::base_adj_list< const graphdom::graph<VertexType>::vertex_container* >(
    adj_list_owner_graph_pointer,
    adj_list_owner_graph_edges_type,
    adj_list_common_begin_point_vertex_container_pointer,
    adj_list_edges_type_selection
){}

#endif //GRAPHDOM_ADJ_LIST_IMPL_H
