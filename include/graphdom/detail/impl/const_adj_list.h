#ifndef GRAPHDOM_CONST_ADJ_LIST_IMPL_H
#define GRAPHDOM_CONST_ADJ_LIST_IMPL_H

#include "../../graph.h"
#include "../base_adj_list.h"
#include "../const_adj_list.h"

template <typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(const const_adj_list& other) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >( other ){}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(const typename graph<VertexType>::adj_list& other) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >(
    other.adj_list_owner_graph_pointer,
    other.adj_list_owner_graph_edges_type,
    other.adj_list_common_begin_point_vertex_container_pointer,
    other.adj_list_edges_type_selection
){}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(const typename multiset_graph<VertexType>::adj_list& other) :
graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* >(
    other.adj_list_owner_graph_pointer,
    other.adj_list_owner_graph_edges_type,
    other.adj_list_common_begin_point_vertex_container_pointer,
    other.adj_list_edges_type_selection
){}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::const_adj_list::begin() const {
    //TODO: implementation
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::const_adj_list::end() const {
    //TODO: implementation
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
    adj_list_owner_graph_pointer,
    adj_list_owner_graph_edges_type,
    adj_list_common_begin_point_vertex_container_pointer,
    adj_list_edges_type_selection
){}

#endif //GRAPHDOM_CONST_ADJ_LIST_IMPL_H
