#ifndef GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_IMPL_H
#define GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_IMPL_H

#include "../../graph.h"
#include "../base_adj_list.h"
#include "../adj_list.h"
#include "../../multiset_graph.h"
#include "../multiset_graph_adj_list.h"

template <typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list::adj_list(const adj_list& other) :
graphdom::graph<VertexType>::template base_adj_list< typename graphdom::graph<VertexType>::vertex_container* >( other ){}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list::adj_list(const typename graph<VertexType>::adj_list& other) :
graphdom::graph<VertexType>::template base_adj_list< typename graphdom::graph<VertexType>::vertex_container* >(
    other.adj_list_common_begin_point_vertex_container_pointer,
    other.adj_list_owner_graph_edges_type,
    nullptr,
    other.adj_list_edges_type_selection
    ) {
    if ( dynamic_cast< const graphdom::multiset_graph<VertexType>* >( this->vertex_container_owner_graph_pointer ) == nullptr ) {
        throw std::runtime_error("Attempt to convert a \"graphdom::graph<VertexType>::adj_list\", which identifies an adj list belonging to a \"graphdom::set_graph<VertexType>\", to a \"graphdom::multiset_graph<VertexType>::adj_list\""); //TODO: write a better message
    }
    this->adj_list_common_begin_point_vertex_container_pointer = const_cast< typename graphdom::graph<VertexType>::vertex_container* >( other.adj_list_common_begin_point_vertex_container_pointer );
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list::adj_list(
    const graph<VertexType>* const adj_list_owner_graph_pointer,
    const typename graphdom::graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
    typename graphdom::graph<VertexType>::vertex_container* const adj_list_common_begin_point_vertex_container_pointer,
    const typename graphdom::graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection ) :
graphdom::graph<VertexType>::template base_adj_list< typename graphdom::graph<VertexType>::vertex_container* >(
    adj_list_owner_graph_pointer,
    adj_list_owner_graph_edges_type,
    adj_list_common_begin_point_vertex_container_pointer,
    adj_list_edges_type_selection
){}

#endif //GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_IMPL_H
