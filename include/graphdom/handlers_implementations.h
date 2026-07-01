#ifndef GRAPHDOM_HANDLERS_IMPLEMENTATIONS_H
#define GRAPHDOM_HANDLERS_IMPLEMENTATIONS_H

#include <stdexcept>

#include "graph.h"
#include "handlers_declarations.h"

template<typename VertexType>
graphdom::graph<VertexType>::vertex_handle::vertex_handle(
    const typename graphdom::multiset_graph<VertexType>::vertex_handle& other) :
    vertex_owner(other.vertex_owner),
    vertex_container_ptr(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_handle::operator typename multiset_graph<VertexType>::vertex_handle() const {
    return typename graphdom::multiset_graph<VertexType>::vertex_handle(*this);
}

template<typename VertexType>
const VertexType& graphdom::graph<VertexType>::vertex_handle::operator*() const {
    if ( std::holds_alternative<const graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return std::get<const graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex;
    }
    if ( std::holds_alternative<graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return std::get<graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex;
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
const VertexType* graphdom::graph<VertexType>::vertex_handle::operator->() const {
    if ( std::holds_alternative<const graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return &( std::get<const graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex );
    }
    if ( std::holds_alternative<graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return &( std::get<graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex );
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool graphdom::graph<VertexType>::vertex_handle::operator==(
    const graphdom::graph<VertexType>::vertex_const_handle& other) const {
    if ( std::holds_alternative<const graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return
            ( vertex_owner == other.vertex_owner ) &&
            ( std::get<const graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) == other.graph_vertex_container );
    }
    if ( std::holds_alternative<graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return
            ( vertex_owner == other.vertex_owner ) &&
            ( std::get<graphdom::graph<VertexType>::vertex_container*>( vertex_container_ptr ) == other.graph_vertex_container );
    }
    return ( vertex_owner == other.vertex_owner ) && ( nullptr == other.graph_vertex_container );
}

template<typename VertexType>
bool graphdom::graph<VertexType>::vertex_handle::operator!=(
    const graphdom::graph<VertexType>::vertex_const_handle& other) const {
    return ! ( (*this) == other );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list graphdom::graph<VertexType>::vertex_handle::adj_list() const {
    return graphdom::graph<VertexType>::adj_list(
        vertex_owner,
        vertex_container_ptr,
        edges_type
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list graphdom::graph<VertexType>::vertex_handle::adj_list(
    const graphdom::edge_type selection ) const {
    return graphdom::graph<VertexType>::adj_list(
        vertex_owner,
        vertex_container_ptr,
        edges_type,
        selection
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::graph<VertexType>::vertex_handle::const_adj_list() const {
    if ( std::holds_alternative <std::monostate >( vertex_container_ptr ) ) {
        throw std::runtime_error("Error"); //TODO: write better message
    }
    else if ( std::holds_alternative< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ) ) {
        return graphdom::graph<VertexType>::const_adj_list(
            vertex_owner,
            std::get< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ),
            edges_type
        );
    }
    else {
        return graphdom::graph<VertexType>::const_adj_list(
            vertex_owner,
            std::get< graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ),
            edges_type
        );
    }
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list graphdom::graph<VertexType>::vertex_handle::const_adj_list(
const graphdom::edge_type selection ) const {
    if ( std::holds_alternative< std::monostate >( vertex_container_ptr ) ) {
        throw std::runtime_error("Error"); //TODO: write better message
    }
    else if ( std::holds_alternative< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ) ) {
        return graphdom::graph<VertexType>::const_adj_list(
            vertex_owner,
            std::get< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ),
            edges_type,
            selection
        );
    }
    else {
        return graphdom::graph<VertexType>::const_adj_list(
            vertex_owner,
            std::get< graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ),
            edges_type,
            selection
        );
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_handle::vertex_handle(
    const graphdom::graph<VertexType>* const vo,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vc_ref,
    const graphdom::edge_type non_mixed_graph_type) :
    vertex_owner(vo),
    vertex_container_ptr(&vc_ref) {
    if (non_mixed_graph_type == graphdom::edge_type::undirected) {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_handle::vertex_handle(
    const graphdom::graph<VertexType>* const vo,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vc_ref) :
    vertex_owner(vo),
    vertex_container_ptr(&vc_ref),
    edges_type(graphdom::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(
    const graphdom::graph<VertexType>::vertex_handle& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(nullptr),
    edges_type(other.edges_type) {
    if ( std::holds_alternative< const graphdom::graph<VertexType>::vertex_container* >( other.vertex_container_ptr ) ) {
        graph_vertex_container = std::get< const graphdom::graph<VertexType>::vertex_container* >( other.vertex_container_ptr );
    }
    else if ( std::holds_alternative< graphdom::graph<VertexType>::vertex_container* >( other.vertex_container_ptr ) ) {
        graph_vertex_container = std::get< graphdom::graph<VertexType>::vertex_container* >( other.vertex_container_ptr );
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(
    const typename graphdom::multiset_graph<VertexType>::vertex_handle& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

template<typename VertexType>
const VertexType& graphdom::graph<VertexType>::vertex_const_handle::operator*() const {
    if (graph_vertex_container!=nullptr) {
        return graph_vertex_container->vertex;
    }
    throw std::runtime_error("Impossible to dereference a const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
const VertexType* graphdom::graph<VertexType>::vertex_const_handle::operator->() const {
    if (graph_vertex_container!=nullptr) {
        return &(graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool graphdom::graph<VertexType>::vertex_const_handle::operator==(const vertex_const_handle& other) const {
    return (vertex_owner == other.vertex_owner) && (graph_vertex_container == other.graph_vertex_container);
}

template<typename VertexType>
bool graphdom::graph<VertexType>::vertex_const_handle::operator!=(const vertex_const_handle& other) const {
    return !( (*this)== other );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list
graphdom::graph<VertexType>::vertex_const_handle::adj_list() const {
    return const_adj_list();
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list
graphdom::graph<VertexType>::vertex_const_handle::adj_list(const graphdom::edge_type et) const {
    return const_adj_list(et);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list
graphdom::graph<VertexType>::vertex_const_handle::const_adj_list() const {
    if (vertex_owner!=nullptr) {
        if (graph_vertex_container!=nullptr) {
            return graphdom::graph<VertexType>::const_adj_list(
                vertex_owner,
                graph_vertex_container,
                edges_type
            );
        }
    }
    throw std::runtime_error("Impossible to get const_adj_list from this const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list
graphdom::graph<VertexType>::vertex_const_handle::const_adj_list(const graphdom::edge_type et) const {
    if (vertex_owner!=nullptr) {
        if (graph_vertex_container!=nullptr) {
            return graphdom::graph<VertexType>::const_adj_list(
                vertex_owner,
                graph_vertex_container,
                edges_type,
                et
            );
        }
    }
    throw std::runtime_error("Impossible to get const_adj_list from this const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(
    const graphdom::graph<VertexType>* const vo,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vc_ref,
    graphdom::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const graphdom::graph<VertexType>::vertex_container*>(&vc_ref)) {
    if (non_mixed_graph_type == graphdom::edge_type::undirected) {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(
    const graphdom::graph<VertexType>* const vo,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vc_ref) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const graphdom::graph<VertexType>::vertex_container*>(&vc_ref)),
    edges_type(graphdom::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(
    const graphdom::multiset_graph<VertexType>* const vo ,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<vertex_container*>& vc_ref,
    graphdom::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const graphdom::graph<VertexType>::vertex_container*>(&vc_ref)) {
    if (non_mixed_graph_type == graphdom::edge_type::undirected) {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::vertex_const_handle::vertex_const_handle(
    const multiset_graph<VertexType>* const vo,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<vertex_container*>& vc_ref) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const graphdom::graph<VertexType>::vertex_container*>(&vc_ref)),
    edges_type(graphdom::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::graph<VertexType>::adj_list::begin() const {
    if ( std::holds_alternative< set_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info ) ) {
        auto& set_vertex_graph_vertex_container_info_pair = std::get< set_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info );
        auto& set_vertex_graph_vertex_container = set_vertex_graph_vertex_container_info_pair.first;
        auto& set_vertex_graph_vertex_container_adj_sets_ptr_array = set_vertex_graph_vertex_container_info_pair.second;
        return graphdom::graph<VertexType>::adj_list_iterator(
            vertex_container_graph_owner,
            set_vertex_graph_vertex_container,
            vertex_container_graph_owner_edges_type,
            set_vertex_graph_vertex_container_adj_sets_ptr_array,
            graphdom::graph<VertexType>::begin_or_end::begin
        );
    }
    auto& multiset_vertex_graph_vertex_container_info_pair = std::get< multiset_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info );
    auto& multiset_vertex_graph_vertex_container = multiset_vertex_graph_vertex_container_info_pair.first;
    auto& multiset_vertex_graph_vertex_container_adj_sets_ptr_array = multiset_vertex_graph_vertex_container_info_pair.second;
    return graphdom::graph<VertexType>::adj_list_iterator(
        vertex_container_graph_owner,
        multiset_vertex_graph_vertex_container,
        vertex_container_graph_owner_edges_type,
        multiset_vertex_graph_vertex_container_adj_sets_ptr_array,
        graphdom::graph<VertexType>::begin_or_end::begin
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::graph<VertexType>::adj_list::end() const {
    if ( std::holds_alternative< set_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info ) ) {
        auto& set_vertex_graph_vertex_container_info_pair = std::get< set_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info );
        auto& set_vertex_graph_vertex_container = set_vertex_graph_vertex_container_info_pair.first;
        auto& set_vertex_graph_vertex_container_adj_sets_ptr_array = set_vertex_graph_vertex_container_info_pair.second;
        return graphdom::graph<VertexType>::adj_list_iterator(
            vertex_container_graph_owner,
            set_vertex_graph_vertex_container,
            vertex_container_graph_owner_edges_type,
            set_vertex_graph_vertex_container_adj_sets_ptr_array,
            graphdom::graph<VertexType>::begin_or_end::end
        );
    }
    auto& multiset_vertex_graph_vertex_container_info_pair = std::get< multiset_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info );
    auto& multiset_vertex_graph_vertex_container = multiset_vertex_graph_vertex_container_info_pair.first;
    auto& multiset_vertex_graph_vertex_container_adj_sets_ptr_array = multiset_vertex_graph_vertex_container_info_pair.second;
    return graphdom::graph<VertexType>::adj_list_iterator(
        vertex_container_graph_owner,
        multiset_vertex_graph_vertex_container,
        vertex_container_graph_owner_edges_type,
        multiset_vertex_graph_vertex_container_adj_sets_ptr_array,
        graphdom::graph<VertexType>::begin_or_end::end
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::graph<VertexType>::adj_list::cbegin() const {
    return begin();
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::graph<VertexType>::adj_list::cend() const {
    return end();
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list::adj_list(
    const graphdom::graph<VertexType>* vertex_container_graph_owner_ptr,
    const std::variant<
        std::monostate,
        const graphdom::graph<VertexType>::vertex_container*,
        graphdom::graph<VertexType>::vertex_container*
    >& vertex_container_ptr,
    const graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type) :
    vertex_container_graph_owner(vertex_container_graph_owner_ptr),
    vertex_container_graph_owner_edges_type(vertex_container_graph_owner_edges_type){
    if ( std::holds_alternative< std::monostate >( vertex_container_ptr ) ) {
        throw std::runtime_error("Impossible to create adj_list"); //TODO: write a better message
    }
    if ( std::holds_alternative< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ) ) {
        auto const set_vertex_graph_vertex_container_ptr = std::get< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr );
        graph_type_dependent_vertex_container_info.template emplace< set_vertex_graph_vertex_container_info_type >(
            set_vertex_graph_vertex_container_ptr,
            set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = ( std::get< set_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info ) ).second;
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const set_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( set_vertex_graph_vertex_container_ptr );
            adj_sets_array[undirected] = &( set_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
            adj_sets_array[directed] = &( set_vertex_mixed_graph_vertex_container_ptr->directed_adj );
        }
        else {
            auto const set_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( set_vertex_graph_vertex_container_ptr );
            adj_sets_array[vertex_container_graph_owner_edges_type] = &( set_vertex_non_mixed_graph_vertex_container_ptr->adj );
        }
    }
    else {
        auto const multiset_vertex_graph_vertex_container_ptr = std::get< graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr );
        graph_type_dependent_vertex_container_info.template emplace< multiset_vertex_graph_vertex_container_info_type >(
            multiset_vertex_graph_vertex_container_ptr,
            multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = ( std::get< multiset_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info ) ).second;
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const multiset_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( multiset_vertex_graph_vertex_container_ptr );
            adj_sets_array[undirected] = &( multiset_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
            adj_sets_array[directed] = &( multiset_vertex_mixed_graph_vertex_container_ptr->directed_adj );
        }
        else {
            auto const multiset_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( multiset_vertex_graph_vertex_container_ptr );
            adj_sets_array[vertex_container_graph_owner_edges_type] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list::adj_list(
    const graphdom::graph<VertexType>* const vertex_container_graph_owner_ptr,
    const std::variant<
        std::monostate,
        const graphdom::graph<VertexType>::vertex_container*,
        graphdom::graph<VertexType>::vertex_container*
    >& vertex_container_ptr,
    const graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type,
    const graphdom::edge_type edges_type_selected) :
    vertex_container_graph_owner(vertex_container_graph_owner_ptr),
    vertex_container_graph_owner_edges_type(vertex_container_graph_owner_edges_type){
    if ( std::holds_alternative< std::monostate >( vertex_container_ptr ) ) {
        throw std::runtime_error("Impossible to create adj_list"); //TODO: write a better message
    }
    if ( std::holds_alternative< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr ) ) {
        auto const set_vertex_graph_vertex_container_ptr = std::get< const graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr );
        graph_type_dependent_vertex_container_info.template emplace< set_vertex_graph_vertex_container_info_type >(
            set_vertex_graph_vertex_container_ptr,
            set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = ( std::get< set_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info ) ).second;
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const set_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( set_vertex_graph_vertex_container_ptr );
            switch( edges_type_selected ) {
                case undirected:
                    adj_sets_array[undirected] = &( set_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
                    break;
                case directed:
                    adj_sets_array[directed] = &( set_vertex_mixed_graph_vertex_container_ptr->directed_adj );
                    break;
            }
        }
        else {
            auto const set_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( set_vertex_graph_vertex_container_ptr );
            if ( vertex_container_graph_owner_edges_type == undirected ) {
                if ( edges_type_selected == undirected ) {
                    adj_sets_array[undirected] = &( set_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
            else {
                if ( edges_type_selected == directed ) {
                    adj_sets_array[directed] = &( set_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
        }
    }
    else {
        auto const multiset_vertex_graph_vertex_container_ptr = std::get< graphdom::graph<VertexType>::vertex_container* >( vertex_container_ptr );
        graph_type_dependent_vertex_container_info.template emplace< multiset_vertex_graph_vertex_container_info_type >(
            multiset_vertex_graph_vertex_container_ptr,
            multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = ( std::get< multiset_vertex_graph_vertex_container_info_type >( graph_type_dependent_vertex_container_info ) ).second;
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const multiset_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( multiset_vertex_graph_vertex_container_ptr );
            switch( edges_type_selected ) {
                case undirected:
                    adj_sets_array[undirected] = &( multiset_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
                    break;
                case directed:
                    adj_sets_array[directed] = &( multiset_vertex_mixed_graph_vertex_container_ptr->directed_adj );
                    break;
            }
        }
        else {
            auto const multiset_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( multiset_vertex_graph_vertex_container_ptr );
            if ( vertex_container_graph_owner_edges_type == undirected ) {
                if ( edges_type_selected == undirected ) {
                    adj_sets_array[undirected] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
            else {
                if ( edges_type_selected == directed ) {
                    adj_sets_array[directed] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(
    const graphdom::graph<VertexType>::adj_list& other) :
    vertex_container_graph_owner( other.vertex_container_graph_owner ),
    vertex_container_graph_owner_edges_type( other.vertex_container_graph_owner_edges_type ){
    if (
        std::holds_alternative<
            graphdom::graph<VertexType>::adj_list::set_vertex_graph_vertex_container_info_type
        >(
            other.graph_type_dependent_vertex_container_info
        )
    ) {
        const auto& other_type_dependent_vertex_container_info =
            std::get<
                graphdom::graph<VertexType>::adj_list::set_vertex_graph_vertex_container_info_type
            >( other.graph_type_dependent_vertex_container_info );
        vertex_container_ptr = other_type_dependent_vertex_container_info.first;
        vertex_container_adj_sets_ptr_array.template emplace<
            set_vertex_graph_vertex_container_adj_sets_ptr_array_type
        >(
            set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_ptr_array = std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >(vertex_container_adj_sets_ptr_array);
        adj_sets_ptr_array[undirected] = (other_type_dependent_vertex_container_info.second)[undirected];
        adj_sets_ptr_array[directed] = (other_type_dependent_vertex_container_info.second)[directed];
    }
    else {
        const auto& other_type_dependent_vertex_container_info =
            std::get<
                graphdom::graph<VertexType>::adj_list::multiset_vertex_graph_vertex_container_info_type
            >( other.graph_type_dependent_vertex_container_info );
        vertex_container_ptr = other_type_dependent_vertex_container_info.first;
        vertex_container_adj_sets_ptr_array.template emplace<
            multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type
        >(
            multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_ptr_array = std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >(vertex_container_adj_sets_ptr_array);
        adj_sets_ptr_array[undirected] = (other_type_dependent_vertex_container_info.second)[undirected];
        adj_sets_ptr_array[directed] = (other_type_dependent_vertex_container_info.second)[directed];
    }
}

/*
CONSTANT_EDGE_ITERATOR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* edge_set_vertex_graph_owner_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* edge_begin_point_ptr,
    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type edge_set_vertex_graph_owner_edges_type,
    const std::array<
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
        2
    >& edge_begin_point_adj_sets_array_ptr,
    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::begin_or_end begin_or_end_indicator
);
*/

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::graph<VertexType>::const_adj_list::begin() const {
    if ( std::holds_alternative< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( vertex_container_adj_sets_ptr_array ) ) {
        auto& adj_sets_ptr_array =
            std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
                vertex_container_adj_sets_ptr_array
            );
        return graphdom::graph<VertexType>::adj_list_const_iterator(
            vertex_container_graph_owner,
            vertex_container_ptr,
            vertex_container_graph_owner_edges_type,
            adj_sets_ptr_array,
            graphdom::graph<VertexType>::begin_or_end::begin
        );
    }
    auto& adj_sets_ptr_array =
        std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
            vertex_container_adj_sets_ptr_array
            );
    return graphdom::graph<VertexType>::adj_list_const_iterator(
        vertex_container_graph_owner,
        vertex_container_ptr,
        vertex_container_graph_owner_edges_type,
        adj_sets_ptr_array,
        graphdom::graph<VertexType>::begin_or_end::begin
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::graph<VertexType>::const_adj_list::end() const {
    if ( std::holds_alternative< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( vertex_container_adj_sets_ptr_array ) ) {
        auto& adj_sets_ptr_array =
            std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
                vertex_container_adj_sets_ptr_array
            );
        return graphdom::graph<VertexType>::adj_list_const_iterator(
            vertex_container_graph_owner,
            vertex_container_ptr,
            vertex_container_graph_owner_edges_type,
            adj_sets_ptr_array,
            graphdom::graph<VertexType>::begin_or_end::end
        );
    }
    auto& adj_sets_ptr_array =
        std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
            vertex_container_adj_sets_ptr_array
            );
    return graphdom::graph<VertexType>::adj_list_const_iterator(
        vertex_container_graph_owner,
        vertex_container_ptr,
        vertex_container_graph_owner_edges_type,
        adj_sets_ptr_array,
        graphdom::graph<VertexType>::begin_or_end::end
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::graph<VertexType>::const_adj_list::cbegin() const {
    return begin();
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::graph<VertexType>::const_adj_list::cend() const {
    return end();
}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(
    const graphdom::graph<VertexType>* const vertex_container_graph_owner_ptr,
    const graphdom::graph<VertexType>::vertex_container* const vertex_container_ptr,
    const graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type) :
    vertex_container_graph_owner(vertex_container_graph_owner_ptr),
    vertex_container_graph_owner_edges_type(vertex_container_graph_owner_edges_type),
    vertex_container_ptr(vertex_container_ptr) {
    if ( vertex_container_graph_owner_ptr == nullptr ) {
        throw std::runtime_error("Impossible to create adj_list"); //TODO: write a better message
    }
    if ( dynamic_cast< const graphdom::set_graph<VertexType>* >( vertex_container_graph_owner_ptr ) != nullptr ) {
        vertex_container_adj_sets_ptr_array.template emplace< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
            set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( vertex_container_adj_sets_ptr_array );
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const set_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            adj_sets_array[undirected] = &( set_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
            adj_sets_array[directed] = &( set_vertex_mixed_graph_vertex_container_ptr->directed_adj );
        }
        else {
            auto const set_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            adj_sets_array[ vertex_container_graph_owner_edges_type ] = &( set_vertex_non_mixed_graph_vertex_container_ptr->adj );
        }
    }
    else {
        vertex_container_adj_sets_ptr_array.template emplace< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
            multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( vertex_container_adj_sets_ptr_array );
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const multiset_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            adj_sets_array[undirected] = &( multiset_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
            adj_sets_array[directed] = &( multiset_vertex_mixed_graph_vertex_container_ptr->directed_adj );
        }
        else {
            auto const multiset_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            adj_sets_array[ vertex_container_graph_owner_edges_type ] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::const_adj_list::const_adj_list(
    const graphdom::graph<VertexType>* const vertex_container_graph_owner_ptr,
    const graphdom::graph<VertexType>::vertex_container* const vertex_container_ptr,
    const graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type,
    const graphdom::edge_type edges_type_selected) :
    vertex_container_graph_owner(vertex_container_graph_owner_ptr),
    vertex_container_graph_owner_edges_type(vertex_container_graph_owner_edges_type),
    vertex_container_ptr(vertex_container_ptr) {
    if ( vertex_container_graph_owner_ptr == nullptr ) {
        throw std::runtime_error("Impossible to create adj_list"); //TODO: write a better message
    }
    if ( dynamic_cast< const graphdom::set_graph<VertexType>* >( vertex_container_graph_owner_ptr ) != nullptr ) {
        vertex_container_adj_sets_ptr_array.template emplace< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
            set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( vertex_container_adj_sets_ptr_array );
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const set_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            switch ( edges_type_selected ) {
                case undirected:
                    adj_sets_array[undirected] = &( set_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
                    break;
                case directed:
                    adj_sets_array[directed] = &( set_vertex_mixed_graph_vertex_container_ptr->directed_adj );
                    break;
            }
        }
        else {
            auto const set_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            if ( vertex_container_graph_owner_edges_type == undirected ) {
                if ( edges_type_selected == undirected ) {
                    adj_sets_array[ undirected ] = &( set_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
            else {
                if ( edges_type_selected == directed ) {
                    adj_sets_array[ directed ] = &( set_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
        }
    }
    else {
        vertex_container_adj_sets_ptr_array.template emplace< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >(
            multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
        );
        auto& adj_sets_array = std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( vertex_container_adj_sets_ptr_array );
        if ( vertex_container_graph_owner_edges_type == mixed ) {
            auto const multiset_vertex_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            switch ( edges_type_selected ) {
                case undirected:
                    adj_sets_array[undirected] = &( multiset_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
                    break;
                case directed:
                    adj_sets_array[directed] = &( multiset_vertex_mixed_graph_vertex_container_ptr->directed_adj );
                    break;
            }
        }
        else {
            auto const multiset_vertex_non_mixed_graph_vertex_container_ptr =
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >( vertex_container_ptr );
            if ( vertex_container_graph_owner_edges_type == undirected ) {
                if ( edges_type_selected == undirected ) {
                    adj_sets_array[ undirected ] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
            else {
                if ( edges_type_selected == directed ) {
                    adj_sets_array[ directed ] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
                }
            }
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const typename graphdom::multiset_graph<VertexType>::adj_list_iterator& other) :
    edge_owner( other.edge_graph_owner ),
    type_dependent_edge_info(
        std::in_place_type< multiset_vertex_graph_edge_info >,
        other.vertex_container_begin_point,
        other.inner_itr,
        other.adj_sets_array
    ),
    current_edge_type(other.current_edge_type) {}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::adj_list_iterator::operator*() const {
    if (std::holds_alternative< set_vertex_graph_edge_info >( type_dependent_edge_info ) ) {
        auto& set_vertex_graph_edge_info_tuple = std::get < set_vertex_graph_edge_info >( type_dependent_edge_info );
        auto& inner_itr = std::get< set_vertex_graph_inner_edge_iterator_type >( set_vertex_graph_edge_info_tuple );
        /*
        if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
            throw std::runtime_error("Impossible to dereference"); //TODO: write a better message
        }
        */
        auto& real_inner_itr = std::get< real_set_vertex_graph_vertex_container_edge_iterator_type >(inner_itr);
        if ( graph_owner_edges_type == mixed ) {
            return graphdom::graph<VertexType>::vertex_handle(
                edge_owner,
                *(
                    static_cast<
                        const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                            const graphdom::graph<VertexType>::vertex_container*
                        >*
                    >(
                        (*(*real_inner_itr)).vertex_container_ptr
                    )
                )
            );
        }
        return graphdom::graph<VertexType>::vertex_handle(
            edge_owner,
            *(
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >*
                >(
                    (*(*real_inner_itr)).vertex_container_ptr
                )
            ),
            current_edge_type
        );
    }
    auto& multiset_vertex_graph_edge_info_tuple = std::get < multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& inner_itr = std::get< multiset_vertex_graph_inner_edge_iterator_type >( multiset_vertex_graph_edge_info_tuple );
    /*
    if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
        throw std::runtime_error("Impossible to dereference"); //TODO: write a better message
    }
    */
    auto& real_inner_itr = std::get< real_multiset_vertex_graph_vertex_container_edge_iterator_type >(inner_itr);
    if ( graph_owner_edges_type == mixed ) {
        return typename graphdom::multiset_graph<VertexType>::vertex_handle(
            dynamic_cast< const graphdom::multiset_graph<VertexType>* >( edge_owner ),
            *(
                static_cast<
                    graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >*
                >(
                    (*(*real_inner_itr)).vertex_container_ptr
                )
            )
        );
    }
    return typename graphdom::multiset_graph<VertexType>::vertex_handle(
        dynamic_cast< const graphdom::multiset_graph<VertexType>* >( edge_owner ),
        *(
            static_cast<
                graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                    graphdom::graph<VertexType>::vertex_container*
                >*
            >(
                (*(*real_inner_itr)).vertex_container_ptr
            )
        ),
        current_edge_type
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::adj_list_iterator::operator->() const {
    return *(*this);
}

template<typename VertexType>
bool graphdom::graph<VertexType>::adj_list_iterator::operator==(const adj_list_const_iterator& other) const {
    return adj_list_const_iterator(*this) == other;
    /*
    if (edge_owner != other.edge_graph_owner) {
        throw std::runtime_error("Undefined behavior"); //TODO: write a better message
    }
    if ( std::holds_alternative<set_vertex_graph_edge_info>(type_dependent_edge_info) ) {
        if ( std::holds_alternative<typename CONSTANT_EDGE_ITERATOR_NAME::multiset_vertex_graph_edge_info>(other.type_dependent_edge_info) ) {
            throw std::runtime_error("Undefined behavior"); //TODO: write a better message
        }
        const auto& this_type_dependent_edge_info = std::get<set_vertex_graph_edge_info>(type_dependent_edge_info);
        const auto& other_type_dependent_edge_info = std::get<typename CONSTANT_EDGE_ITERATOR_NAME::set_vertex_graph_edge_info>(other.type_dependent_edge_info);
        if ( std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(this_type_dependent_edge_info) != other.edge_vertex_container_owner ) {
            throw std::runtime_error("Undefined behavior"); //TODO: write a better message
        }
        if (current_edge_type != other.current_edge_type) {
            return false;
        }
        const auto this_inner_itr =
            std::get<
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator
            >(this_type_dependent_edge_info);
        return this_inner_itr == other_type_dependent_edge_info.first;
    }
    if ( std::holds_alternative<typename CONSTANT_EDGE_ITERATOR_NAME::set_vertex_graph_edge_info>(other.type_dependent_edge_info) ) {
        throw std::runtime_error("Undefined behavior"); //TODO: write a better message
    }
    const auto& this_type_dependent_edge_info = std::get<multiset_vertex_graph_edge_info>(type_dependent_edge_info);
    const auto& other_type_dependent_edge_info = std::get<typename CONSTANT_EDGE_ITERATOR_NAME::multiset_vertex_graph_edge_info>(other.type_dependent_edge_info);
    if ( std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(this_type_dependent_edge_info) != other.edge_vertex_container_owner ) {
        throw std::runtime_error("Undefined behavior"); //TODO: write a better message
    }
    if (current_edge_type != other.current_edge_type) {
        return false;
    }
    const auto this_inner_itr =
        std::get<
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator
        >(this_type_dependent_edge_info);
    return this_inner_itr == other_type_dependent_edge_info.first;
    */
}

template<typename VertexType>
bool graphdom::graph<VertexType>::adj_list_iterator::operator!=(const adj_list_const_iterator& other) const {
    return !( (*this) == other );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator& graphdom::graph<VertexType>::adj_list_iterator::operator++() {
    if ( std::holds_alternative<set_vertex_graph_edge_info>(type_dependent_edge_info) ) {
        auto& set_vertex_graph_info_tuple = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
        auto& inner_itr = std::get< set_vertex_graph_inner_edge_iterator_type >( set_vertex_graph_info_tuple );
        /*
        if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
            throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
        }
        */
        auto& real_inner_itr = std::get< real_set_vertex_graph_vertex_container_edge_iterator_type >( inner_itr );
        auto& vertex_container_adj_sets_ptr_array = std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( set_vertex_graph_info_tuple );
        if ( current_edge_type == undirected ) {
            if ( std::next( real_inner_itr ) == ( vertex_container_adj_sets_ptr_array[undirected]->end() ) ) {
                if ( vertex_container_adj_sets_ptr_array[directed] != nullptr ) {
                    if ( ! vertex_container_adj_sets_ptr_array[directed]->empty() ) {
                        real_inner_itr = vertex_container_adj_sets_ptr_array[directed]->begin();
                        current_edge_type = graphdom::edge_type::directed;
                        return *this;
                    }
                }
            }
            ++real_inner_itr;
            return *this;
        }
        ++real_inner_itr;
        return *this;
    }
    auto& multiset_vertex_graph_info_tuple = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& inner_itr = std::get< multiset_vertex_graph_inner_edge_iterator_type >( multiset_vertex_graph_info_tuple );
    /*
    if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
        throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
    }
    */
    auto& real_inner_itr = std::get< real_multiset_vertex_graph_vertex_container_edge_iterator_type >( inner_itr );
    auto& vertex_container_adj_sets_ptr_array = std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( multiset_vertex_graph_info_tuple );
    if ( current_edge_type == undirected ) {
        if ( std::next( real_inner_itr ) == ( vertex_container_adj_sets_ptr_array[undirected]->end() ) ) {
            if ( vertex_container_adj_sets_ptr_array[directed] != nullptr ) {
                if ( ! vertex_container_adj_sets_ptr_array[directed]->empty() ) {
                    real_inner_itr = vertex_container_adj_sets_ptr_array[directed]->begin();
                    current_edge_type = graphdom::edge_type::directed;
                    return *this;
                }
            }
        }
        ++real_inner_itr;
        return *this;
    }
    ++real_inner_itr;
    return *this;
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator graphdom::graph<VertexType>::adj_list_iterator::operator++(int) {
    auto this_before_increment = *this;
    ++(*this);
    return this_before_increment;
}

template<typename VertexType>
graphdom::edge_type graphdom::graph<VertexType>::adj_list_iterator::edge_type() const {
    return current_edge_type;
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graphdom::graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const graphdom::graph<VertexType>::vertex_container* const edge_begin_point_ptr,
    const graphdom::graph<VertexType>::graph_edges_type edge_set_vertex_graph_owner_edges_type,
    const std::array<
        graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
        2
    >& edge_begin_point_adj_sets_array_ptr,
    const graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator) :
    edge_owner(edge_set_vertex_graph_owner_ptr),
    graph_owner_edges_type(edge_set_vertex_graph_owner_edges_type),
    type_dependent_edge_info(
        std::in_place_type< set_vertex_graph_edge_info >,
        edge_begin_point_ptr,
        special_begin_end_indicator(),
        edge_begin_point_adj_sets_array_ptr
    ) {
    if ( edge_begin_point_adj_sets_array_ptr[undirected] == nullptr && edge_begin_point_adj_sets_array_ptr[directed] == nullptr ) {
        current_edge_type = ( edge_set_vertex_graph_owner_edges_type == undirected )? graphdom::edge_type::undirected : graphdom::edge_type::directed;
    }
    else {
        auto& set_vertex_graph_edge_info_tuple = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
        auto& set_vertex_graph_inner_edge_iterator = std::get< set_vertex_graph_inner_edge_iterator_type >( set_vertex_graph_edge_info_tuple );
        switch( begin_or_end_indicator ) {
            case begin:
                if ( edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[undirected]->empty() && edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                        if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() ) {
                            set_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->begin() );
                            current_edge_type =  graphdom::edge_type::undirected;
                        }
                        else {
                            set_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->begin() );
                            current_edge_type = graphdom::edge_type::directed;
                        }
                    }
                    else {
                        // !edge_begin_point_adj_sets_array_ptr[undirected]->empty() || edge_begin_point_adj_sets_array_ptr[directed] == nullptr
                        set_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->begin() );
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                }
                else {
                    // edge_begin_point_adj_sets_array_ptr[undirected] == nullptr
                    set_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->begin() );
                    current_edge_type = graphdom::edge_type::directed;
                }
                break;
            case end:
                if ( edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() && edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                        set_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->end() );
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                    else {
                        // !edge_begin_point_adj_sets_array_ptr[directed]->empty() || edge_begin_point_adj_sets_array_ptr[undirected] == nullptr
                        set_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->end() );
                        current_edge_type = graphdom::edge_type::directed;
                    }
                }
                else {
                    // edge_begin_point_adj_sets_array_ptr[directed] == nullptr
                    set_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->end() );
                    current_edge_type = graphdom::edge_type::undirected;
                }
                break;
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graphdom::graph<VertexType>* const edge_multiset_vertex_graph_owner_ptr,
    graphdom::graph<VertexType>::vertex_container* const edge_begin_point_ptr,
    const graphdom::graph<VertexType>::graph_edges_type edge_multiset_vertex_graph_owner_edges_type,
    const std::array<
        graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
        2
    >& edge_begin_point_adj_sets_array_ptr,
    const graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator) :
    edge_owner(edge_multiset_vertex_graph_owner_ptr),
    graph_owner_edges_type(edge_multiset_vertex_graph_owner_edges_type),
    type_dependent_edge_info(
        std::in_place_type< multiset_vertex_graph_edge_info >,
        edge_begin_point_ptr,
        special_begin_end_indicator(),
        edge_begin_point_adj_sets_array_ptr
    ) {
    if ( edge_begin_point_adj_sets_array_ptr[undirected] == nullptr && edge_begin_point_adj_sets_array_ptr[directed] == nullptr ) {
        current_edge_type = ( edge_multiset_vertex_graph_owner_edges_type == undirected )? graphdom::edge_type::undirected : graphdom::edge_type::directed;
    }
    else {
        auto& multiset_vertex_graph_edge_info_tuple = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
        auto& multiset_vertex_graph_inner_edge_iterator = std::get< multiset_vertex_graph_inner_edge_iterator_type >( multiset_vertex_graph_edge_info_tuple );
        switch( begin_or_end_indicator ) {
            case begin:
                if ( edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[undirected]->empty() && edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                        if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() ) {
                            multiset_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->begin() );
                            current_edge_type =  graphdom::edge_type::undirected;
                        }
                        else {
                            multiset_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->begin() );
                            current_edge_type = graphdom::edge_type::directed;
                        }
                    }
                    else {
                        // !edge_begin_point_adj_sets_array_ptr[undirected]->empty() || edge_begin_point_adj_sets_array_ptr[directed] == nullptr
                        multiset_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->begin() );
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                }
                else {
                    // edge_begin_point_adj_sets_array_ptr[undirected] == nullptr
                    multiset_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->begin() );
                    current_edge_type = graphdom::edge_type::directed;
                }
                break;
            case end:
                if ( edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() && edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                        multiset_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->end() );
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                    else {
                        // !edge_begin_point_adj_sets_array_ptr[directed]->empty() || edge_begin_point_adj_sets_array_ptr[undirected] == nullptr
                        multiset_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->end() );
                        current_edge_type = graphdom::edge_type::directed;
                    }
                }
                else {
                    // edge_begin_point_adj_sets_array_ptr[directed] == nullptr
                    multiset_vertex_graph_inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->end() );
                    current_edge_type = graphdom::edge_type::undirected;
                }
                break;
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const set_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
        const graphdom::graph<VertexType>::vertex_container*
    >* const edge_begin_point_ptr,
    const graphdom::edge_type edge_set_vertex_graph_owner_edges_type,
    const typename graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr) :
    edge_owner(edge_set_vertex_graph_owner_ptr),
    graph_owner_edges_type( (edge_set_vertex_graph_owner_edges_type == undirected) ?
        graphdom::graph<VertexType>::graph_edges_type::undirected : graphdom::graph<VertexType>::graph_edges_type::directed ),
    type_dependent_edge_info(
        std::in_place_type< set_vertex_graph_edge_info >,
        edge_begin_point_ptr,
        std::variant< special_begin_end_indicator, real_set_vertex_graph_vertex_container_edge_iterator_type >(
            std::in_place_type< real_set_vertex_graph_vertex_container_edge_iterator_type >,
            inner_itr
        ),
        set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
    ),
    current_edge_type(edge_set_vertex_graph_owner_edges_type){
    auto& specific_type_dependent_edge_info =
        std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& adj_sets_ptr_array =
        std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( specific_type_dependent_edge_info );
    adj_sets_ptr_array[ edge_set_vertex_graph_owner_edges_type ] = &( edge_begin_point_ptr->adj );
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const set_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
        const graphdom::graph<VertexType>::vertex_container*
    >* const edge_begin_point_ptr,
    const typename graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr,
    const graphdom::edge_type inner_itr_edge_type,
    const bool inner_itr_is_limited_by_edge_type) :
    edge_owner(edge_set_vertex_graph_owner_ptr),
    graph_owner_edges_type(mixed),
    type_dependent_edge_info(
        std::in_place_type< set_vertex_graph_edge_info >,
        edge_begin_point_ptr,
        std::variant< special_begin_end_indicator, real_set_vertex_graph_vertex_container_edge_iterator_type >(
            std::in_place_type< real_set_vertex_graph_vertex_container_edge_iterator_type >,
            inner_itr
        ),
        set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
    ),
    current_edge_type(inner_itr_edge_type) {
    auto& specific_type_dependent_edge_info =
        std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& adj_sets_ptr_array =
        std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( specific_type_dependent_edge_info );
    adj_sets_ptr_array[current_edge_type] = &( ( current_edge_type == undirected ) ? edge_begin_point_ptr->undirected_adj : edge_begin_point_ptr->directed_adj );
    if ( ! inner_itr_is_limited_by_edge_type ) {
        if ( current_edge_type == undirected ) {
            adj_sets_ptr_array[directed] = &( edge_begin_point_ptr->directed_adj );
        }
        else {
            adj_sets_ptr_array[undirected] = &( edge_begin_point_ptr->undirected_adj );
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
    graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
        graphdom::graph<VertexType>::vertex_container*
    >* const edge_begin_point_ptr,
    const graphdom::edge_type edge_multiset_vertex_graph_owner_edges_type,
    const typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr) :
    edge_owner(edge_multiset_vertex_graph_owner_ptr),
    graph_owner_edges_type( (edge_multiset_vertex_graph_owner_edges_type == undirected) ?
        graphdom::graph<VertexType>::graph_edges_type::undirected : graphdom::graph<VertexType>::graph_edges_type::directed ),
    type_dependent_edge_info(
        std::in_place_type< multiset_vertex_graph_edge_info >,
        edge_begin_point_ptr,
        std::variant< special_begin_end_indicator, real_multiset_vertex_graph_vertex_container_edge_iterator_type >(
            std::in_place_type< real_multiset_vertex_graph_vertex_container_edge_iterator_type >,
            inner_itr
        ),
        multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
    ),
    current_edge_type(edge_multiset_vertex_graph_owner_edges_type) {
    auto& specific_type_dependent_edge_info =
        std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& adj_sets_ptr_array =
        std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( specific_type_dependent_edge_info );
    adj_sets_ptr_array[ edge_multiset_vertex_graph_owner_edges_type ] = &( edge_begin_point_ptr->adj );
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
    graphdom::graph<VertexType>::mixed_graph_vertex_container<
        graphdom::graph<VertexType>::vertex_container*
    >* const edge_begin_point_ptr,
    const typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr,
    const graphdom::edge_type inner_itr_edge_type,
    const bool inner_itr_is_limited_by_edge_type) :
    edge_owner(edge_multiset_vertex_graph_owner_ptr),
    graph_owner_edges_type(mixed),
    type_dependent_edge_info(
        std::in_place_type< multiset_vertex_graph_edge_info >,
        edge_begin_point_ptr,
        std::variant< special_begin_end_indicator, real_multiset_vertex_graph_vertex_container_edge_iterator_type >(
            std::in_place_type< real_multiset_vertex_graph_vertex_container_edge_iterator_type >,
            inner_itr
        ),
        multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
    ),
    current_edge_type(inner_itr_edge_type) {
    auto& specific_type_dependent_edge_info =
        std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& adj_sets_ptr_array =
        std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( specific_type_dependent_edge_info );
    adj_sets_ptr_array[current_edge_type] = &( ( current_edge_type == undirected ) ? edge_begin_point_ptr->undirected_adj : edge_begin_point_ptr->directed_adj );
    if ( ! inner_itr_is_limited_by_edge_type ) {
        if ( current_edge_type == undirected ) {
            adj_sets_ptr_array[directed] = &( edge_begin_point_ptr->directed_adj );
        }
        else {
            adj_sets_ptr_array[undirected] = &( edge_begin_point_ptr->undirected_adj );
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(const adj_list_iterator& other) :
edge_graph_owner(other.edge_owner),
edge_vertex_container_owner(nullptr),
graph_owner_edges_type(other.graph_owner_edges_type),
current_edge_type(other.current_edge_type) {
    if ( std::holds_alternative< typename adj_list_iterator::set_vertex_graph_edge_info >( other.type_dependent_edge_info ) ) {
        const auto& other_type_dependent_edge_info =
            std::get< typename adj_list_iterator::set_vertex_graph_edge_info >( other.type_dependent_edge_info );
        edge_vertex_container_owner = std::get<const graphdom::graph<VertexType>::vertex_container*>( other_type_dependent_edge_info );
        const auto& other_inner_itr = std::get< typename adj_list_iterator::set_vertex_graph_inner_edge_iterator_type >( other_type_dependent_edge_info );
        const auto& other_adj_sets_ptr_array = std::get< typename adj_list_iterator::set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( other_type_dependent_edge_info );
        if ( std::holds_alternative< typename adj_list_iterator::special_begin_end_indicator >( other_inner_itr ) ) {
            const set_vertex_graph_inner_edge_iterator_type inner_itr_to_insert = special_begin_end_indicator();
            type_dependent_edge_info.template emplace< set_vertex_graph_edge_info >(
                inner_itr_to_insert,
                set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
            );
            auto& adj_sets_ptr_array = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info ).second;
            adj_sets_ptr_array[undirected] = other_adj_sets_ptr_array[undirected];
            adj_sets_ptr_array[directed] = other_adj_sets_ptr_array[directed];
        }
        else {
            const set_vertex_graph_inner_edge_iterator_type inner_itr_to_insert =
                std::get< typename adj_list_iterator::real_set_vertex_graph_vertex_container_edge_iterator_type >( other_inner_itr );
            type_dependent_edge_info.template emplace< set_vertex_graph_edge_info >(
                inner_itr_to_insert,
                set_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
            );
            auto& adj_sets_ptr_array = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info ).second;
            adj_sets_ptr_array[undirected] = other_adj_sets_ptr_array[undirected];
            adj_sets_ptr_array[directed] = other_adj_sets_ptr_array[directed];
        }
    }
    else {
        const auto& other_type_dependent_edge_info =
            std::get< typename adj_list_iterator::multiset_vertex_graph_edge_info >( other.type_dependent_edge_info );
        edge_vertex_container_owner = std::get<graphdom::graph<VertexType>::vertex_container*>( other_type_dependent_edge_info );
        const auto& other_inner_itr = std::get< typename adj_list_iterator::multiset_vertex_graph_inner_edge_iterator_type >( other_type_dependent_edge_info );
        const auto& other_adj_sets_ptr_array = std::get< typename adj_list_iterator::multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( other_type_dependent_edge_info );
        if ( std::holds_alternative< typename adj_list_iterator::special_begin_end_indicator >( other_inner_itr ) ) {
            const multiset_vertex_graph_inner_edge_iterator_type inner_itr_to_insert = special_begin_end_indicator();
            type_dependent_edge_info.template emplace< multiset_vertex_graph_edge_info >(
                inner_itr_to_insert,
                multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
            );
            auto& adj_sets_ptr_array = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info ).second;
            adj_sets_ptr_array[undirected] = other_adj_sets_ptr_array[undirected];
            adj_sets_ptr_array[directed] = other_adj_sets_ptr_array[directed];
        }
        else {
            const multiset_vertex_graph_inner_edge_iterator_type inner_itr_to_insert =
                std::get< typename adj_list_iterator::real_multiset_vertex_graph_vertex_container_edge_iterator_type >( other_inner_itr );
            type_dependent_edge_info.template emplace< multiset_vertex_graph_edge_info >(
                inner_itr_to_insert,
                multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type{nullptr,nullptr}
            );
            auto& adj_sets_ptr_array = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info ).second;
            adj_sets_ptr_array[undirected] = other_adj_sets_ptr_array[undirected];
            adj_sets_ptr_array[directed] = other_adj_sets_ptr_array[directed];
        }
    }
    /*
    if (std::holds_alternative<typename EDGE_ITERATOR_NAME::set_vertex_graph_edge_info>(other.type_dependent_edge_info)) {
        const auto& other_type_dependent_edge_info =
            std::get<typename EDGE_ITERATOR_NAME::set_vertex_graph_edge_info>(other.type_dependent_edge_info);
        edge_vertex_container_owner = std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(other_type_dependent_edge_info);
        const auto other_inner_itr =
            std::get<
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator
            >(other_type_dependent_edge_info);
        const auto& other_adj_sets_array =
            std::get<
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >(other_type_dependent_edge_info);
        type_dependent_edge_info.template emplace<set_vertex_graph_edge_info>(
            other_inner_itr,
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >{nullptr,nullptr}
        );
        auto& this_adj_sets_array = ( std::get<set_vertex_graph_edge_info>( type_dependent_edge_info ) ).second;
        this_adj_sets_array[undirected] = other_adj_sets_array[undirected];
        this_adj_sets_array[directed] = other_adj_sets_array[directed];
    }
    else {
        const auto& other_type_dependent_edge_info =
            std::get<typename EDGE_ITERATOR_NAME::multiset_vertex_graph_edge_info>(other.type_dependent_edge_info);
        edge_vertex_container_owner = std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(other_type_dependent_edge_info);
        const auto other_inner_itr =
            std::get<
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator
            >(other_type_dependent_edge_info);
        const auto& other_adj_sets_array =
            std::get<
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >(other_type_dependent_edge_info);
        type_dependent_edge_info.template emplace<multiset_vertex_graph_edge_info>(
            other_inner_itr,
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >{nullptr,nullptr}
        );
        auto& this_adj_sets_array = ( std::get<multiset_vertex_graph_edge_info>( type_dependent_edge_info ) ).second;
        this_adj_sets_array[undirected] = other_adj_sets_array[undirected];
        this_adj_sets_array[directed] = other_adj_sets_array[directed];
    }
    */
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(
    const typename graphdom::multiset_graph<VertexType>::adj_list_iterator& other) :
    edge_graph_owner(other.edge_owner),
    edge_vertex_container_owner(other.edge_vertex_container_owner),
    graph_owner_edges_type(other.graph_owner_edges_type),
    type_dependent_edge_info(std::in_place_type< graphdom::graph<VertexType>::adj_list_const_iterator::multiset_vertex_graph_edge_info >),
    current_edge_type(other.current_edge_type) {
    auto& this_multiset_vertex_graph_edge_info = std::get< graphdom::graph<VertexType>::adj_list_const_iterator::multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& this_multiset_vertex_graph_inner_edge_iterator_type = std::get< graphdom::graph<VertexType>::adj_list_const_iterator::multiset_vertex_graph_inner_edge_iterator_type >( this_multiset_vertex_graph_edge_info );
    this_multiset_vertex_graph_inner_edge_iterator_type = other.inner_edge_iterator;
    auto& this_multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type = std::get< graphdom::graph<VertexType>::adj_list_const_iterator::multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( this_multiset_vertex_graph_edge_info );
    this_multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type[undirected] = (other.vertex_container_adj_sets_ptr_array)[undirected];
    this_multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type[directed] = (other.vertex_container_adj_sets_ptr_array)[directed];
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle
graphdom::graph<VertexType>::adj_list_const_iterator::operator*() const {
    if ( std::holds_alternative< set_vertex_graph_edge_info >( type_dependent_edge_info ) ) {
        auto& specific_type_dependent_edge_info = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
        auto& inner_itr = specific_type_dependent_edge_info.first;
        /*
        if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
            throw std::runtime_error("Impossible to dereference"); //TODO: write a better message
        }
        */
        auto& real_inner_itr = std::get< real_set_vertex_graph_vertex_container_edge_iterator_type >( inner_itr);
        if ( graph_owner_edges_type == mixed ) {
            return graphdom::graph<VertexType>::vertex_const_handle(
                edge_graph_owner,
                *(
                    static_cast<
                        const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                            const graphdom::graph<VertexType>::vertex_container*
                        >
                        *
                    > (
                        (*(*real_inner_itr)).vertex_container_ptr
                    )
                )
            );
        }
        return graphdom::graph<VertexType>::vertex_const_handle(
            edge_graph_owner,
            *(
                static_cast<
                    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                        const graphdom::graph<VertexType>::vertex_container*
                    >
                    *
                > (
                    (*(*real_inner_itr)).vertex_container_ptr
                )
            ),
            current_edge_type
        );
    }
    auto& specific_type_dependent_edge_info = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& inner_itr = specific_type_dependent_edge_info.first;
    /*
    if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
        throw std::runtime_error("Impossible to dereference"); //TODO: write a better message
    }
    */
    auto& real_inner_itr = std::get< real_multiset_vertex_graph_vertex_container_edge_iterator_type >( inner_itr);
    if ( graph_owner_edges_type == mixed ) {
        return graphdom::graph<VertexType>::vertex_const_handle(
            dynamic_cast< const graphdom::multiset_graph<VertexType>* >( edge_graph_owner ),
            *(
                static_cast<
                    const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                        graphdom::graph<VertexType>::vertex_container*
                    >
                    *
                > (
                    (*(*real_inner_itr)).vertex_container_ptr
                )
            )
        );
    }
    return graphdom::graph<VertexType>::vertex_const_handle(
        dynamic_cast< const graphdom::multiset_graph<VertexType>* >( edge_graph_owner ),
        *(
            static_cast<
                const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                    graphdom::graph<VertexType>::vertex_container*
                >
                *
            > (
                (*(*real_inner_itr)).vertex_container_ptr
            )
        ),
        current_edge_type
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle
graphdom::graph<VertexType>::adj_list_const_iterator::operator->() const {
    return *(*this);
}

template<typename VertexType>
bool graphdom::graph<VertexType>::adj_list_const_iterator::operator==(const adj_list_const_iterator& other) const {
    if (current_edge_type != other.current_edge_type) {
        return false;
    }
    if ( std::holds_alternative<set_vertex_graph_edge_info>(type_dependent_edge_info) ) {
        const auto& other_type_dependent_edge_info = std::get< set_vertex_graph_edge_info >( other.type_dependent_edge_info );
        const auto& this_type_dependent_edge_info = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
        return this_type_dependent_edge_info.first == other_type_dependent_edge_info.first;
    }
    const auto& other_type_dependent_edge_info = std::get< multiset_vertex_graph_edge_info >( other.type_dependent_edge_info );
    const auto& this_type_dependent_edge_info = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    return this_type_dependent_edge_info.first == other_type_dependent_edge_info.first;
}

template<typename VertexType>
bool graphdom::graph<VertexType>::adj_list_const_iterator::operator!=(const adj_list_const_iterator& other) const {
    return !( (*this) == other );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator& graphdom::graph<VertexType>::adj_list_const_iterator::operator++() {
    if ( std::holds_alternative<set_vertex_graph_edge_info>(type_dependent_edge_info) ) {
        auto& specific_type_dependent_edge_info = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
        auto& inner_itr = specific_type_dependent_edge_info.first;
        /*
        if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
            throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
        }
        */
        auto& real_inner_itr = std::get< real_set_vertex_graph_vertex_container_edge_iterator_type >( inner_itr );
        auto& vertex_container_adj_sets_ptr_array = std::get< set_vertex_graph_vertex_container_adj_sets_ptr_array_type >( specific_type_dependent_edge_info );
        if ( current_edge_type == undirected ) {
            if ( std::next(real_inner_itr) == vertex_container_adj_sets_ptr_array[undirected]->end() ) {
                if ( vertex_container_adj_sets_ptr_array[directed] != nullptr ) {
                    if ( ! vertex_container_adj_sets_ptr_array[directed]->empty() ) {
                        real_inner_itr = vertex_container_adj_sets_ptr_array[directed]->begin();
                        current_edge_type = graphdom::edge_type::directed;
                        return *this;
                    }
                }
            }
            ++real_inner_itr;
            return *this;
        }
        ++real_inner_itr;
        return *this;
    }
    auto& specific_type_dependent_edge_info = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    auto& inner_itr = specific_type_dependent_edge_info.first;
    /*
    if ( std::holds_alternative< special_begin_end_indicator >( inner_itr ) ) {
        throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
    }
    */
    auto& real_inner_itr = std::get< real_multiset_vertex_graph_vertex_container_edge_iterator_type >( inner_itr );
    auto& vertex_container_adj_sets_ptr_array = std::get< multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type >( specific_type_dependent_edge_info );
    if ( current_edge_type == undirected ) {
        if ( std::next(real_inner_itr) == vertex_container_adj_sets_ptr_array[undirected]->end() ) {
            if ( vertex_container_adj_sets_ptr_array[directed] != nullptr ) {
                if ( ! vertex_container_adj_sets_ptr_array[directed]->empty() ) {
                    real_inner_itr = vertex_container_adj_sets_ptr_array[directed]->begin();
                    current_edge_type = graphdom::edge_type::directed;
                    return *this;
                }
            }
        }
        ++real_inner_itr;
        return *this;
    }
    ++real_inner_itr;
    return *this;
    /*
    if ( std::holds_alternative<set_vertex_graph_edge_info>(type_dependent_edge_info) ) {
        auto& specific_type_dependent_edge_info = std::get<set_vertex_graph_edge_info>(type_dependent_edge_info);
        auto& inner_itr = specific_type_dependent_edge_info.first;
        auto& adj_sets_array = specific_type_dependent_edge_info.second;
        if ( current_edge_type == undirected ) {
            if ( inner_itr == ( adj_sets_array[undirected]->end() ) ) {
                throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
            }
            if ( std::next(inner_itr) != ( adj_sets_array[undirected]->end() ) || adj_sets_array[directed] == nullptr ) {
                ++inner_itr;
                return (*this);
            }
            inner_itr = ( adj_sets_array[directed]->begin() );
            current_edge_type = directed;
            return *this;
        }
        if ( inner_itr == ( adj_sets_array[directed]->end() ) ) {
            throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
        }
        ++inner_itr;
        return (*this);
    }
    auto& specific_type_dependent_edge_info = std::get<multiset_vertex_graph_edge_info>(type_dependent_edge_info);
    auto& inner_itr = specific_type_dependent_edge_info.first;
    auto& adj_sets_array = specific_type_dependent_edge_info.second;
    if ( current_edge_type == undirected ) {
        if ( inner_itr == ( adj_sets_array[undirected]->end() ) ) {
            throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
        }
        if ( std::next(inner_itr) != ( adj_sets_array[undirected]->end() ) || adj_sets_array[directed] == nullptr ) {
            ++inner_itr;
            return (*this);
        }
        inner_itr = ( adj_sets_array[directed]->begin() );
        current_edge_type = directed;
        return *this;
    }
    if ( inner_itr == ( adj_sets_array[directed]->end() ) ) {
        throw std::runtime_error("Generic edge iterator overflow"); //TODO: write a better message
    }
    ++inner_itr;
    return (*this);
    */
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator graphdom::graph<VertexType>::adj_list_const_iterator::operator++(int) {
    auto this_before_increment = *this;
    ++(*this);
    return this_before_increment;
}

template<typename VertexType>
graphdom::edge_type graphdom::graph<VertexType>::adj_list_const_iterator::edge_type() const {
    return current_edge_type;
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(
    const graphdom::graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const graphdom::graph<VertexType>::vertex_container* const edge_begin_point_ptr,
    const graphdom::graph<VertexType>::graph_edges_type edge_set_vertex_graph_owner_edges_type,
    const std::array<
        const graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
        2
    >& edge_begin_point_adj_sets_array_ptr,
    const graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator) :
    edge_graph_owner(edge_set_vertex_graph_owner_ptr),
    edge_vertex_container_owner(edge_begin_point_ptr),
    graph_owner_edges_type(edge_set_vertex_graph_owner_edges_type),
    type_dependent_edge_info(
        std::in_place_type< set_vertex_graph_edge_info >,
        special_begin_end_indicator(),
        edge_begin_point_adj_sets_array_ptr
    ){
    if ( edge_begin_point_adj_sets_array_ptr[undirected] == nullptr && edge_begin_point_adj_sets_array_ptr[directed] == nullptr ) {
        current_edge_type = ( edge_set_vertex_graph_owner_edges_type == undirected ) ? graphdom::edge_type::undirected :  graphdom::edge_type::directed;
    }
    else {
        auto& set_vertex_graph_edge_info_pair = std::get< set_vertex_graph_edge_info >(type_dependent_edge_info);
        auto& set_vertex_graph_inner_edge_iterator = std::get< set_vertex_graph_inner_edge_iterator_type >( set_vertex_graph_edge_info_pair );
        switch ( begin_or_end_indicator ) {
            case begin:
                if ( edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[undirected]->empty() && edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                        if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() ) {
                            set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->begin();
                            current_edge_type = graphdom::edge_type::undirected;
                        }
                        else {
                            set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[directed]->begin();
                            current_edge_type = graphdom::edge_type::directed;
                        }
                    }
                    else {
                        // ( ! edge_begin_point_adj_sets_array_ptr[undirected]->empty() ) || edge_begin_point_adj_sets_array_ptr[directed] == nullptr
                        set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->begin();
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                }
                else {
                    set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[directed]->begin();
                    current_edge_type = graphdom::edge_type::directed;
                }
                break;
            case end:
                if ( edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() && edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                        set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->end();
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                    else {
                        set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[directed]->end();
                        current_edge_type = graphdom::edge_type::directed;
                    }
                }
                else {
                    set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->end();
                    current_edge_type = graphdom::edge_type::undirected;
                }
                break;
        }
    }
}

template<typename VertexType>
graphdom::graph<VertexType>::adj_list_const_iterator::adj_list_const_iterator(
    const graphdom::graph<VertexType>* const edge_multiset_vertex_graph_owner_ptr,
    const graphdom::graph<VertexType>::vertex_container* const edge_begin_point_ptr,
    const graphdom::graph<VertexType>::graph_edges_type edge_multiset_vertex_graph_owner_edges_type,
    const std::array<
        const graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
        2
    >& edge_begin_point_adj_sets_array_ptr,
    const graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator) :
    edge_graph_owner(edge_multiset_vertex_graph_owner_ptr),
    edge_vertex_container_owner(edge_begin_point_ptr),
    graph_owner_edges_type(edge_multiset_vertex_graph_owner_edges_type),
    type_dependent_edge_info(
        std::in_place_type< multiset_vertex_graph_edge_info >,
        special_begin_end_indicator(),
        edge_begin_point_adj_sets_array_ptr
    ){
    if ( edge_begin_point_adj_sets_array_ptr[undirected] == nullptr && edge_begin_point_adj_sets_array_ptr[directed] == nullptr ) {
        current_edge_type = ( edge_multiset_vertex_graph_owner_edges_type == undirected ) ? graphdom::edge_type::undirected :  graphdom::edge_type::directed;
    }
    else {
        auto& set_vertex_graph_edge_info_pair = std::get< multiset_vertex_graph_edge_info >(type_dependent_edge_info);
        auto& set_vertex_graph_inner_edge_iterator = std::get< multiset_vertex_graph_inner_edge_iterator_type >( set_vertex_graph_edge_info_pair );
        switch ( begin_or_end_indicator ) {
            case begin:
                if ( edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[undirected]->empty() && edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                        if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() ) {
                            set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->begin();
                            current_edge_type = graphdom::edge_type::undirected;
                        }
                        else {
                            set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[directed]->begin();
                            current_edge_type = graphdom::edge_type::directed;
                        }
                    }
                    else {
                        // ( ! edge_begin_point_adj_sets_array_ptr[undirected]->empty() ) || edge_begin_point_adj_sets_array_ptr[directed] == nullptr
                        set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->begin();
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                }
                else {
                    set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[directed]->begin();
                    current_edge_type = graphdom::edge_type::directed;
                }
                break;
            case end:
                if ( edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() && edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                        set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->end();
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                    else {
                        set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[directed]->end();
                        current_edge_type = graphdom::edge_type::directed;
                    }
                }
                else {
                    set_vertex_graph_inner_edge_iterator = edge_begin_point_adj_sets_array_ptr[undirected]->end();
                    current_edge_type = graphdom::edge_type::undirected;
                }
                break;
        }
    }
}

template<typename VertexType>
bool graphdom::graph<VertexType>::adj_list_const_iterator::is_limited_by_edge_type() const {
    if ( std::holds_alternative< set_vertex_graph_edge_info >( type_dependent_edge_info ) ) {
        const auto& specific_type_dependent_edge_info = std::get< set_vertex_graph_edge_info >( type_dependent_edge_info );
        const auto& adj_sets_ptr_array = specific_type_dependent_edge_info.second;
        if ( graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::mixed ) {
            return ( adj_sets_ptr_array[graphdom::edge_type::undirected] == nullptr ) ||
                    ( adj_sets_ptr_array[graphdom::edge_type::directed] == nullptr );
        }
        return adj_sets_ptr_array[
            ( graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::undirected ) ?
            graphdom::edge_type::undirected : graphdom::edge_type::directed
        ] == nullptr;
    }
    const auto& specific_type_dependent_edge_info = std::get< multiset_vertex_graph_edge_info >( type_dependent_edge_info );
    const auto& adj_sets_ptr_array = specific_type_dependent_edge_info.second;
    if ( graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::mixed ) {
        return ( adj_sets_ptr_array[graphdom::edge_type::undirected] == nullptr ) ||
                ( adj_sets_ptr_array[graphdom::edge_type::directed] == nullptr );
    }
    return adj_sets_ptr_array[
        ( graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::undirected ) ?
        graphdom::edge_type::undirected : graphdom::edge_type::directed
    ] == nullptr;
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::vertex_handle::vertex_handle(
    const typename graphdom::graph<VertexType>::vertex_handle& other) :
    vertex_owner( dynamic_cast< const graphdom::multiset_graph<VertexType>* >( other.vertex_owner ) ),
    edges_type( other.edges_type ) {
    if ( std::holds_alternative< typename graphdom::graph<VertexType>::vertex_container* >( other.vertex_container_ptr ) ) {
        multiset_graph_vertex_container = std::get< typename graphdom::graph<VertexType>::vertex_container* >( other.vertex_container_ptr );
    }
    else if ( std::holds_alternative< std::monostate >( other.vertex_container_ptr ) ) {
        multiset_graph_vertex_container = nullptr;
    }
    else {
        throw std::runtime_error("Impossible to convert"); //TODO: write a better message
    }
}

template<typename VertexType>
VertexType& graphdom::multiset_graph<VertexType>::vertex_handle::operator*() const {
    if (multiset_graph_vertex_container!=nullptr) {
        return multiset_graph_vertex_container->vertex;
    }
    throw std::runtime_error("Impossible to dereference a multiset_vertex_graph::vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
VertexType* graphdom::multiset_graph<VertexType>::vertex_handle::operator->() const {
    if (multiset_graph_vertex_container!=nullptr) {
        return &(multiset_graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a multiset_vertex_graph::vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool graphdom::multiset_graph<VertexType>::vertex_handle::operator==(
    const typename graphdom::graph<VertexType>::vertex_const_handle& other) const {
    if(vertex_owner!=other.vertex_owner) {
        return false;
    }
    return multiset_graph_vertex_container == other.graph_vertex_container;
}

template<typename VertexType>
bool graphdom::multiset_graph<VertexType>::vertex_handle::operator!=(
    const typename graphdom::graph<VertexType>::vertex_const_handle& other) const {
    return !( (*this) == other );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list
graphdom::multiset_graph<VertexType>::vertex_handle::adj_list() const {
    if (vertex_owner!=nullptr) {
        if (multiset_graph_vertex_container!=nullptr){
            return graphdom::multiset_graph<VertexType>::adj_list(
                vertex_owner,
                multiset_graph_vertex_container,
                edges_type
            );
        }
    }
    throw std::runtime_error("Impossible to get adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list
graphdom::multiset_graph<VertexType>::vertex_handle::adj_list(const graphdom::edge_type et) const {
    if (vertex_owner!=nullptr) {
        if (multiset_graph_vertex_container!=nullptr){
            return graphdom::multiset_graph<VertexType>::adj_list(
                vertex_owner,
                multiset_graph_vertex_container,
                edges_type,
                et
            );
        }
    }
    throw std::runtime_error("Impossible to get adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list
graphdom::multiset_graph<VertexType>::vertex_handle::const_adj_list() const {
    if (vertex_owner!=nullptr) {
        return typename graphdom::graph<VertexType>::const_adj_list(
            vertex_owner,
            multiset_graph_vertex_container,
            edges_type
        );
    }
    throw std::runtime_error("Impossible to get const_adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename graphdom::graph<VertexType>::const_adj_list
graphdom::multiset_graph<VertexType>::vertex_handle::const_adj_list(graphdom::edge_type et) const {
    if (vertex_owner!=nullptr) {
        return typename graphdom::graph<VertexType>::const_adj_list(
            vertex_owner,
            multiset_graph_vertex_container,
            edges_type,
            et
        );
    }
    throw std::runtime_error("Impossible to get const_adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::vertex_handle::vertex_handle(
    const graphdom::multiset_graph<VertexType>* vo,
    typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vc_ref,
    graphdom::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    multiset_graph_vertex_container(static_cast<VertexContainerPointerType>(&vc_ref)) {
    if (non_mixed_graph_type == graphdom::edge_type::undirected) {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = graphdom::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::vertex_handle::vertex_handle(
    const graphdom::multiset_graph<VertexType>* vo,
    typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vc_ref) :
    vertex_owner(vo),
    multiset_graph_vertex_container(static_cast<VertexContainerPointerType>(&vc_ref)),
    edges_type(graphdom::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list::adj_list(
    const typename graphdom::graph<VertexType>::adj_list& other_adj_list) :
    vertex_container_graph_owner(
        dynamic_cast< const graphdom::multiset_graph<VertexType>* >( other_adj_list.vertex_container_graph_owner )
    ),
    vertex_container_graph_owner_edges_type( other_adj_list.vertex_container_graph_owner_edges_type ),
    vertex_container_ptr( nullptr ),
    adj_sets_array( {nullptr,nullptr} ) {
    if (
        std::holds_alternative< typename graphdom::graph<VertexType>::adj_list::multiset_vertex_graph_vertex_container_info_type > (
            other_adj_list.graph_type_dependent_vertex_container_info
        )
    ) {
        const auto& multiset_vertex_graph_vertex_container_info_type_pair =
            std::get< typename graphdom::graph<VertexType>::adj_list::multiset_vertex_graph_vertex_container_info_type >(
                other_adj_list.graph_type_dependent_vertex_container_info
            );
        vertex_container_ptr = multiset_vertex_graph_vertex_container_info_type_pair.first;
        adj_sets_array = multiset_vertex_graph_vertex_container_info_type_pair.second;
    }
    else {
        throw std::runtime_error("Impossible to convert"); //TODO: write a better message
    }
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator
graphdom::multiset_graph<VertexType>::adj_list::begin() const {
    return graphdom::multiset_graph<VertexType>::adj_list_iterator(
        vertex_container_graph_owner,
        vertex_container_ptr,
        vertex_container_graph_owner_edges_type,
        adj_sets_array,
        graphdom::graph<VertexType>::begin_or_end::begin
    );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator
graphdom::multiset_graph<VertexType>::adj_list::end() const {
    return graphdom::multiset_graph<VertexType>::adj_list_iterator(
        vertex_container_graph_owner,
        vertex_container_ptr,
        vertex_container_graph_owner_edges_type,
        adj_sets_array,
        graphdom::graph<VertexType>::begin_or_end::end
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::multiset_graph<VertexType>::adj_list::cbegin() const {
    return typename graphdom::graph<VertexType>::adj_list_const_iterator((*this).begin());
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_const_iterator
graphdom::multiset_graph<VertexType>::adj_list::cend() const {
    return typename graphdom::graph<VertexType>::adj_list_const_iterator((*this).end());
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list::adj_list(
    const graphdom::multiset_graph<VertexType>* const vertex_container_graph_owner_ptr,
    const VertexContainerPointerType vertex_container_ptr,
    const typename graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type) :
    vertex_container_graph_owner(vertex_container_graph_owner_ptr),
    vertex_container_graph_owner_edges_type(vertex_container_graph_owner_edges_type),
    vertex_container_ptr(vertex_container_ptr),
    adj_sets_array({nullptr,nullptr}) {
    if ( vertex_container_ptr == nullptr ) {
        throw std::runtime_error("Impossible to create adj_list"); //TODO: write a better message
    }
    if ( vertex_container_graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::mixed ) {
        auto const multiset_vertex_mixed_graph_vertex_container_ptr =
            static_cast<
                typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<
                    VertexContainerPointerType
                >*
            >( vertex_container_ptr );
        adj_sets_array[undirected] = &( multiset_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
        adj_sets_array[directed] = &( multiset_vertex_mixed_graph_vertex_container_ptr->directed_adj );
    }
    else {
        auto const multiset_vertex_non_mixed_graph_vertex_container_ptr =
            static_cast<
                typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<
                    VertexContainerPointerType
                >*
            >( vertex_container_ptr );
        adj_sets_array[
            vertex_container_graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::undirected ?
            graphdom::edge_type::undirected :
            graphdom::edge_type::directed
        ] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
    }
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list::adj_list(
    const graphdom::multiset_graph<VertexType>* const vertex_container_graph_owner_ptr,
    const VertexContainerPointerType vertex_container_ptr,
    const typename graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type,
    const graphdom::edge_type edges_type_selected) :
    vertex_container_graph_owner(vertex_container_graph_owner_ptr),
    vertex_container_graph_owner_edges_type(vertex_container_graph_owner_edges_type),
    vertex_container_ptr(vertex_container_ptr),
    adj_sets_array({nullptr,nullptr}) {
    if ( vertex_container_ptr == nullptr ) {
        throw std::runtime_error("Impossible to create adj_list"); //TODO: write a better message
    }
    if ( vertex_container_graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::mixed ) {
        auto const multiset_vertex_mixed_graph_vertex_container_ptr =
            static_cast<
                typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<
                    VertexContainerPointerType
                >*
            >( vertex_container_ptr );
        switch( edges_type_selected ) {
            case graphdom::edge_type::undirected:
                adj_sets_array[graphdom::edge_type::undirected] = &( multiset_vertex_mixed_graph_vertex_container_ptr->undirected_adj );
                break;
            case graphdom::edge_type::directed:
                adj_sets_array[graphdom::edge_type::directed] = &( multiset_vertex_mixed_graph_vertex_container_ptr->directed_adj );
                break;
        }
    }
    else {
        auto const multiset_vertex_non_mixed_graph_vertex_container_ptr =
            static_cast<
                typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<
                    VertexContainerPointerType
                >*
            >( vertex_container_ptr );
        if ( vertex_container_graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::undirected ) {
            if ( edges_type_selected == graphdom::edge_type::undirected ) {
                adj_sets_array[graphdom::edge_type::undirected] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
            }
        }
        else {
            if ( edges_type_selected == graphdom::edge_type::directed ) {
                adj_sets_array[graphdom::edge_type::directed] = &( multiset_vertex_non_mixed_graph_vertex_container_ptr->adj );
            }
        }
    }
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const typename graphdom::graph<VertexType>::adj_list_iterator& other) :
    edge_owner( dynamic_cast< graphdom::multiset_graph<VertexType>* > ( other.edge_owner ) ),
    graph_owner_edges_type( other.graph_owner_edges_type ),
    vertex_container_adj_sets_ptr_array( {nullptr,nullptr} ),
    current_edge_type( other.current_edge_type ) {
    auto& other_multiset_vertex_graph_edge_info = std::get<
        graphdom::graph<VertexType>::adj_list_iterator::multiset_vertex_graph_edge_info
    >( other.type_dependent_edge_info );
    auto& other_begin_point = std::get<
        VertexContainerPointerType
    >( other_multiset_vertex_graph_edge_info );
    auto& other_inner_itr = std::get<
        graphdom::graph<VertexType>::adj_list_iterator::multiset_vertex_graph_inner_edge_iterator_type
    >( other_multiset_vertex_graph_edge_info );
    vertex_container_adj_sets_ptr_array = std::get<
         graphdom::graph<VertexType>::adj_list_iterator::multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type
    >( other_multiset_vertex_graph_edge_info );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::multiset_graph<VertexType>::adj_list_iterator::operator*() const {
    auto& real_inner_itr = std::get< real_multiset_vertex_graph_vertex_container_edge_iterator_type >( inner_edge_iterator );
    if ( graph_owner_edges_type == graphdom::graph<VertexType>::graph_edges_type::mixed ) {
        return graphdom::multiset_graph<VertexType>::vertex_handle(
            edge_owner,
            *(
                static_cast<
                    typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<
                        VertexContainerPointerType
                    >*
                >(
                    (*(*real_inner_itr)).vertex_container_ptr
                )
            )
        );
    }
    return graphdom::multiset_graph<VertexType>::vertex_handle(
        edge_owner,
        *(
            static_cast<
                typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<
                    VertexContainerPointerType
                >
                *
            >(
                (*(*real_inner_itr)).vertex_container_ptr
            )
        ),
        current_edge_type
    );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::multiset_graph<VertexType>::adj_list_iterator::operator->() const {
    return *(*this);
}

template<typename VertexType>
bool graphdom::multiset_graph<VertexType>::adj_list_iterator::operator==(
    const typename graphdom::graph<VertexType>::adj_list_const_iterator& other) const {
    return typename graphdom::graph<VertexType>::adj_list_const_iterator(*this) == other;
}

template<typename VertexType>
bool graphdom::multiset_graph<VertexType>::adj_list_iterator::operator!=(
    const typename graphdom::graph<VertexType>::adj_list_const_iterator& other) const {
    return ! ( (*this) == other );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator&
graphdom::multiset_graph<VertexType>::adj_list_iterator::operator=(
    const typename graphdom::graph<VertexType>::adj_list_iterator& other) {
    auto& other_multiset_vertex_graph_edge_info = std::get<
        typename graphdom::graph<VertexType>::adj_list_iterator::multiset_vertex_graph_edge_info
    >( other.type_dependent_edge_info );
    edge_owner = dynamic_cast< const graphdom::multiset_graph<VertexType>* > ( other.edge_owner );
    graph_owner_edges_type = other.graph_owner_edges_type;
    current_edge_type = other.current_edge_type;
    auto& other_begin_point = std::get<
        VertexContainerPointerType
    >( other_multiset_vertex_graph_edge_info );
    edge_vertex_container_owner = other_begin_point;
    auto& other_inner_itr = std::get<
        typename graphdom::graph<VertexType>::adj_list_iterator::multiset_vertex_graph_inner_edge_iterator_type
    >( other_multiset_vertex_graph_edge_info );
    inner_edge_iterator = other_inner_itr;
    vertex_container_adj_sets_ptr_array = std::get<
         typename graphdom::graph<VertexType>::adj_list_iterator::multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type
    >( other_multiset_vertex_graph_edge_info );
    return (*this);
}


template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator&
graphdom::multiset_graph<VertexType>::adj_list_iterator::operator++() {
    auto& real_inner_itr = std::get< real_multiset_vertex_graph_vertex_container_edge_iterator_type >( inner_edge_iterator );
    if ( current_edge_type == undirected ) {
        if ( std::next( real_inner_itr ) == ( vertex_container_adj_sets_ptr_array[undirected]->end() ) ) {
            if ( vertex_container_adj_sets_ptr_array[directed] != nullptr ) {
                if ( ! vertex_container_adj_sets_ptr_array[directed]->empty() ) {
                    real_inner_itr = vertex_container_adj_sets_ptr_array[directed]->begin();
                    current_edge_type = graphdom::edge_type::directed;
                }
            }
        }
    }
    ++real_inner_itr;
    return *this;
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_list_iterator
graphdom::multiset_graph<VertexType>::adj_list_iterator::operator++(int) {
    auto this_before_increment = *(this);
    ++(*this);
    return this_before_increment;
}

template<typename VertexType>
graphdom::edge_type graphdom::multiset_graph<VertexType>::adj_list_iterator::edge_type() const {
    return current_edge_type;
}

template<typename VertexType>
graphdom::multiset_graph<VertexType>::adj_list_iterator::adj_list_iterator(
    const graphdom::multiset_graph<VertexType>* const edge_multiset_vertex_graph_owner_ptr,
    const VertexContainerPointerType edge_begin_point_ptr,
    const typename graphdom::graph<VertexType>::graph_edges_type edge_multiset_vertex_graph_owner_edges_type,
    const std::array<
        typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>*,
        2
    >& edge_begin_point_adj_sets_array_ptr,
    const typename graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator) :
    edge_owner(edge_multiset_vertex_graph_owner_ptr),
    edge_vertex_container_owner(edge_begin_point_ptr),
    graph_owner_edges_type(edge_multiset_vertex_graph_owner_edges_type),
    inner_edge_iterator( std::in_place_type<special_begin_end_indicator> ),
    vertex_container_adj_sets_ptr_array(edge_begin_point_adj_sets_array_ptr) {
    if ( edge_begin_point_adj_sets_array_ptr[undirected] == nullptr && edge_begin_point_adj_sets_array_ptr[directed] == nullptr ) {
        current_edge_type = ( edge_multiset_vertex_graph_owner_edges_type == undirected )? graphdom::edge_type::undirected : graphdom::edge_type::directed;
    }
    else {
        switch( begin_or_end_indicator ) {
            case graphdom::graph<VertexType>::begin_or_end::begin :
                if ( edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[undirected]->empty() && edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                        if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() ) {
                            inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->begin() );
                            current_edge_type =  graphdom::edge_type::undirected;
                        }
                        else {
                            inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->begin() );
                            current_edge_type =  graphdom::edge_type::directed;
                        }
                    }
                    else {
                        // ( edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) && ( !edge_begin_point_adj_sets_array_ptr[undirected]->empty() || edge_begin_point_adj_sets_array_ptr[directed] == nullptr )
                        inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->begin() );
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                }
                else {
                    // edge_begin_point_adj_sets_array_ptr[undirected] == nullptr && edge_begin_point_adj_sets_array_ptr[directed] != nullptr
                    inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->begin() );
                    current_edge_type = directed;
                }
                break;
            case graphdom::graph<VertexType>::begin_or_end::end :
                if ( edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) {
                    if ( edge_begin_point_adj_sets_array_ptr[directed]->empty() && edge_begin_point_adj_sets_array_ptr[undirected] != nullptr ) {
                        inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->end() );
                        current_edge_type = graphdom::edge_type::undirected;
                    }
                    else {
                        // ( edge_begin_point_adj_sets_array_ptr[directed] != nullptr ) && ( !edge_begin_point_adj_sets_array_ptr[directed]->empty() || edge_begin_point_adj_sets_array_ptr[undirected] == nullptr )
                        inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[directed]->end() );
                        current_edge_type = graphdom::edge_type::directed;
                    }
                }
                else {
                    // edge_begin_point_adj_sets_array_ptr[undirected] != nullptr && edge_begin_point_adj_sets_array_ptr[directed] == nullptr
                    inner_edge_iterator = ( edge_begin_point_adj_sets_array_ptr[undirected]->end() );
                    current_edge_type = graphdom::edge_type::undirected;
                }
                break;
        }
    }
}

#endif //GRAPHDOM_HANDLERS_IMPLEMENTATIONS_H