/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_FULL_LABELED_SET_DIGRAPH_IMPL_H
#define GRAPHDOM_FULL_LABELED_SET_DIGRAPH_IMPL_H

#include "../full_labeled_set_digraph.h"

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(const Compare& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(const Compare& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(const Compare& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(const Compare& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(Compare&& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(Compare&& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(Compare&& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_digraph(Compare&& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_vertices_set_compare(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::~full_labeled_set_digraph() {
    for (auto digraph_vertices_itr = vertices.begin(); digraph_vertices_itr != vertices.end(); ++digraph_vertices_itr) {
        auto& dv_itr_vertex_container = *digraph_vertices_itr;
        auto& dv_itr_vc_adj = dv_itr_vertex_container.adj;
        for (auto edge_endpoint_to_deallocate = dv_itr_vc_adj.begin(); edge_endpoint_to_deallocate != dv_itr_vc_adj.end(); ++edge_endpoint_to_deallocate) {
            safe_edge_endpoint_deallocation(*edge_endpoint_to_deallocate); // This is to avoid memory leaks
        }
        dv_itr_vc_adj.clear();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::size_t graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::order() const {
    return vertices.size();
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const VertexLabelType& graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) const {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return vertex_container_ptr->vertex_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const EdgeLabelType& graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
const typename graph<VertexType>::adj_list_const_iterator& edge ) const {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return (
        *(
            static_cast<edge_endpoint*>(
                *( graphdom::set_graph<VertexType>::get_inner_iterator( edge ) )
            )
        )
    ).edge_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_vertex(
    const typename graphdom::graph<VertexType>::vertex_const_handle& const_vertex_ptr) {
    if ( graphdom::graph<VertexType>::get_owner_graph(const_vertex_ptr) == this ) {
        const auto vertex_container_to_erase_ptr = graphdom::graph<VertexType>::get_vertex_container(const_vertex_ptr);
        if ( vertex_container_to_erase_ptr != nullptr ) {
            auto vertex_container_to_erase_found_vertices_itr = vertices.end();
            for (auto digraph_vertices_itr = vertices.begin(); digraph_vertices_itr != vertices.end(); ++digraph_vertices_itr) {
                auto& digraph_vertices_itr_vertex_container = *digraph_vertices_itr;
                if ( &digraph_vertices_itr_vertex_container == vertex_container_to_erase_ptr ) {
                    vertex_container_to_erase_found_vertices_itr = digraph_vertices_itr;
                }
                auto& digraph_vertices_itr_vertex_container_adj = digraph_vertices_itr_vertex_container.adj;
                auto itr_vertex_container_adj_found_result_itr = digraph_vertices_itr_vertex_container_adj.find(vertex_container_to_erase_ptr);
                if (itr_vertex_container_adj_found_result_itr != digraph_vertices_itr_vertex_container_adj.end()) {
                    safe_edge_endpoint_deallocation(*itr_vertex_container_adj_found_result_itr); // This is to avoid memory leaks
                    digraph_vertices_itr_vertex_container_adj.erase(itr_vertex_container_adj_found_result_itr);
                }
            }
            if ( vertex_container_to_erase_found_vertices_itr != vertices.end() ) {
                auto& vertex_container_to_erase = *vertex_container_to_erase_found_vertices_itr;
                auto& vertex_container_to_erase_adj = vertex_container_to_erase.adj;
                for(auto vertex_container_to_erase_adj_itr = vertex_container_to_erase_adj.begin();
                    vertex_container_to_erase_adj_itr != vertex_container_to_erase_adj.end();) {
                    safe_edge_endpoint_deallocation(*vertex_container_to_erase_adj_itr); // This is to avoid memory leaks
                    vertex_container_to_erase_adj_itr = vertex_container_to_erase_adj.erase(vertex_container_to_erase_adj_itr);
                }
                vertices.erase(vertex_container_to_erase_found_vertices_itr);
            }
            //TODO:: Evaluate a possible exception throw HERE
        }
        //TODO:: Evaluate a possible exception throw HERE
    }
    //TODO:: Evaluate a possible exception throw HERE
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_edge(
    const typename graph<VertexType>::adj_list_const_iterator& edge_itr) {
    if ( graphdom::graph<VertexType>::get_owner_graph(edge_itr) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const edge_itr_begin_point = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_begin_point(edge_itr) );
    auto edge_itr_inner_iterator = graphdom::set_graph<VertexType>::get_inner_iterator( edge_itr );
    auto const edge_itr_endpoint = *edge_itr_inner_iterator;
    safe_edge_endpoint_deallocation(edge_itr_endpoint);
    return graphdom::set_graph<VertexType>::adj_list_iterator_factory(
        this,
        edge_itr_begin_point,
        directed,
        ( edge_itr_begin_point->adj ).erase( edge_itr_inner_iterator )
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
VertexLabelType& graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return const_cast< VertexLabelType& >( (*vertex_container_ptr).vertex_label );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
    const VertexType& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        vertex_to_insert,
        vertex_label_to_insert
    );
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *(inner_insertion_result.first),
            graphdom::edge_type::directed
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
const VertexType& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    const auto lower_bound = vertices.lower_bound(vertex_to_insert);
    if ( lower_bound == vertices.cend()  ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, vertex_to_insert, std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::directed
            ),
            true
        );
    }
    if ( ( vertices.key_comp() )( vertex_to_insert, *lower_bound ) ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, vertex_to_insert, std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::directed
            ),
            true
        );
    }
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *( lower_bound ),
            graphdom::edge_type::directed
        ),
        false
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle,bool>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    const auto lower_bound = vertices.lower_bound(vertex_to_insert);
    if ( lower_bound == vertices.cend()  ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), vertex_label_to_insert) ),
                graphdom::edge_type::directed
            ),
            true
        );
    }
    if ( ( vertices.key_comp() )( vertex_to_insert, *lower_bound ) ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), vertex_label_to_insert) ),
                graphdom::edge_type::directed
            ),
            true
        );
    }
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *( lower_bound ),
            graphdom::edge_type::directed
        ),
        false
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>
graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    const auto lower_bound = vertices.lower_bound(vertex_to_insert);
    if ( lower_bound == vertices.cend()  ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::directed
            ),
            true
        );
    }
    if ( ( vertices.key_comp() )( vertex_to_insert, *lower_bound ) ) {
        return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
            graphdom::graph<VertexType>::vertex_handle_factory(
                this,
                *( vertices.emplace_hint(lower_bound, std::move(vertex_to_insert), std::move(vertex_label_to_insert)) ),
                graphdom::edge_type::directed
            ),
            true
        );
    }
    return std::pair<typename graphdom::graph<VertexType>::vertex_handle, bool>(
        graphdom::graph<VertexType>::vertex_handle_factory(
            this,
            *( lower_bound ),
            graphdom::edge_type::directed
        ),
        false
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
EdgeLabelType& graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
    const typename graph<VertexType>::adj_list_const_iterator& edge ) {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return (
        *(
            static_cast<edge_endpoint*>(
                *( graphdom::set_graph<VertexType>::get_inner_iterator( edge ) )
            )
        )
    ).edge_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
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
    auto const end_point_vertex_container = graphdom::graph<VertexType>::get_vertex_container( head );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert( new edge_endpoint( end_point_vertex_container , edge_label ) );
    const auto inner_insertion_result = ( ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert.get() ) ).second;
    if ( inner_insertion_result ) {
        edge_endpoint_to_insert.release();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
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
    auto const end_point_vertex_container = graphdom::graph<VertexType>::get_vertex_container( head );
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
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert( new edge_endpoint( end_point_vertex_container , std::move( edge_label_to_insert ) ) );
    const auto inner_insertion_result = ( ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert.get() ) ).second;
    if ( inner_insertion_result ) {
        edge_endpoint_to_insert.release();
    }
    */
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void graphdom::full_labeled_set_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
safe_edge_endpoint_deallocation(
    typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>* ee_ptr) {
    delete static_cast<edge_endpoint*>(ee_ptr);
}

#endif //GRAPHDOM_FULL_LABELED_SET_DIGRAPH_IMPL_H