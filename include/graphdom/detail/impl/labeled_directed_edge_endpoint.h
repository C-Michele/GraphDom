#ifndef GRAPHDOM_LABELED_DIRECTED_EDGE_ENDPOINT_IMPL_H
#define GRAPHDOM_LABELED_DIRECTED_EDGE_ENDPOINT_IMPL_H

#include "../../graph.h"
#include "edge_endpoint.h"
#include "../labeled_directed_edge_endpoint.h"

template <typename VertexType>
template <typename VertexContainerPointerType, typename EdgeLabelType>
graphdom::graph<VertexType>::labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>::
labeled_directed_edge_endpoint(
    const VertexContainerPointerType ptr,
    const EdgeLabelType& edge ) :
        edge_endpoint<VertexContainerPointerType>(ptr),
        edge_label(edge) {}

template<typename VertexType>
template<typename VertexContainerPointerType, typename EdgeLabelType>
graphdom::graph<VertexType>::labeled_directed_edge_endpoint<VertexContainerPointerType, EdgeLabelType>::
labeled_directed_edge_endpoint(
    const VertexContainerPointerType ptr,
    EdgeLabelType&& edge) :
        edge_endpoint<VertexContainerPointerType>(ptr),
        edge_label( std::move(edge) ) {}

#endif //GRAPHDOM_LABELED_DIRECTED_EDGE_ENDPOINT_IMPL_H
