#ifndef GRAPHDOM_MULTISET_GRAPH_IMPL_H
#define GRAPHDOM_MULTISET_GRAPH_IMPL_H

#include "../multiset_graph.h"

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle graphdom::multiset_graph<VertexType>::vertex_handle_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    return typename graphdom::multiset_graph<VertexType>::vertex_handle(
        graph_ptr,
        ( non_mixed_graph_type == graphdom::edge_type::undirected ) ? graphdom::graph<VertexType>::graph_edges_type::undirected : graphdom::graph<VertexType>::graph_edges_type::directed,
        &vertex_container_reference
    );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle graphdom::multiset_graph<VertexType>::vertex_handle_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return typename graphdom::multiset_graph<VertexType>::vertex_handle(
        graph_ptr,
        graphdom::graph<VertexType>::graph_edges_type::mixed,
        &vertex_container_reference
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::multiset_graph<VertexType>::const_vertex_handle_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    const typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    return graphdom::graph<VertexType>::vertex_const_handle(
        graph_ptr,
        ( non_mixed_graph_type == graphdom::edge_type::undirected ) ? graphdom::graph<VertexType>::graph_edges_type::undirected : graphdom::graph<VertexType>::graph_edges_type::directed,
        &vertex_container_reference
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::multiset_graph<VertexType>::const_vertex_handle_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    const typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return graphdom::graph<VertexType>::vertex_const_handle(
        graph_ptr,
        graphdom::graph<VertexType>::graph_edges_type::mixed,
        &vertex_container_reference
    );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::VertexContainerPointerType
graphdom::multiset_graph<VertexType>::get_vertex_container(
    const graphdom::multiset_graph<VertexType>::vertex_handle& ptr) {
    return ptr.vertex_container_pointer;
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_set::const_iterator
graphdom::multiset_graph<VertexType>::get_inner_iterator(
const typename graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    return std::get< typename graph<VertexType>::template adj_set<typename graph<VertexType>::vertex_container*>::iterator >( const_edge_itr.inner_iterator );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::multiset_graph<VertexType>::adj_list_iterator_factory(
    const graphdom::multiset_graph<VertexType>* const edge_multiset_vertex_graph_owner_ptr,
    non_mixed_graph_vertex_container* const edge_begin_point_ptr,
    const graphdom::edge_type edge_multiset_vertex_graph_owner_edges_type,
    const typename adj_set::iterator inner_itr) {
    return typename graphdom::graph<VertexType>::adj_list_iterator(
        edge_multiset_vertex_graph_owner_ptr,
        ( edge_multiset_vertex_graph_owner_edges_type == graphdom::edge_type::undirected ) ?
            graph<VertexType>::graph_edges_type::undirected :
            graph<VertexType>::graph_edges_type::directed,
        edge_begin_point_ptr,
        graph<VertexType>::edges_type_selection_type::none,
        edge_multiset_vertex_graph_owner_edges_type,
        inner_itr
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::multiset_graph<VertexType>::adj_list_iterator_factory(
    const set_graph<VertexType>* const edge_multiset_vertex_graph_owner_ptr,
    mixed_graph_vertex_container* const edge_begin_point_ptr,
    typename adj_set::iterator inner_itr,
    const graphdom::edge_type inner_itr_edge_type,
    const bool inner_itr_is_limited_by_edge_type) {
    return typename graphdom::graph<VertexType>::adj_list_iterator(
        edge_multiset_vertex_graph_owner_ptr,
        graph<VertexType>::graph_edges_type::mixed,
        edge_begin_point_ptr,
        inner_itr_is_limited_by_edge_type ?
            ( ( inner_itr_edge_type == graphdom::edge_type::undirected ) ?
                graph<VertexType>::edges_type_selection_type::undirected_edges :
                graph<VertexType>::edges_type_selection_type::directed_edges ) :
            graph<VertexType>::edges_type_selection_type::none,
        inner_itr_edge_type,
        inner_itr
    );
}

#endif //GRAPHDOM_MULTISET_GRAPH_IMPL_H