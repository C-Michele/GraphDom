#ifndef GRAPHDOM_BASE_ADJ_LIST_IMPL_H
#define GRAPHDOM_BASE_ADJ_LIST_IMPL_H

#include "../../graph.h"
#include "../base_adj_list.h"
#include "../adj_list_base_iterator.h"

template <typename VertexType>
template <typename VertexContainerPointerType>
graphdom::graph<VertexType>::base_adj_list<VertexContainerPointerType>::base_adj_list(
    const graph<VertexType>* const adj_list_owner_graph_pointer,
    const graph_edges_type adj_list_owner_graph_edges_type,
    const VertexContainerPointerType adj_list_common_begin_point_vertex_container_pointer,
    const graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection
) :
adj_list_owner_graph_pointer(adj_list_owner_graph_pointer),
adj_list_owner_graph_edges_type(adj_list_owner_graph_edges_type),
adj_list_common_begin_point_vertex_container_pointer(adj_list_common_begin_point_vertex_container_pointer),
adj_list_edges_type_selection(adj_list_edges_type_selection) {}

template <typename VertexType>
template <typename VertexContainerPointerType>
template <typename K>
constexpr typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>
graphdom::graph<VertexType>::base_adj_list<VertexContainerPointerType>::internal_begin() const {
    static_assert(
        std::is_same< K , graphdom::graph<VertexType>::vertex_container* >::value ||
        std::is_same< K , const graphdom::graph<VertexType>::vertex_container* >::value
    );
    auto* const undirected_adj_set = get_adj_set_if_accessible<K>(graphdom::edge_type::undirected);
    auto* const directed_adj_set = get_adj_set_if_accessible<K>(graphdom::edge_type::directed);
    if ( ( undirected_adj_set == nullptr ) && ( directed_adj_set == nullptr ) ) {
        return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
            adj_list_owner_graph_pointer,
            adj_list_owner_graph_edges_type,
            adj_list_common_begin_point_vertex_container_pointer,
            adj_list_edges_type_selection,
            ( adj_list_owner_graph_edges_type == undirected ) ? graphdom::edge_type::undirected : graphdom::edge_type::directed
        );
    }
    if ( undirected_adj_set != nullptr ) {
        if ( undirected_adj_set->empty() && directed_adj_set != nullptr ) {
            if ( directed_adj_set->empty() ) {
                return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
                    adj_list_owner_graph_pointer,
                    adj_list_owner_graph_edges_type,
                    adj_list_common_begin_point_vertex_container_pointer,
                    adj_list_edges_type_selection,
                    graphdom::edge_type::undirected,
                    undirected_adj_set->begin()
                );
            }
            return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
                adj_list_owner_graph_pointer,
                adj_list_owner_graph_edges_type,
                adj_list_common_begin_point_vertex_container_pointer,
                adj_list_edges_type_selection,
                graphdom::edge_type::directed,
                directed_adj_set->begin()
            );
        }
        return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
            adj_list_owner_graph_pointer,
            adj_list_owner_graph_edges_type,
            adj_list_common_begin_point_vertex_container_pointer,
            adj_list_edges_type_selection,
            graphdom::edge_type::undirected,
            undirected_adj_set->begin()
        );
    }
    return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
        adj_list_owner_graph_pointer,
        adj_list_owner_graph_edges_type,
        adj_list_common_begin_point_vertex_container_pointer,
        adj_list_edges_type_selection,
        graphdom::edge_type::directed,
        directed_adj_set->begin()
    );
}

template <typename VertexType>
template <typename VertexContainerPointerType>
template <typename K>
constexpr typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>
graphdom::graph<VertexType>::base_adj_list<VertexContainerPointerType>::internal_end() const {
    static_assert(
        std::is_same< K , graphdom::graph<VertexType>::vertex_container* >::value ||
        std::is_same< K , const graphdom::graph<VertexType>::vertex_container* >::value
    );
    auto* const undirected_adj_set = get_adj_set_if_accessible<K>(graphdom::edge_type::undirected);
    auto* const directed_adj_set = get_adj_set_if_accessible<K>(graphdom::edge_type::directed);
    if ( ( undirected_adj_set == nullptr ) && ( directed_adj_set == nullptr ) ) {
        return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
            adj_list_owner_graph_pointer,
            adj_list_owner_graph_edges_type,
            adj_list_common_begin_point_vertex_container_pointer,
            adj_list_edges_type_selection,
            ( adj_list_owner_graph_edges_type == undirected ) ? graphdom::edge_type::undirected : graphdom::edge_type::directed
        );
    }
    if ( directed_adj_set != nullptr ) {
        if ( directed_adj_set->empty() && undirected_adj_set != nullptr ) {
            return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
                adj_list_owner_graph_pointer,
                adj_list_owner_graph_edges_type,
                adj_list_common_begin_point_vertex_container_pointer,
                adj_list_edges_type_selection,
                graphdom::edge_type::undirected,
                undirected_adj_set->end()
            );
        }
        return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
            adj_list_owner_graph_pointer,
            adj_list_owner_graph_edges_type,
            adj_list_common_begin_point_vertex_container_pointer,
            adj_list_edges_type_selection,
            graphdom::edge_type::directed,
            directed_adj_set->end()
        );
    }
    return typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>(
        adj_list_owner_graph_pointer,
        adj_list_owner_graph_edges_type,
        adj_list_common_begin_point_vertex_container_pointer,
        adj_list_edges_type_selection,
        graphdom::edge_type::undirected,
        undirected_adj_set->end()
    );
}

template <typename VertexType>
template <typename VertexContainerPointerType>
template <typename K>
constexpr typename graphdom::graph<VertexType>::template adj_set<K>*
graphdom::graph<VertexType>::base_adj_list<VertexContainerPointerType>::get_adj_set_if_accessible(const graphdom::edge_type edge_type) const {
    static_assert(
        std::is_same< K , graphdom::graph<VertexType>::vertex_container* >::value ||
        std::is_same< K , const graphdom::graph<VertexType>::vertex_container* >::value
        );
    auto* const undirected_adj =
        ( adj_list_owner_graph_edges_type == mixed ) ?
        &( ( static_cast< const typename graphdom::graph<VertexType>::mixed_graph_vertex_container<K>* >( adj_list_common_begin_point_vertex_container_pointer ) )->undirected_adj )
        :
        (
            ( adj_list_owner_graph_edges_type == undirected ) ?
            &( ( static_cast< const typename graphdom::graph<VertexType>::non_mixed_graph_vertex_container<K>* >( adj_list_common_begin_point_vertex_container_pointer ) )->adj )
            :
            nullptr
        );
    auto* const directed_adj =
        ( adj_list_owner_graph_edges_type == mixed ) ?
        &( ( static_cast< const typename graphdom::graph<VertexType>::mixed_graph_vertex_container<K>* >( adj_list_common_begin_point_vertex_container_pointer ) )->directed_adj )
        :
        (
            ( adj_list_owner_graph_edges_type == directed ) ?
            &( ( static_cast< const typename graphdom::graph<VertexType>::non_mixed_graph_vertex_container<K>* >( adj_list_common_begin_point_vertex_container_pointer ) )->adj )
            :
            nullptr
        );
    if ( edge_type == edge_type::undirected ) {
        if ( adj_list_edges_type_selection != directed_edges ) {
            return undirected_adj;
        }
        return nullptr;
    }
    if ( adj_list_edges_type_selection != undirected_edges ) {
        return directed_adj;
    }
    return nullptr;
}

#endif //GRAPHDOM_BASE_ADJ_LIST_IMPL_H