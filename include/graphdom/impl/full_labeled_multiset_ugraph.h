#ifndef GRAPHDOM_FULL_LABELED_MULTISET_UGRAPH_IMPL_H
#define GRAPHDOM_FULL_LABELED_MULTISET_UGRAPH_IMPL_H

#include "../full_labeled_multiset_ugraph.h"

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>//TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_ugraph() :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>//TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_ugraph(const T1& v_lab, const T2& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_ugraph(const T1& v_lab, T2&& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_ugraph(T1&& v_lab, const T2& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_ugraph(T1&& v_lab, T2&& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::~full_labeled_multiset_ugraph() {
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

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
std::size_t graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::order() const {
    return number_of_vertices_inserted;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
const VertexLabelType& graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) const {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return vertex_container_ptr->vertex_label;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
const EdgeLabelType& graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_edge_label(
const typename graph<VertexType>::adj_list_const_iterator& edge) const {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return
    *(
        (
            *(
                static_cast<edge_endpoint*>(
                    *( graphdom::multiset_graph<VertexType>::get_inner_iterator( edge ) )
                )
            )
        ).edge_label_ptr
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::erase_vertex(
    const typename graphdom::graph<VertexType>::vertex_const_handle& const_vertex_ptr_to_erase_reference) {
    if( graphdom::graph<VertexType>::get_owner_graph(const_vertex_ptr_to_erase_reference) == this ) {
        const auto vertex_container_to_erase_ptr = graphdom::graph<VertexType>::get_vertex_container(const_vertex_ptr_to_erase_reference);
        if ( vertex_container_to_erase_ptr != nullptr ) {
            for(auto vertices_itr = vertices.before_begin(); vertices_itr != vertices.end(); ++vertices_itr) {
                auto vertices_itr_next = std::next(vertices_itr);
                if( vertices_itr_next != vertices.end() ){
                    if( ( &( *vertices_itr_next ) ) == vertex_container_to_erase_ptr ){
                        auto& vertex_container_to_erase_adj = ( *vertices_itr_next ).adj;
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
                        vertices.erase_after( vertices_itr );
                        --number_of_vertices_inserted;
                        break;
                    }
                }
            }
            //TODO:: Evaluate a possible exception throw HERE
        }
        //TODO:: Evaluate a possible exception throw HERE
    }
    //TODO:: Evaluate a possible exception throw HERE
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::erase_edge(
    const typename graph<VertexType>::adj_list_const_iterator& edge_itr) {
    if ( graphdom::graph<VertexType>::get_owner_graph(edge_itr) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const edge_itr_begin_point = const_cast< vertex_container* >( static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_begin_point(edge_itr) ) );
    auto inner_iterator_of_begin_point_adj = graphdom::multiset_graph<VertexType>::get_inner_iterator( edge_itr );
    auto const edge_itr_endpoint = static_cast< vertex_container* >( ( *( *inner_iterator_of_begin_point_adj ) ).vertex_container_ptr );
    if ( edge_itr_begin_point != edge_itr_endpoint ) { //The edge could be a loop
        auto inner_iterator_of_end_point_adj = ( (*edge_itr_endpoint).adj ).find( edge_itr_begin_point );
        safe_edge_endpoint_deallocation(*inner_iterator_of_end_point_adj);
        ( (*edge_itr_endpoint).adj ).erase( inner_iterator_of_end_point_adj );
    }
    safe_edge_endpoint_deallocation(*inner_iterator_of_begin_point_adj);
    return graphdom::multiset_graph<VertexType>::adj_list_iterator_factory(
        this,
        edge_itr_begin_point,
        undirected,
        ( (*edge_itr_begin_point).adj ).erase( inner_iterator_of_begin_point_adj )
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
VertexLabelType& graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle& vertex) {
    if ( graphdom::graph<VertexType>::get_owner_graph(vertex) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto* const vertex_container_ptr = static_cast< const vertex_container* >( graphdom::graph< VertexType >::get_vertex_container( vertex ) );
    return const_cast< VertexLabelType& >( (*vertex_container_ptr).vertex_label );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
    const VertexType& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    vertices.emplace_front(
        vertex_to_insert,
        vertex_label_to_insert
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::undirected
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
const VertexType& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    vertices.emplace_front(
        vertex_to_insert,
        std::move(vertex_label_to_insert)
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::undirected
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    vertices.emplace_front(
        std::move(vertex_to_insert),
        vertex_label_to_insert
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::undirected
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    vertices.emplace_front(
        std::move(vertex_to_insert),
        std::move(vertex_label_to_insert)
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_handle_factory(
        this,
        vertices.front(),
        graphdom::edge_type::undirected
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
EdgeLabelType& graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_edge_label(
    const typename graph<VertexType>::adj_list_const_iterator& edge ) {
    if ( graphdom::graph<VertexType>::get_owner_graph( edge ) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    return
    *(
        (
            *(
                static_cast<edge_endpoint*>(
                    *( graphdom::multiset_graph<VertexType>::get_inner_iterator( edge ) )
                )
            )
        ).edge_label_ptr
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& begin_point_vertex_ptr,
    const typename graph<VertexType>::vertex_const_handle& end_point_vertex_ptr,
    const EdgeLabelType& edge_label_to_insert) {
    if (
        graphdom::graph<VertexType>::get_owner_graph( begin_point_vertex_ptr ) != this ||
        graphdom::graph<VertexType>::get_owner_graph( end_point_vertex_ptr ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = const_cast< vertex_container* >( static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( begin_point_vertex_ptr ) ) );
    auto const end_point_vertex_container = const_cast< vertex_container* >( static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( end_point_vertex_ptr ) ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_begin_point_adj( new edge_endpoint( end_point_vertex_container , edge_label_to_insert ) );
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

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& begin_point_vertex_ptr,
    const typename graph<VertexType>::vertex_const_handle& end_point_vertex_ptr,
    EdgeLabelType&& edge_label_to_insert) {
    if (
        graphdom::graph<VertexType>::get_owner_graph( begin_point_vertex_ptr ) != this ||
        graphdom::graph<VertexType>::get_owner_graph( end_point_vertex_ptr ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = const_cast< vertex_container* >( static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( begin_point_vertex_ptr ) ) );
    auto const end_point_vertex_container = const_cast< vertex_container* >( static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( end_point_vertex_ptr ) ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    const auto lower_bound = ( begin_point_vertex_container->adj ).lower_bound( end_point_vertex_container );
    if ( lower_bound == ( begin_point_vertex_container->adj ).cend()  ) {
        const auto first_insertion_itr = ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
        if ( begin_point_vertex_container != end_point_vertex_container ) { //The edge could be a loop
            ( end_point_vertex_container->adj ).emplace( new edge_endpoint( begin_point_vertex_container, static_cast< const edge_endpoint* >( *first_insertion_itr )->edge_label_ptr ) );
        }
    }
    else {
        if ( ( ( begin_point_vertex_container->adj ).key_comp() )( end_point_vertex_container, *lower_bound ) ) {
            const auto first_insertion_itr = ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
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

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_ugraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
safe_edge_endpoint_deallocation(
    typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>* ee_ptr) {
    delete static_cast<edge_endpoint*>(ee_ptr);
}

#endif //GRAPHDOM_FULL_LABELED_MULTISET_UGRAPH_IMPL_H