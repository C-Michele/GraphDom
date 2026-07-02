#ifndef GRAPHDOM_LABELED_UNDIRECTED_EDGE_ENDPOINT_IMPL_H
#define GRAPHDOM_LABELED_UNDIRECTED_EDGE_ENDPOINT_IMPL_H

#include "../../graph.h"
#include "edge_endpoint.h"
#include "../labeled_undirected_edge_endpoint.h"

template <typename VertexType>
template <typename VertexContainerPointerType, typename EdgeLabelType>
graphdom::graph<VertexType>::labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>::
labeled_undirected_edge_endpoint(const VertexContainerPointerType ptr, const EdgeLabelType& edge) :
    edge_endpoint<VertexContainerPointerType>(ptr),
    edge_label_ptr(std::make_shared<EdgeLabelType>(edge)) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename EdgeLabelType>
graphdom::graph<VertexType>::labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>::
labeled_undirected_edge_endpoint(const VertexContainerPointerType ptr, EdgeLabelType&& edge) :
    edge_endpoint<VertexContainerPointerType>(ptr),
    edge_label_ptr(std::make_shared<EdgeLabelType>(std::move(edge))) {}

template <typename VertexType>
template <typename VertexContainerPointerType, typename EdgeLabelType>
graphdom::graph<VertexType>::labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>::
labeled_undirected_edge_endpoint(const VertexContainerPointerType ptr, const std::shared_ptr<EdgeLabelType>& existent_edge_label_ptr) :
    edge_endpoint<VertexContainerPointerType>(ptr),
    edge_label_ptr(existent_edge_label_ptr) {}

#endif //GRAPHDOM_LABELED_UNDIRECTED_EDGE_ENDPOINT_IMPL_H