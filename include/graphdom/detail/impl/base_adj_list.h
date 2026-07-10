#ifndef GRAPHDOM_BASE_ADJ_LIST_IMPL_H
#define GRAPHDOM_BASE_ADJ_LIST_IMPL_H

#include "../../graph.h"
#include "../base_adj_list.h"

template <typename VertexType>
template <typename VertexContainerPointerType>
graphdom::graph<VertexType>::base_adj_list<VertexContainerPointerType>::base_adj_list(
    const graph<VertexType>* const adj_list_owner_graph_pointer,
    const graph_edges_type adj_list_owner_graph_edges_type,
    const VertexContainerPointerType adj_list_common_begin_point_vertex_container_pointer,
    const graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection
) :
adj_list_owner_graph_pointer(adj_list_owner_graph_pointer),
adj_list_owner_graph_edges_type(adj_list_owner_graph_edges_type),
adj_list_common_begin_point_vertex_container_pointer(adj_list_common_begin_point_vertex_container_pointer),
adj_list_edges_type_selection(adj_list_edges_type_selection) {}

#endif //GRAPHDOM_BASE_ADJ_LIST_IMPL_H