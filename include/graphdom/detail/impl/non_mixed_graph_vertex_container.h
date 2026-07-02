#ifndef GRAPHDOM_NON_MIXED_GRAPH_VERTEX_CONTAINER_IMPL_H
#define GRAPHDOM_NON_MIXED_GRAPH_VERTEX_CONTAINER_IMPL_H

#include "../../graph.h"
#include "vertex_container.h"

template <typename VertexType>
template <typename VertexContainerPointerType>
graphdom::graph<VertexType>::non_mixed_graph_vertex_container<VertexContainerPointerType>::
non_mixed_graph_vertex_container(const VertexType& v) : vertex_container(v) {}

template <typename VertexType>
template <typename VertexContainerPointerType>
graphdom::graph<VertexType>::non_mixed_graph_vertex_container<VertexContainerPointerType>::
non_mixed_graph_vertex_container(VertexType&& v) : vertex_container( std::move( v ) ) {}

#endif //GRAPHDOM_NON_MIXED_GRAPH_VERTEX_CONTAINER_IMPL_H