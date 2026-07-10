#ifndef GRAPHDOM_MULTISET_GRAPH_VERTEX_HANDLE_IMPL_H
#define GRAPHDOM_MULTISET_GRAPH_VERTEX_HANDLE_IMPL_H

#include <stdexcept>

#include "../../graph.h"
#include "../vertex_base_handle.h"
#include "../vertex_handle.h"
#include "../../multiset_graph.h"
#include "../multiset_graph_vertex_handle.h"

template <typename VertexType>
graphdom::multiset_graph<VertexType>::vertex_handle::vertex_handle(const graphdom::multiset_graph<VertexType>::vertex_handle& other) :
graphdom::graph<VertexType>::template vertex_base_handle< typename graphdom::graph<VertexType>::vertex_container* >( other ) {}

template <typename VertexType>
graphdom::multiset_graph<VertexType>::vertex_handle::vertex_handle(const typename graph<VertexType>::vertex_handle& other) :
graphdom::graph<VertexType>::template vertex_base_handle< typename graphdom::graph<VertexType>::vertex_container* >(
    other.vertex_container_owner_graph_pointer,
    other.vertex_container_owner_graph_edges_type,
    nullptr
) {
    if ( dynamic_cast< const graphdom::multiset_graph<VertexType>* >( this->vertex_container_owner_graph_pointer ) == nullptr ) {
        throw std::runtime_error("Attempt to convert a \"graphdom::graph<VertexType>::vertex_handle\", which identifies a vertex belonging to a \"graphdom::set_graph<VertexType>\", to a \"graphdom::multiset_graph<VertexType>::vertex_handle\""); //TODO: write a better message
    }
    this->vertex_container_pointer = const_cast< typename graphdom::graph<VertexType>::vertex_container* >( other.vertex_container_pointer );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle& graphdom::multiset_graph<VertexType>::vertex_handle::operator=(const vertex_handle& other) {
    if ( this != &other ) {
        this->vertex_container_owner_graph_pointer = other.vertex_container_owner_graph_pointer;
        this->vertex_container_owner_graph_edges_type = other.vertex_container_owner_graph_edges_type;
        this->vertex_container_pointer = other.vertex_container_pointer;
    }
    return (*this);
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list graphdom::multiset_graph<VertexType>::vertex_handle::adj_list() const {
    return typename graphdom::multiset_graph<VertexType>::adj_list(
        this->vertex_container_owner_graph_pointer,
        this->vertex_container_owner_graph_edges_type,
        this->vertex_container_pointer
    );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list graphdom::multiset_graph<VertexType>::vertex_handle::adj_list(const edge_type edge_type) const {
    return typename graphdom::multiset_graph<VertexType>::adj_list(
        this->vertex_container_owner_graph_pointer,
        this->vertex_container_owner_graph_edges_type,
        this->vertex_container_pointer,
        ( edge_type == undirected ) ?
            graphdom::graph<VertexType>::edges_type_selection_type::undirected_edges :
            graphdom::graph<VertexType>::edges_type_selection_type::directed_edges
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::multiset_graph<VertexType>::vertex_handle::const_adj_list() const {
    return typename graphdom::graph<VertexType>::const_adj_list(
        this->vertex_container_owner_graph_pointer,
        this->vertex_container_owner_graph_edges_type,
        this->vertex_container_pointer
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::multiset_graph<VertexType>::vertex_handle::const_adj_list(const edge_type edge_type) const {
    return typename graphdom::graph<VertexType>::const_adj_list(
        this->vertex_container_owner_graph_pointer,
        this->vertex_container_owner_graph_edges_type,
        this->vertex_container_pointer,
        ( edge_type == undirected ) ?
            graphdom::graph<VertexType>::edges_type_selection_type::undirected_edges :
            graphdom::graph<VertexType>::edges_type_selection_type::directed_edges
    );
}

#endif //GRAPHDOM_MULTISET_GRAPH_VERTEX_HANDLE_IMPL_H
