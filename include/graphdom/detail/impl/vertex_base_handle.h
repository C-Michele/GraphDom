#ifndef GRAPHDOM_VERTEX_BASE_HANDLE_IMPL_H
#define GRAPHDOM_VERTEX_BASE_HANDLE_IMPL_H

#include "../../graph.h"
#include "../vertex_container.h"
#include "../vertex_base_handle.h"

template<typename VertexType>
template<typename VertexContainerPointerType>
graphdom::graph<VertexType>::vertex_base_handle<VertexContainerPointerType>::vertex_base_handle(
    const graph<VertexType>* vertex_container_owner_ptr,
    const graph_edges_type vertex_container_owner_et,
    const VertexContainerPointerType vertex_container_ptr ) :
    vertex_container_owner_graph_pointer(vertex_container_owner_ptr),
    vertex_container_owner_graph_edges_type(vertex_container_owner_et),
    vertex_container_pointer(vertex_container_ptr) {}

template<typename VertexType>
template<typename VertexContainerPointerType>
constexpr auto& graphdom::graph<VertexType>::vertex_base_handle<VertexContainerPointerType>::operator*() const {
    return vertex_container_pointer->vertex;
}

template<typename VertexType>
template<typename VertexContainerPointerType>
constexpr auto* graphdom::graph<VertexType>::vertex_base_handle<VertexContainerPointerType>::operator->() const {
    return &( vertex_container_pointer->vertex );
}

template<typename VertexType>
template<typename VertexContainerPointerType>
template<typename K>
constexpr bool graphdom::graph<VertexType>::vertex_base_handle<VertexContainerPointerType>::operator==(
    const vertex_base_handle<K>& other_handle) const {
    return this->vertex_container_pointer == other_handle.vertex_container_pointer;
}

template<typename VertexType>
template<typename VertexContainerPointerType>
template<typename K>
constexpr bool graphdom::graph<VertexType>::vertex_base_handle<VertexContainerPointerType>::operator!=(
    const vertex_base_handle<K>& other_handle) const {
    return this->vertex_container_pointer != other_handle.vertex_container_pointer;
}

#endif //GRAPHDOM_VERTEX_BASE_HANDLE_IMPL_H
