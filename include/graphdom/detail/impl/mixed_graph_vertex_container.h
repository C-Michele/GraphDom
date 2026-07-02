#ifndef GRAPHDOM_MIXED_GRAPH_VERTEX_CONTAINER_IMPL_H
#define GRAPHDOM_MIXED_GRAPH_VERTEX_CONTAINER_IMPL_H

#include "../../graph.h"
#include "../mixed_graph_vertex_container.h"

template <typename VertexType>
template <typename VertexContainerPointerType>
graphdom::graph<VertexType>::mixed_graph_vertex_container<VertexContainerPointerType>::
mixed_graph_vertex_container(const VertexType& v) : vertex_container(v) {}

template <typename VertexType>
template <typename VertexContainerPointerType>
graphdom::graph<VertexType>::mixed_graph_vertex_container<VertexContainerPointerType>::
mixed_graph_vertex_container(VertexType&& v) : vertex_container(std::move(v)) {}

#endif //GRAPHDOM_MIXED_GRAPH_VERTEX_CONTAINER_IMPL_H