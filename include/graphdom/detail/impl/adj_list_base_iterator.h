#ifndef GRAPHDOM_ADJ_LIST_BASE_ITERATOR_IMPL_H
#define GRAPHDOM_ADJ_LIST_BASE_ITERATOR_IMPL_H

#include <stdexcept>
#include <variant>

#include "../adj_list_base_iterator.h"

template<typename VertexType>
template<typename VertexContainerPointerType>
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::adj_list_base_iterator() :
iterator_owner_graph(nullptr),
iterator_owner_graph_edges_type(mixed),
edge_begin_point_vertex_container(nullptr),
edges_type_restriction(none),
inner_iterator_edge_current_type(undirected),
inner_iterator( special_begin_end_indicator() )
{}

template<typename VertexType>
template<typename VertexContainerPointerType>
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::adj_list_base_iterator(
    const graphdom::graph<VertexType>* const iterator_owner_pointer,
    const typename graphdom::graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    const VertexContainerPointerType edge_begin_point_vertex_container,
    const typename graphdom::graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type) :
iterator_owner_graph(iterator_owner_pointer),
iterator_owner_graph_edges_type(iterator_owner_graph_edges_type),
edge_begin_point_vertex_container(edge_begin_point_vertex_container),
edges_type_restriction(edges_type_restriction),
inner_iterator_edge_current_type(inner_iterator_edge_current_type),
inner_iterator( special_begin_end_indicator() ){}

template<typename VertexType>
template<typename VertexContainerPointerType>
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::adj_list_base_iterator(
    const graphdom::graph<VertexType>* const iterator_owner_pointer,
    const typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    const VertexContainerPointerType edge_begin_point_vertex_container,
    const typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type,
    const typename graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator& inner_iterator) :
iterator_owner_graph(iterator_owner_pointer),
iterator_owner_graph_edges_type(iterator_owner_graph_edges_type),
edge_begin_point_vertex_container(edge_begin_point_vertex_container),
edges_type_restriction(edges_type_restriction),
inner_iterator_edge_current_type(inner_iterator_edge_current_type),
inner_iterator( inner_iterator ){}

template<typename VertexType>
template<typename VertexContainerPointerType>
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::adj_list_base_iterator(
    const graphdom::graph<VertexType>* const iterator_owner_pointer,
    const typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
    const VertexContainerPointerType edge_begin_point_vertex_container,
    const typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
    const graphdom::edge_type inner_iterator_edge_current_type,
    const typename graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator& inner_iterator) :
iterator_owner_graph(iterator_owner_pointer),
iterator_owner_graph_edges_type(iterator_owner_graph_edges_type),
edge_begin_point_vertex_container(edge_begin_point_vertex_container),
edges_type_restriction(edges_type_restriction),
inner_iterator_edge_current_type(inner_iterator_edge_current_type),
inner_iterator( inner_iterator ){}

template<typename VertexType>
template<typename VertexContainerPointerType>
template<typename K>
constexpr bool graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::operator==(
    const adj_list_base_iterator<K>& other_iterator) const {
    if ( inner_iterator_edge_current_type != other_iterator.inner_iterator_edge_current_type ) {
        return false;
    }
    if ( std::holds_alternative< special_begin_end_indicator >( inner_iterator ) ) {
        if ( std::holds_alternative< special_begin_end_indicator >( other_iterator.inner_iterator ) ) {
            return true;
        }
        return false;
    }
    else if ( std::holds_alternative< typename graph<VertexType>::adj_set<graph<VertexType>::vertex_container*>::iterator >( inner_iterator ) ) {
        if ( ! std::holds_alternative< typename graph<VertexType>::adj_set<graph<VertexType>::vertex_container*>::iterator >( other_iterator.inner_iterator ) ) {
            return false;
        }
        return std::get< typename graph<VertexType>::adj_set<graph<VertexType>::vertex_container*>::iterator >( inner_iterator ) ==
            std::get< typename graph<VertexType>::adj_set<graph<VertexType>::vertex_container*>::iterator >( other_iterator.inner_iterator );
    }
    else {
        if ( ! std::holds_alternative< typename graph<VertexType>::adj_set<const graph<VertexType>::vertex_container*>::iterator >( other_iterator.inner_iterator ) ) {
            return false;
        }
        return std::get< typename graph<VertexType>::adj_set<const graph<VertexType>::vertex_container*>::iterator >( inner_iterator ) ==
            std::get< typename graph<VertexType>::adj_set<const graph<VertexType>::vertex_container*>::iterator >( other_iterator.inner_iterator );
    }
}

template<typename VertexType>
template<typename VertexContainerPointerType>
template<typename K>
constexpr bool graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::operator!=(
    const adj_list_base_iterator<K>& other_iterator) const {
    return !( (*this) == other_iterator );
}

template<typename VertexType>
template<typename VertexContainerPointerType>
constexpr graphdom::edge_type graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::edge_type() const {
    return inner_iterator_edge_current_type;
}

template<typename VertexType>
template<typename VertexContainerPointerType>
constexpr typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>&
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::internal_single_increment() {
    if ( std::holds_alternative< typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator >( inner_iterator ) ) {
        return specialized_internal_single_increment< graphdom::graph<VertexType>::vertex_container* >();
    }
    if ( std::holds_alternative< typename graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator >( inner_iterator ) ) {
        return specialized_internal_single_increment< const graphdom::graph<VertexType>::vertex_container* >();
    }
    throw std::runtime_error("adj_list overflow"); //TODO: write a better message
}

template<typename VertexType>
template<typename VertexContainerPointerType>
template<typename K>
constexpr typename graphdom::graph<VertexType>::template adj_list_base_iterator<VertexContainerPointerType>&
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::specialized_internal_single_increment() {
    static_assert(
        std::is_same< K , graphdom::graph<VertexType>::vertex_container* >::value ||
        std::is_same< K , const graphdom::graph<VertexType>::vertex_container* >::value
        ,
        "The typename 'K' of 'graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::specialized_internal_next<K>()' method must be a pointer to graphdom::graph<VertexType>::vertex_container"
    );
    auto& specialized_inner_iterator = std::get< typename graphdom::graph<VertexType>::adj_set<K>::iterator >( inner_iterator );
    if ( inner_iterator_edge_current_type == graphdom::edge_type::undirected ) {
        if ( std::next( specialized_inner_iterator ) == ( ( get_adj_set_if_accessible<K>(graphdom::edge_type::undirected) )->end() ) ) {
            auto* const adj_set_directed = get_adj_set_if_accessible<K>(graphdom::edge_type::directed);
            if ( adj_set_directed != nullptr ) {
                if ( ! adj_set_directed->empty() ) {
                    inner_iterator = adj_set_directed->begin();
                    inner_iterator_edge_current_type = graphdom::edge_type::directed;
                    return *this;
                }
            }
        }
        ++specialized_inner_iterator;
        return *this;
    }
    ++specialized_inner_iterator;
    return *this;
}

template<typename VertexType>
template<typename VertexContainerPointerType>
template<typename K>
constexpr typename graphdom::graph<VertexType>::template adj_set<K>*
graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::get_adj_set_if_accessible(const graphdom::edge_type edge_type) const {
    static_assert(
        std::is_same< K , graphdom::graph<VertexType>::vertex_container* >::value ||
        std::is_same< K , const graphdom::graph<VertexType>::vertex_container* >::value
        ,
        "The typename 'K' of 'graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>::get_adj_list<K>(graphdom::edge_type edge_type)' method must be a pointer to graphdom::graph<VertexType>::vertex_container"
    );
    auto* const undirected_adj =
        ( iterator_owner_graph_edges_type == mixed ) ?
        &( ( static_cast< const typename graphdom::graph<VertexType>::mixed_graph_vertex_container<K>* >( edge_begin_point_vertex_container ) )->undirected_adj )
        :
        (
            ( iterator_owner_graph_edges_type == undirected ) ?
            &( ( static_cast< const typename graphdom::graph<VertexType>::non_mixed_graph_vertex_container<K>* >( edge_begin_point_vertex_container ) )->adj )
            :
            nullptr
        );
    auto* const directed_adj =
        ( iterator_owner_graph_edges_type == mixed ) ?
        &( ( static_cast< const typename graphdom::graph<VertexType>::mixed_graph_vertex_container<K>* >( edge_begin_point_vertex_container ) )->directed_adj )
        :
        (
            ( iterator_owner_graph_edges_type == directed ) ?
            &( ( static_cast< const typename graphdom::graph<VertexType>::non_mixed_graph_vertex_container<K>* >( edge_begin_point_vertex_container ) )->adj )
            :
            nullptr
        );
    if ( edge_type ==  edge_type::undirected ) {
        if ( edges_type_restriction != directed_edges ) {
            return undirected_adj;
        }
        return nullptr;
    }
    if ( edges_type_restriction != undirected_edges ) {
        return directed_adj;
    }
    return nullptr;
}

#endif //GRAPHDOM_ADJ_LIST_BASE_ITERATOR_IMPL_H