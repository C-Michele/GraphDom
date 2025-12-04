#ifndef HANDLERS_IMPLEMENTATIONS_H
#define HANDLERS_IMPLEMENTATIONS_H

#include <stdexcept>

#include "graph.h"
#include "handlers_declarations.h"

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    set_graph_vertex_container(nullptr),
    multiset_graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

template<typename VertexType>
const VertexType& MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator*() const {
    if (set_graph_vertex_container!=nullptr) {
        return set_graph_vertex_container->vertex;
    }
    if (multiset_graph_vertex_container!=nullptr) {
        return multiset_graph_vertex_container->value;
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
const VertexType* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator->() const {
    if (set_graph_vertex_container!=nullptr) {
        return &(set_graph_vertex_container->vertex);
    }
    if (multiset_graph_vertex_container!=nullptr) {
        return &(multiset_graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator==(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    if (vertex_owner != other.vertex_owner ) {
        return false;
    }
    if (set_graph_vertex_container != nullptr ) {
        return set_graph_vertex_container == other.graph_vertex_container;
    }
    return multiset_graph_vertex_container == other.graph_vertex_container;
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator!=(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    return ! ( (*this) == other );
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    set_graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    multiset_graph_vertex_container(nullptr) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vc_ref) :
    vertex_owner(vo),
    set_graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    multiset_graph_vertex_container(nullptr),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

template<typename VertexType>
const VertexType& MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator*() const {
    if (graph_vertex_container!=nullptr) {
        return graph_vertex_container->vertex;
    }
    throw std::runtime_error("Impossible to dereference a const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
const VertexType* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator->() const {
    if (graph_vertex_container!=nullptr) {
        return &(graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator==(const CONSTANT_VERTEX_PTR_NAME& other) const {
    return (vertex_owner == other.vertex_owner) && (graph_vertex_container == other.graph_vertex_container);
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator!=(const CONSTANT_VERTEX_PTR_NAME& other) const {
    return !( (*this)== other );
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vc_ref) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const vo ,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<vertex_container*>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const multiset_vertex_graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<vertex_container*>& vc_ref) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(dynamic_cast<const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*>(other.vertex_owner)),
    multiset_graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type) {
    if ( vertex_owner == nullptr ) {
        throw std::runtime_error("Impossible to convert"); //TODO: write a better message
    }
}

template<typename VertexType>
VertexType& MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator*() const {
    if (multiset_graph_vertex_container!=nullptr) {
        return multiset_graph_vertex_container->vertex;
    }
    throw std::runtime_error("Impossible to dereference a multiset_vertex_graph::vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
VertexType* MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator->() const {
    if (multiset_graph_vertex_container!=nullptr) {
        return &(multiset_graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a multiset_vertex_graph::vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator==(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::const_vertex_ptr& other) const {
    if(vertex_owner!=other.vertex_owner) {
        return false;
    }
    return multiset_graph_vertex_container == other.graph_vertex_container;
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator!=(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    return !( (*this) == other );
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vo,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    multiset_graph_vertex_container(static_cast<VertexContainerPointerType>(&vc_ref)) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vo,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vc_ref) :
    vertex_owner(vo),
    multiset_graph_vertex_container(static_cast<VertexContainerPointerType>(&vc_ref)),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

#endif //HANDLERS_IMPLEMENTATIONS_H