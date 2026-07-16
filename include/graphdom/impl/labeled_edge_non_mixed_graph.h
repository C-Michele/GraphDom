#ifndef GRAPHDOM_LABELED_EDGE_NON_MIXED_GRAPH_IMPL_H
#define GRAPHDOM_LABELED_EDGE_NON_MIXED_GRAPH_IMPL_H

#include "../labeled_edge_non_mixed_graph.h"

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph() : edges_labeller() {}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph(const EdgeLabellerType& edge_labeller) : edges_labeller(edge_labeller) {}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph(EdgeLabellerType&& edge_labeller) : edges_labeller(std::move(edge_labeller)) {}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
constexpr const EdgeLabellerType& graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::get_edges_labeller() const {
    return edges_labeller;
}

template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
void graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& first_endpoint,
    const typename graph<VertexType>::vertex_const_handle& second_endpoint) {
    insert_edge(first_endpoint,second_endpoint,edges_labeller(first_endpoint,second_endpoint));
}

#endif //GRAPHDOM_LABELED_EDGE_NON_MIXED_GRAPH_IMPL_H