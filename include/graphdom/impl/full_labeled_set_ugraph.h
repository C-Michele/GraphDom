/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_FULL_LABELED_SET_UGRAPH_IMPL_H
#define GRAPHDOM_FULL_LABELED_SET_UGRAPH_IMPL_H

#include "../full_labeled_set_ugraph.h"

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(const Compare& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(const Compare& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(const Compare& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(const Compare& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(Compare&& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(Compare&& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(Compare&& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_ugraph(Compare&& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
~full_labeled_set_ugraph() {
    for (auto ugraph_vertices_itr = vertices.begin(); ugraph_vertices_itr != vertices.end(); ++ugraph_vertices_itr) {
        auto& ugv_itr_vertex_container = *ugraph_vertices_itr;
        auto& ugv_itr_vc_adj = ugv_itr_vertex_container.adj;
        for (auto edge_endpoint_to_deallocate = ugv_itr_vc_adj.begin(); edge_endpoint_to_deallocate != ugv_itr_vc_adj.end(); ++edge_endpoint_to_deallocate) {
            safe_edge_endpoint_deallocation(*edge_endpoint_to_deallocate); // This is to avoid memory leaks
        }
        ugv_itr_vc_adj.clear();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::size_t graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::order() const {
    return vertices.size();
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const VertexLabelType& graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) const {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return vertex_container_ptr->vertex_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const EdgeLabelType& graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
const typename graph<VertexType>::adj_list_const_iterator& edge) const {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return
    *(
        (
            *(
                static_cast<edge_endpoint*>(
                    *( graphdom::set_graph<VertexType>::get_inner_iterator( edge ) )
                )
            )
        ).edge_label_ptr
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_vertex(
    const typename graphdom::graph<VertexType>::vertex_const_handle& const_vertex_ptr) {
    if ( graphdom::graph<VertexType>::get_owner_graph(const_vertex_ptr) == this ) {
        const auto* const vertex_container_to_erase_ptr =
            static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container(const_vertex_ptr) );
        if ( vertex_container_to_erase_ptr != nullptr ) {
            const auto vertex_container_to_erase_found_vertices_itr = vertices.find( *vertex_container_to_erase_ptr );
            auto& vertex_container_to_erase_adj = ( *vertex_container_to_erase_found_vertices_itr ).adj;
            for (auto vertex_container_to_erase_adj_itr = vertex_container_to_erase_adj.begin();
                vertex_container_to_erase_adj_itr != vertex_container_to_erase_adj.end();
                ++vertex_container_to_erase_adj_itr) {
                const auto& edge_endpoint_vertex_container =
                    *(
                        static_cast< const vertex_container* >(
                            (
                                *(
                                    *(
                                        vertex_container_to_erase_adj_itr
                                    )
                                )
                            ).vertex_container_ptr
                        )
                    );
                if ( ( &edge_endpoint_vertex_container ) != vertex_container_to_erase_ptr ) { //The edge could be a loop
                    auto& edge_endpoint_vertex_container_adj = edge_endpoint_vertex_container.adj;
                    const auto vertex_container_to_erase_founded_in_edge_endpoint_vertex_container_adj =
                        edge_endpoint_vertex_container_adj.find( vertex_container_to_erase_ptr );
                    safe_edge_endpoint_deallocation( *vertex_container_to_erase_founded_in_edge_endpoint_vertex_container_adj );
                    edge_endpoint_vertex_container_adj.erase( vertex_container_to_erase_founded_in_edge_endpoint_vertex_container_adj );
                }
                safe_edge_endpoint_deallocation( *vertex_container_to_erase_adj_itr );
            }
            vertices.erase(vertex_container_to_erase_found_vertices_itr);
        }
        //TODO:: Evaluate a possible exception throw HERE
    }
    //TODO:: Evaluate a possible exception throw HERE
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_edge(
    const typename graph<VertexType>::adj_list_const_iterator& edge_itr) {
    if ( graphdom::graph<VertexType>::get_owner_graph(edge_itr) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const edge_itr_begin_point = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_begin_point( edge_itr ) );
    auto inner_iterator_of_begin_point_adj = graphdom::set_graph<VertexType>::get_inner_iterator( edge_itr );
    auto const edge_itr_endpoint = static_cast< const vertex_container* >( ( *( *inner_iterator_of_begin_point_adj ) ).vertex_container_ptr );
    if ( edge_itr_begin_point != edge_itr_endpoint ) { //The edge could be a loop
        auto inner_iterator_of_end_point_adj = ( (*edge_itr_endpoint).adj ).find( edge_itr_begin_point );
        safe_edge_endpoint_deallocation(*inner_iterator_of_end_point_adj);
        ( (*edge_itr_endpoint).adj ).erase( inner_iterator_of_end_point_adj );
    }
    safe_edge_endpoint_deallocation(*inner_iterator_of_begin_point_adj);
    return graphdom::set_graph<VertexType>::adj_list_iterator_factory(
        this,
        edge_itr_begin_point,
        undirected,
        ( (*edge_itr_begin_point).adj ).erase( inner_iterator_of_begin_point_adj )
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
VertexLabelType& graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return const_cast< VertexLabelType& >( (*vertex_container_ptr).vertex_label );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle,bool>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
    const VertexType& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        vertex_to_insert,
        vertex_label_to_insert
    );
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *(inner_insertion_result.first),
            graphdom::edge_type::undirected
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle,bool>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
const VertexType& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    const auto lower_bound = vertices.lower_bound(vertex_to_insert);
    if ( lower_bound == vertices.cend()  ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, vertex_to_insert, std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::undirected
            ),
            true
        );
    }
    if ( ( vertices.key_comp() )( vertex_to_insert, *lower_bound ) ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, vertex_to_insert, std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::undirected
            ),
            true
        );
    }
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *( lower_bound ),
            graphdom::edge_type::undirected
        ),
        false
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle,bool>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    const auto lower_bound = vertices.lower_bound(vertex_to_insert);
    if ( lower_bound == vertices.cend()  ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), vertex_label_to_insert) ),
                graphdom::edge_type::undirected
            ),
            true
        );
    }
    if ( ( vertices.key_comp() )( vertex_to_insert, *lower_bound ) ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), vertex_label_to_insert) ),
                graphdom::edge_type::undirected
            ),
            true
        );
    }
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *( lower_bound ),
            graphdom::edge_type::undirected
        ),
        false
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle,bool>
graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    const auto lower_bound = vertices.lower_bound(vertex_to_insert);
    if ( lower_bound == vertices.cend()  ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::undirected
            ),
            true
        );
    }
    if ( ( vertices.key_comp() )( vertex_to_insert, *lower_bound ) ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::undirected
            ),
            true
        );
    }
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *( lower_bound ),
            graphdom::edge_type::undirected
        ),
        false
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
EdgeLabelType& graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
    const typename graph<VertexType>::adj_list_const_iterator& edge ) {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return
    *(
        (
            *(
                static_cast<edge_endpoint*>(
                    *( graphdom::set_graph<VertexType>::get_inner_iterator( edge ) )
                )
            )
        ).edge_label_ptr
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& first_endpoint,
    const typename graph<VertexType>::vertex_const_handle& second_endpoint,
    const EdgeLabelType& edge_label) {
    if (
        graphdom::graph<VertexType>::get_owner_graph( first_endpoint ) != this ||
        graphdom::graph<VertexType>::get_owner_graph( second_endpoint ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( first_endpoint ) );
    auto const end_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( second_endpoint ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_begin_point_adj( new edge_endpoint( end_point_vertex_container , edge_label ) );
    const auto inner_insertion_result_in_begin_point_adj = ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_begin_point_adj.get() );
    if ( inner_insertion_result_in_begin_point_adj.second ) {
        edge_endpoint_to_insert_in_begin_point_adj.release();
        if ( begin_point_vertex_container != end_point_vertex_container ) { //The edge could be a loop
            std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_end_point_adj(
                new edge_endpoint(
                    begin_point_vertex_container ,
                    ( static_cast< edge_endpoint* >( *( inner_insertion_result_in_begin_point_adj.first ) ) )->edge_label_ptr
                )
            );
            const auto inner_insertion_result_in_end_point_adj = ( ( end_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_end_point_adj.get() ) ).second;
            if ( inner_insertion_result_in_end_point_adj ) {
                edge_endpoint_to_insert_in_end_point_adj.release();
            }
            else {
                safe_edge_endpoint_deallocation( *( inner_insertion_result_in_begin_point_adj.first ) );
                ( begin_point_vertex_container->adj ).erase( inner_insertion_result_in_begin_point_adj.first );
            }
        }
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& first_endpoint,
    const typename graph<VertexType>::vertex_const_handle& second_endpoint,
    EdgeLabelType&& edge_label) {
    if (
        graphdom::graph<VertexType>::get_owner_graph( first_endpoint ) != this ||
        graphdom::graph<VertexType>::get_owner_graph( second_endpoint ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( first_endpoint ) );
    auto const end_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( second_endpoint ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto lower_bound = ( begin_point_vertex_container->adj ).lower_bound( end_point_vertex_container );
    if ( lower_bound == ( begin_point_vertex_container->adj ).cend()  ) {
        const auto first_insertion_itr = ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label) ) );
        if ( begin_point_vertex_container != end_point_vertex_container ) { //The edge could be a loop
            ( end_point_vertex_container->adj ).emplace( new edge_endpoint( begin_point_vertex_container, static_cast< const edge_endpoint* >( *first_insertion_itr )->edge_label_ptr ) );
        }
    }
    else {
        if ( ( ( begin_point_vertex_container->adj ).key_comp() )( end_point_vertex_container, *lower_bound ) ) {
            const auto first_insertion_itr = ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label) ) );
            if ( begin_point_vertex_container != end_point_vertex_container ) { //The edge could be a loop
                ( end_point_vertex_container->adj ).emplace( new edge_endpoint( begin_point_vertex_container, static_cast< const edge_endpoint* >( *first_insertion_itr )->edge_label_ptr ) );
            }
        }
    }
    /*
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_begin_point_adj( new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
    const auto inner_insertion_result_in_begin_point_adj = ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_begin_point_adj.get() );
    if ( inner_insertion_result_in_begin_point_adj.second ) {
        edge_endpoint_to_insert_in_begin_point_adj.release();
        if ( begin_point_vertex_container != end_point_vertex_container ) { //The edge could be a loop
            std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_end_point_adj(
                new edge_endpoint(
                    begin_point_vertex_container ,
                    ( static_cast< edge_endpoint* >( *( inner_insertion_result_in_begin_point_adj.first ) ) )->edge_label_ptr
                )
            );
            const auto inner_insertion_result_in_end_point_adj = ( ( end_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_end_point_adj.get() ) ).second;
            if ( inner_insertion_result_in_end_point_adj ) {
                edge_endpoint_to_insert_in_end_point_adj.release();
            }
            else {
                safe_edge_endpoint_deallocation( *( inner_insertion_result_in_begin_point_adj.first ) );
                ( begin_point_vertex_container->adj ).erase( inner_insertion_result_in_begin_point_adj.first );
            }
        }
    }
    */
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
safe_edge_endpoint_deallocation(
    typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>* ee_ptr) {
    delete static_cast<edge_endpoint*>(ee_ptr);
}

#endif //GRAPHDOM_FULL_LABELED_SET_UGRAPH_IMPL_H