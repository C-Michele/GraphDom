/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_FULL_LABELED_MULTISET_DIGRAPH_IMPL_H
#define GRAPHDOM_FULL_LABELED_MULTISET_DIGRAPH_IMPL_H

#include "../full_labeled_multiset_digraph.h"

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::
full_labeled_multiset_digraph() :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>(),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>(),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::
full_labeled_multiset_digraph(const VertexLabellerType& v_lab, const EdgeLabellerType& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>(e_lab),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::
full_labeled_multiset_digraph(const VertexLabellerType& v_lab, EdgeLabellerType&& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>(std::move(e_lab)),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::
full_labeled_multiset_digraph(VertexLabellerType&& v_lab, const EdgeLabellerType& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>(e_lab),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::
full_labeled_multiset_digraph(VertexLabellerType&& v_lab, EdgeLabellerType&& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>(std::move(e_lab)),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::~full_labeled_multiset_digraph() {
    while ( ! vertices.empty() ) {
        auto& vertex_to_erase = vertices.front();
        auto& vertex_to_erase_adj = vertex_to_erase.adj;
        for (auto edge_endpoint_to_deallocate = vertex_to_erase_adj.begin();
            edge_endpoint_to_deallocate != vertex_to_erase_adj.end();
            ++edge_endpoint_to_deallocate) {
            safe_edge_endpoint_deallocation(*edge_endpoint_to_deallocate); // This is to avoid memory leaks
        }
        vertices.pop_front();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
std::size_t graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::order() const {
    return number_of_vertices_inserted;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
const VertexLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) const {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return vertex_container_ptr->vertex_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
const EdgeLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::get_edge_label(
    const typename graph<VertexType>::adj_list_const_iterator& edge) const {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return (
        *(
            static_cast<edge_endpoint*>(
                *( graphdom::multiset_graph<VertexType>::get_inner_iterator( edge ) )
            )
        )
    ).edge_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::erase_vertex(
    const typename graphdom::graph<VertexType>::vertex_const_handle& vertex) {
    if( graphdom::graph<VertexType>::get_owner_graph(vertex) == this ) {
        const auto vertex_container_to_erase_ptr = graphdom::graph<VertexType>::get_vertex_container(vertex);
        if ( vertex_container_to_erase_ptr != nullptr ) {
            auto before_vertex_container_to_erase_found_vertices_itr = vertices.end();
            for(auto vertices_itr = vertices.before_begin(); vertices_itr != vertices.end(); ++vertices_itr) {
                auto vertices_itr_next = std::next(vertices_itr);
                if( vertices_itr_next != vertices.end() ){
                    if( (&(*vertices_itr_next)) == vertex_container_to_erase_ptr ){
                        before_vertex_container_to_erase_found_vertices_itr = vertices_itr;
                    }
                    auto& vertices_itr_next_vertex_container = *vertices_itr_next;
                    auto& vertices_itr_next_vertex_container_adj = vertices_itr_next_vertex_container.adj;
                    auto vertices_itr_next_vertex_container_adj_found_result_itr = vertices_itr_next_vertex_container_adj.find(vertex_container_to_erase_ptr);
                    if ( vertices_itr_next_vertex_container_adj_found_result_itr != vertices_itr_next_vertex_container_adj.end() ) {
                        safe_edge_endpoint_deallocation(*vertices_itr_next_vertex_container_adj_found_result_itr); // This is to avoid memory leaks
                        vertices_itr_next_vertex_container_adj.erase(vertices_itr_next_vertex_container_adj_found_result_itr);
                    }
                }
            }
            if ( before_vertex_container_to_erase_found_vertices_itr != vertices.end() ) {
                const auto& vertex_container_to_erase_forward_list_iterator = std::next( before_vertex_container_to_erase_found_vertices_itr );
                auto& adj_to_erase = (*vertex_container_to_erase_forward_list_iterator).adj;
                for (auto adj_to_erase_itr = adj_to_erase.begin(); adj_to_erase_itr != adj_to_erase.end(); ++adj_to_erase_itr) {
                    safe_edge_endpoint_deallocation(*adj_to_erase_itr); // This is to avoid memory leaks
                }
                vertices.erase_after(before_vertex_container_to_erase_found_vertices_itr);
                --number_of_vertices_inserted;
            }
            //TODO:: Evaluate a possible exception throw HERE
        }
        //TODO:: Evaluate a possible exception throw HERE
    }
    //TODO:: Evaluate a possible exception throw HERE
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType, EdgeLabelType, VertexLabellerType, EdgeLabellerType>::erase_edge(
    const typename graph<VertexType>::adj_list_const_iterator& edge_itr) {
    if ( graphdom::graph<VertexType>::get_owner_graph(edge_itr) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const edge_itr_begin_point = const_cast<vertex_container*>( static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_begin_point(edge_itr) ) );
    auto edge_itr_inner_iterator = graphdom::multiset_graph<VertexType>::get_inner_iterator( edge_itr );
    auto const edge_itr_endpoint = *edge_itr_inner_iterator;
    safe_edge_endpoint_deallocation(edge_itr_endpoint);
    return graphdom::multiset_graph<VertexType>::adj_list_iterator_factory(
        this,
        edge_itr_begin_point,
        directed,
        ( edge_itr_begin_point->adj ).erase( edge_itr_inner_iterator )
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
VertexLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return const_cast< VertexLabelType& >( (*vertex_container_ptr).vertex_label );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::insert_vertex(
    const VertexType& v_core, const VertexLabelType& vertex_label) {
    vertices.emplace_front(
        v_core,
        vertex_label
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::insert_vertex(
const VertexType& v_core, VertexLabelType&& vertex_label) {
    vertices.emplace_front(
        v_core,
        std::move(vertex_label)
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::insert_vertex(
VertexType&& v_core, const VertexLabelType& vertex_label) {
    vertices.emplace_front(
        std::move(v_core),
        vertex_label
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::insert_vertex(
VertexType&& v_core, VertexLabelType&& vertex_label) {
    vertices.emplace_front(
        std::move(v_core),
        std::move(vertex_label)
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
EdgeLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::get_edge_label(
    const typename graph<VertexType>::adj_list_const_iterator& edge ) {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return (
        *(
            static_cast<edge_endpoint*>(
                *( graphdom::multiset_graph<VertexType>::get_inner_iterator( edge ) )
            )
        )
    ).edge_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& tail,
    const typename graph<VertexType>::vertex_const_handle& head,
    const EdgeLabelType& edge_label) {
    if (
        graphdom::graph<VertexType>::get_owner_graph( tail ) != this ||
        graphdom::graph<VertexType>::get_owner_graph( head ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( tail ) );
    auto const end_point_vertex_container = const_cast< typename graphdom::graph<VertexType>::vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( head ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert( new edge_endpoint( end_point_vertex_container , edge_label ) );
    const auto inner_insertion_result = ( ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert.get() ) ).second;
    if ( inner_insertion_result ) {
        edge_endpoint_to_insert.release();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& tail,
    const typename graph<VertexType>::vertex_const_handle& head,
    EdgeLabelType&& edge_label) {
        if (
            graphdom::graph<VertexType>::get_owner_graph( tail ) != this ||
            graphdom::graph<VertexType>::get_owner_graph( head ) != this
        ) {
            throw std::runtime_error("Error"); //TODO: write a better message
        }
        auto const begin_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( tail ) );
        auto const end_point_vertex_container = const_cast< typename graphdom::graph<VertexType>::vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( head ) );
        if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
            throw std::runtime_error("Error"); //TODO: write a better message
        }
        const auto lower_bound = ( begin_point_vertex_container->adj ).lower_bound( end_point_vertex_container );
        if ( lower_bound == ( begin_point_vertex_container->adj ).cend()  ) {
            ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label) ) );
        }
        else {
            if ( ( ( begin_point_vertex_container->adj ).key_comp() )( end_point_vertex_container, *lower_bound ) ) {
                ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label) ) );
            }
        }
        /*
        std::unique_ptr< edge_endpoint > edge_endpoint_to_insert( new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
        const auto inner_insertion_result = ( ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert.get() ) ).second;
        if ( inner_insertion_result ) {
            edge_endpoint_to_insert.release();
        }
        */
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename VertexLabellerType, typename EdgeLabellerType>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,VertexLabellerType,EdgeLabellerType>::
safe_edge_endpoint_deallocation(
    typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>* ee_ptr) {
    delete static_cast< edge_endpoint* >( ee_ptr );
}

#endif //GRAPHDOM_FULL_LABELED_MULTISET_DIGRAPH_IMPL_H