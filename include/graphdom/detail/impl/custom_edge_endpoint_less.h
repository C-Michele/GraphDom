#ifndef GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_IMPL_H
#define GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_IMPL_H

#include "../../graph.h"
#include "../vertex_container.h"
#include "../edge_endpoint.h"
#include "../custom_edge_endpoint_less.h"

template <typename VertexType>
template <typename VertexContainerPointerType>
bool constexpr graphdom::graph<VertexType>::custom_edge_endpoint_less<VertexContainerPointerType>::operator()(
    const edge_endpoint<VertexContainerPointerType>* const left,
    const edge_endpoint<VertexContainerPointerType>* const right) const {
    return less_functor( left->vertex_container_ptr , right->vertex_container_ptr );
}

template <typename VertexType>
template <typename VertexContainerPointerType>
bool constexpr graphdom::graph<VertexType>::custom_edge_endpoint_less<VertexContainerPointerType>::operator()(
    const edge_endpoint<VertexContainerPointerType>* const left,
    const vertex_container* const right) const {
    return less_functor( left->vertex_container_ptr , right );
}

template <typename VertexType>
template <typename VertexContainerPointerType>
bool constexpr graphdom::graph<VertexType>::custom_edge_endpoint_less<VertexContainerPointerType>::operator()(
    const vertex_container* const left,
    const edge_endpoint<VertexContainerPointerType>* const right) const {
    return less_functor( left , right->vertex_container_ptr );
}

#endif //GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_IMPL_H