#ifndef GRAPHDOM_ADJ_LIST_BASE_ITERATOR_IMPL_H
#define GRAPHDOM_ADJ_LIST_BASE_ITERATOR_IMPL_H

#include <variant>

#include "../adj_list_base_iterator.h"

template<typename VertexType>
template<typename VertexContainerPointerType, typename EdgesEndpointsContainerType>
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType, EdgesEndpointsContainerType>::
adj_list_base_iterator() :
    iterator_owner_graph(nullptr),
    iterator_owner_graph_edges_type(mixed),
    edge_begin_point_undirected_adj(nullptr),
    edge_begin_point_directed_adj(nullptr),
    inner_iterator_edge_current_type(undirected),
    inner_iterator( special_begin_end_indicator() ) {}

template<typename VertexType>
template<typename VertexContainerPointerType, typename EdgesEndpointsContainerType>
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType, EdgesEndpointsContainerType>::
adj_list_base_iterator(
    const graph<VertexType>* iterator_owner_pointer,
    const graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    EdgesEndpointsContainerType* const edge_begin_point_undirected_adj,
    EdgesEndpointsContainerType* const edge_begin_point_directed_adj,
    const graphdom::edge_type inner_iterator_edge_current_type) :
    iterator_owner_graph(iterator_owner_pointer),
    iterator_owner_graph_edges_type(iterator_owner_graph_edges_type),
    edge_begin_point_undirected_adj(edge_begin_point_undirected_adj),
    edge_begin_point_directed_adj(edge_begin_point_directed_adj),
    inner_iterator_edge_current_type(inner_iterator_edge_current_type),
    inner_iterator( special_begin_end_indicator() ) {}

template<typename VertexType>
template<typename VertexContainerPointerType, typename EdgesEndpointsContainerType>
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType, EdgesEndpointsContainerType>::
adj_list_base_iterator(
    const graph<VertexType>* iterator_owner_pointer,
    const graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    EdgesEndpointsContainerType* const edge_begin_point_undirected_adj,
    EdgesEndpointsContainerType* const edge_begin_point_directed_adj,
    const graphdom::edge_type inner_iterator_edge_current_type,
    const typename EdgesEndpointsContainerType::iterator& inner_iterator) :
    iterator_owner_graph(iterator_owner_pointer),
    iterator_owner_graph_edges_type(iterator_owner_graph_edges_type),
    edge_begin_point_undirected_adj(edge_begin_point_undirected_adj),
    edge_begin_point_directed_adj(edge_begin_point_directed_adj),
    inner_iterator_edge_current_type(inner_iterator_edge_current_type),
    inner_iterator( inner_iterator ) {}

template<typename VertexType>
template<typename VertexContainerPointerType, typename EdgesEndpointsContainerType>
template<typename K, typename J>
constexpr bool graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType,EdgesEndpointsContainerType>::operator==(
    const adj_list_base_iterator<K,J>& other_iterator) const {
    if ( inner_iterator_edge_current_type != other_iterator.inner_iterator_edge_current_type ) {
        return false;
    }
    if ( std::holds_alternative< special_begin_end_indicator >( inner_iterator ) ) {
        if ( std::holds_alternative< adj_list_base_iterator<K,J>::special_begin_end_indicator >( other_iterator.inner_iterator ) ) {
            return true;
        }
        return false;
    }
    if ( std::holds_alternative< J::iterator >( other_iterator.inner_iterator ) ) {
        return ( *( std::get< EdgesEndpointsContainerType::iterator >( inner_iterator ) ) ) == ( *( std::get< J::iterator >( other_iterator.inner_iterator ) ) );
    }
    return false;
}

template<typename VertexType>
template<typename VertexContainerPointerType, typename EdgesEndpointsContainerType>
template<typename K, typename J>
constexpr bool graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType,EdgesEndpointsContainerType>::operator!=(
    const adj_list_base_iterator<K,J>& other_iterator) const {
    return !( (*this) == other_iterator );
}

#endif //GRAPHDOM_ADJ_LIST_BASE_ITERATOR_IMPL_H