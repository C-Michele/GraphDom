#ifndef GRAPHDOM_VERTEX_CONST_HANDLE_IMPL_H
#define GRAPHDOM_VERTEX_CONST_HANDLE_IMPL_H

#include "../../graph.h"
#include "../vertex_base_handle.h"
#include "../vertex_const_handle.h"

template <typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(const typename graph<VertexType>::vertex_const_handle& other) :
graphdom::graph<VertexType>::vertex_base_handle< const graphdom::graph<VertexType>::vertex_container* >( other ){}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(const typename graph<VertexType>::vertex_handle& other) :
graphdom::graph<VertexType>::vertex_base_handle< const graphdom::graph<VertexType>::vertex_container* >( other ){}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(const typename graphdom::multiset_graph<VertexType>::vertex_handle& other) :
graphdom::graph<VertexType>::vertex_base_handle< const graphdom::graph<VertexType>::vertex_container* >(
    other.vertex_container_owner_graph_pointer,
    other.vertex_container_owner_graph_edges_type,
    other.vertex_container_pointer
) {}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle& graphdom::graph<VertexType>::vertex_const_handle::operator=(const vertex_const_handle& other) {
    if ( this != &other ) {
        this->vertex_container_owner_graph_pointer = other.vertex_container_owner_graph_pointer;
        this->vertex_container_owner_graph_edges_type = other.vertex_container_owner_graph_edges_type;
        this->vertex_container_pointer = other.vertex_container_pointer;
    }
    return (*this);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::graph<VertexType>::vertex_const_handle::adj_list() const {
    return graphdom::graph<VertexType>::const_adj_list(
        this->vertex_container_owner_graph_pointer,
        this->vertex_container_owner_graph_edges_type,
        this->vertex_container_pointer
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::graph<VertexType>::vertex_const_handle::adj_list(const edge_type edge_type) const {
    return graphdom::graph<VertexType>::const_adj_list(
        this->vertex_container_owner_graph_pointer,
        this->vertex_container_owner_graph_edges_type,
        this->vertex_container_pointer,
        ( edge_type == graphdom::edge_type::undirected ) ?
            graphdom::graph<VertexType>::edges_type_selection_type::undirected_edges :
            graphdom::graph<VertexType>::edges_type_selection_type::directed_edges
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::graph<VertexType>::vertex_const_handle::const_adj_list() const {
    return adj_list();
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::graph<VertexType>::vertex_const_handle::const_adj_list(const edge_type edge_type) const {
    return adj_list(edge_type);
}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(
    const graph<VertexType>* const vertex_container_owner_ptr,
    const graph<VertexType>::graph_edges_type vertex_container_owner_et,
    const typename graph<VertexType>::vertex_container* const vertex_container_ptr) :
graphdom::graph<VertexType>::vertex_base_handle< const graphdom::graph<VertexType>::vertex_container* >(
    vertex_container_owner_ptr,
    vertex_container_owner_et,
    vertex_container_ptr
) {}

#endif //GRAPHDOM_VERTEX_CONST_HANDLE_IMPL_H
