#ifndef HANDLERS_IMPLEMENTATIONS_H
#define HANDLERS_IMPLEMENTATIONS_H

#include <stdexcept>

#include "graph.h"
#include "handlers_declarations.h"

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    vertex_container_ptr(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME() const {
    return typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME(*this);
}

template<typename VertexType>
const VertexType& MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator*() const {
    if ( std::holds_alternative<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex;
    }
    if ( std::holds_alternative<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex;
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
const VertexType* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator->() const {
    if ( std::holds_alternative<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return &( std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex );
    }
    if ( std::holds_alternative<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return &( std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr )->vertex );
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator==(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    if ( std::holds_alternative<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return
            ( vertex_owner == other.vertex_owner ) &&
            ( std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) == other.graph_vertex_container );
    }
    if ( std::holds_alternative<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        return
            ( vertex_owner == other.vertex_owner ) &&
            ( std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) == other.graph_vertex_container );
    }
    return ( vertex_owner == other.vertex_owner ) && ( nullptr == other.graph_vertex_container );
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator!=(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    return ! ( (*this) == other );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::adj_list() const {
    if ( vertex_owner==nullptr || std::holds_alternative<std::monostate>(vertex_container_ptr) ) {
        throw std::runtime_error("Impossible to get adj_list from this vertex_ptr"); //TODO: write a better message
    }
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST(
        vertex_owner,
        vertex_container_ptr,
        edges_type
    );
    /*
    if (vertex_owner!=nullptr) {
        if (set_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST(
                vertex_owner,
                set_graph_vertex_container,
                edges_type
            );
        }
        if (multiset_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST(
                vertex_owner,
                multiset_graph_vertex_container,
                edges_type
            );
        }
    }
    throw std::runtime_error("Impossible to get adj_list from this vertex_ptr"); //TODO: write a better message
    */
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::adj_list(const MAIN_LIBRARY_NAMESPACE::edge_type et) const {
    if ( vertex_owner==nullptr || std::holds_alternative<std::monostate>(vertex_container_ptr) ) {
        throw std::runtime_error("Impossible to get adj_list from this vertex_ptr"); //TODO: write a better message
    }
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST(
        vertex_owner,
        vertex_container_ptr,
        et
    );
    /*
    if (vertex_owner!=nullptr) {
        if (set_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST(
                vertex_owner,
                set_graph_vertex_container,
                et
            );
        }
        if (multiset_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST(
                vertex_owner,
                multiset_graph_vertex_container,
                et
            );
        }
    }
    throw std::runtime_error("Impossible to get adj_list from this vertex_ptr"); //TODO: write a better message
    */
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::const_adj_list() const {
    if (vertex_owner==nullptr || std::holds_alternative<std::monostate>(vertex_container_ptr) ) {
        throw std::runtime_error("Impossible to get const_adj_list from this vertex_ptr"); //TODO: write a better message
    }
    if ( std::holds_alternative<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr) ) {
        return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
            vertex_owner,
            std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr),
            edges_type
        );
    }
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
        vertex_owner,
        std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr),
        edges_type
    );
    /*
    if (vertex_owner!=nullptr) {
        if (set_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
                vertex_owner,
                set_graph_vertex_container,
                edges_type
            );
        }
        if (multiset_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
                vertex_owner,
                multiset_graph_vertex_container,
                edges_type
            );
        }
    }
    throw std::runtime_error("Impossible to get const_adj_list from this vertex_ptr"); //TODO: write a better message
    */
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::const_adj_list(const MAIN_LIBRARY_NAMESPACE::edge_type et) const {
    if (vertex_owner==nullptr || std::holds_alternative<std::monostate>(vertex_container_ptr) ) {
        throw std::runtime_error("Impossible to get const_adj_list from this vertex_ptr"); //TODO: write a better message
    }
    if ( std::holds_alternative<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr) ) {
        return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
            vertex_owner,
            std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr),
            et
        );
    }
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
        vertex_owner,
        std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr),
        et
    );
    /*
    if (vertex_owner!=nullptr) {
        if (set_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
                vertex_owner,
                set_graph_vertex_container,
                et
            );
        }
        if (multiset_graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
                vertex_owner,
                multiset_graph_vertex_container,
                et
            );
        }
    }
    throw std::runtime_error("Impossible to get const_adj_list from this vertex_ptr"); //TODO: write a better message
    */
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vc_ref,
    const MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type) :
    vertex_owner(vo),
    vertex_container_ptr(&vc_ref) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vc_ref) :
    vertex_owner(vo),
    vertex_container_ptr(&vc_ref),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(nullptr),
    edges_type(other.edges_type) {
    if ( std::holds_alternative< const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* >( other.vertex_container_ptr ) ) {
        graph_vertex_container = std::get< const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* >( other.vertex_container_ptr );
    }
    else if ( std::holds_alternative< MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* >( other.vertex_container_ptr ) ) {
        graph_vertex_container = std::get< MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* >( other.vertex_container_ptr );
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

template<typename VertexType>
const VertexType& MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator*() const {
    if (graph_vertex_container!=nullptr) {
        return graph_vertex_container->vertex;
    }
    throw std::runtime_error("Impossible to dereference a const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
const VertexType* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator->() const {
    if (graph_vertex_container!=nullptr) {
        return &(graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator==(const CONSTANT_VERTEX_PTR_NAME& other) const {
    return (vertex_owner == other.vertex_owner) && (graph_vertex_container == other.graph_vertex_container);
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::operator!=(const CONSTANT_VERTEX_PTR_NAME& other) const {
    return !( (*this)== other );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::adj_list() const {
    return const_adj_list();
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::adj_list(const MAIN_LIBRARY_NAMESPACE::edge_type et) const {
    return const_adj_list(et);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::const_adj_list() const {
    if (vertex_owner!=nullptr) {
        if (graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
                vertex_owner,
                graph_vertex_container,
                edges_type
            );
        }
    }
    throw std::runtime_error("Impossible to get const_adj_list from this const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::const_adj_list(const MAIN_LIBRARY_NAMESPACE::edge_type et) const {
    if (vertex_owner!=nullptr) {
        if (graph_vertex_container!=nullptr) {
            return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
                vertex_owner,
                graph_vertex_container,
                et
            );
        }
    }
    throw std::runtime_error("Impossible to get const_adj_list from this const_vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vc_ref) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const vo ,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<vertex_container*>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const multiset_vertex_graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<vertex_container*>& vc_ref) :
    vertex_owner(vo),
    graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST::ADJ_LIST(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST& other) :
    vertex_owner(other.vertex_owner),
    vertex_info(
        std::in_place_type<
            std::pair<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >
        >,
        other.multiset_graph_vertex_container,
        {nullptr,nullptr}
    ) {
        auto& adj_sets_array =
            std::get<
                std::pair<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                    std::array<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                        2
                    >
                >
            >(vertex_info).second;
        adj_sets_array[undirected] = other.multiset_graph_undirected_adj;
        adj_sets_array[directed] = other.multiset_graph_directed_adj;
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST::ADJ_LIST(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vertex_owner_ptr,
    const std::variant<
        std::monostate,
        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
    >& vertex_container_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type vertex_owner_edges_type ) :
    vertex_owner(vertex_owner_ptr) {
    if ( std::holds_alternative<std::monostate>( vertex_container_ptr ) ) {
        throw std::runtime_error("Impossibile to create ADJ_LIST"); //TODO: write a better message
    }
    if ( std::holds_alternative<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>( vertex_container_ptr ) ) {
        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* const explicit_vertex_container_ptr =
            std::get<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr);
        vertex_info.template emplace<
            std::pair<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >
        >( explicit_vertex_container_ptr, {nullptr,nullptr} );
        auto& adj_sets_array =
            std::get<
                std::pair<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                    std::array<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                        2
                    >
                >
            >(vertex_info).second;
        if ( vertex_owner_edges_type == mixed ) {
            adj_sets_array[undirected] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(explicit_vertex_container_ptr)->undirected_adj
                );
            adj_sets_array[directed] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(explicit_vertex_container_ptr)->directed_adj
            );
        }
        else {
            adj_sets_array[vertex_owner_edges_type] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(explicit_vertex_container_ptr)->adj
            );
        }
    }
    else {
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* const explicit_vertex_container_ptr =
            std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(vertex_container_ptr);
        vertex_info.template emplace<
            std::pair<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >
        >( explicit_vertex_container_ptr, {nullptr,nullptr} );
        auto& adj_sets_array =
            std::get<
                std::pair<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                    std::array<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                        2
                    >
                >
            >(vertex_info).second;
        if ( vertex_owner_edges_type == mixed ) {
            adj_sets_array[undirected] = &(
                static_cast<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(explicit_vertex_container_ptr)->undirected_adj
                );
            adj_sets_array[directed] = &(
                static_cast<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(explicit_vertex_container_ptr)->directed_adj
            );
        }
        else {
            adj_sets_array[vertex_owner_edges_type] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(explicit_vertex_container_ptr)->adj
            );
        }
    }
}


template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST::CONSTANT_ADJ_LIST(const ADJ_LIST& other) :
vertex_owner(other.vertex_owner),
vertex_container(nullptr) {
    if (
        std::holds_alternative<
            std::pair<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >
        >(other.vertex_info)
    ) {
        auto& other_specific_vertex_info =
            std::get<
                std::pair<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                    std::array<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                        2
                    >
                >
            >(other.vertex_info);
        vertex_container = other_specific_vertex_info.first;
        auto& other_adj_sets_array = other_specific_vertex_info.second;
        vertex_info.template emplace<
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >
        >({nullptr,nullptr});
        auto& this_specific_vertex_info =
            std::get<
                std::array<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >(vertex_info);
        this_specific_vertex_info[undirected] = other_adj_sets_array[undirected];
        this_specific_vertex_info[directed] = other_adj_sets_array[directed];
    }
    else {
        auto& other_specific_vertex_info =
            std::get<
                std::pair<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                    std::array<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                        2
                    >
                >
            >(other.vertex_info);
        vertex_container = other_specific_vertex_info.first;
        auto& other_adj_sets_array = other_specific_vertex_info.second;
        vertex_info.template emplace<
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >
        >({nullptr,nullptr});
        auto& this_specific_vertex_info =
            std::get<
                std::array<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >(vertex_info);
        this_specific_vertex_info[undirected] = other_adj_sets_array[undirected];
        this_specific_vertex_info[directed] = other_adj_sets_array[directed];
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST::CONSTANT_ADJ_LIST(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST& other ) :
    vertex_owner(other.vertex_owner),
    vertex_container(other.multiset_graph_vertex_container),
    vertex_info(
        std::in_place_type<
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >
        >,
        {nullptr,nullptr}
    ) {
    auto& this_adj_sets_array =
        std::get<
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >
        >(vertex_info);
    this_adj_sets_array[undirected] = other.adj_sets_array[undirected];
    this_adj_sets_array[directed] = other.adj_sets_array[directed];
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST::CONSTANT_ADJ_LIST(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* const vc_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type ge_type) :
    vertex_owner(vo),
    vertex_container(vc_ptr) {
    if ( vo == nullptr || vc_ptr == nullptr) {
        throw std::runtime_error("Impossible to create CONSTANT_ADJ_LIST"); //TODO: write a better message
    }
    if ( dynamic_cast<const MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>*>(vertex_owner) != nullptr ) {
        vertex_info.template emplace<
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >
        >({nullptr,nullptr});
        auto& adj_sets_array =
            std::get<
                std::array<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >(vertex_info);
        if ( ge_type == mixed ) {
            adj_sets_array[undirected] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(vc_ptr)->undirected_adj
            );
            adj_sets_array[directed] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(vc_ptr)->directed_adj
            );
        }
        else {
            adj_sets_array[ge_type] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(vc_ptr)->adj
            );
        }
    }
    else {
        vertex_info.template emplace<
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >
        >({nullptr,nullptr});
        auto& adj_sets_array =
            std::get<
                std::array<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >(vertex_info);
        if ( ge_type == mixed ) {
            adj_sets_array[undirected] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(vc_ptr)->undirected_adj
            );
            adj_sets_array[directed] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(vc_ptr)->directed_adj
            );
        }
        else {
            adj_sets_array[ge_type] = &(
                static_cast<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                    >
                >(vc_ptr)->adj
            );
        }
    }
}


template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner( dynamic_cast< const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* >( other.vertex_owner ) ),
    edges_type( other.edges_type ) {
    if ( std::holds_alternative< typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* >( other.vertex_container_ptr ) ) {
        multiset_graph_vertex_container = std::get< typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* >( other.vertex_container_ptr );
    }
    else if ( std::holds_alternative< std::monostate >( other.vertex_container_ptr ) ) {
        multiset_graph_vertex_container = nullptr;
    }
    else {
        throw std::runtime_error("Impossible to convert"); //TODO: write a better message
    }
}

template<typename VertexType>
VertexType& MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator*() const {
    if (multiset_graph_vertex_container!=nullptr) {
        return multiset_graph_vertex_container->vertex;
    }
    throw std::runtime_error("Impossible to dereference a multiset_vertex_graph::vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
VertexType* MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator->() const {
    if (multiset_graph_vertex_container!=nullptr) {
        return &(multiset_graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a multiset_vertex_graph::vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator==(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    if(vertex_owner!=other.vertex_owner) {
        return false;
    }
    return multiset_graph_vertex_container == other.graph_vertex_container;
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::operator!=(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    return !( (*this) == other );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::adj_list() const {
    if (vertex_owner!=nullptr) {
        if (multiset_graph_vertex_container!=nullptr){
            return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST(
                vertex_owner,
                multiset_graph_vertex_container,
                edges_type
            );
        }
    }
    throw std::runtime_error("Impossible to get adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::adj_list(const MAIN_LIBRARY_NAMESPACE::edge_type et) const {
    if (vertex_owner!=nullptr) {
        if (multiset_graph_vertex_container!=nullptr){
            return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST(
                vertex_owner,
                multiset_graph_vertex_container,
                et
            );
        }
    }
    throw std::runtime_error("Impossible to get adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::const_adj_list() const {
    if (vertex_owner!=nullptr) {
        return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
            vertex_owner,
            multiset_graph_vertex_container,
            edges_type
        );
    }
    throw std::runtime_error("Impossible to get const_adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type et) const {
    if (vertex_owner!=nullptr) {
        return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST(
            vertex_owner,
            multiset_graph_vertex_container,
            et
        );
    }
    throw std::runtime_error("Impossible to get const_adj_list from this multiset_vertex_graph vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vo,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    multiset_graph_vertex_container(static_cast<VertexContainerPointerType>(&vc_ref)) {
    if (non_mixed_graph_type == MAIN_LIBRARY_NAMESPACE::edge_type::undirected) {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::undirected;
    }
    else {
        edges_type = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::directed;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vo,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vc_ref) :
    vertex_owner(vo),
    multiset_graph_vertex_container(static_cast<VertexContainerPointerType>(&vc_ref)),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST::ADJ_LIST(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST& other) :
    vertex_owner(dynamic_cast<const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*>(other.vertex_owner)),
    multiset_graph_vertex_container(other.multiset_graph_vertex_container) {
    if ( vertex_owner == nullptr ) {
        throw std::runtime_error("Impossible to convert"); //TODO: write a better message
    }
    if (
        std::holds_alternative<
            std::pair<
                const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template adj_set<const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >
        >(other.vertex_info)
    ) {
        throw std::runtime_error("Impossible to convert"); //TODO: write a better message
    }
    auto& other_specific_vertex_info =
        std::get<
            std::pair<
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template adj_set<VertexContainerPointerType>*,
                    2
                >
            >
        >(other.vertex_info);
    multiset_graph_vertex_container = other_specific_vertex_info.first;
    auto& other_adj_sets_array = other_specific_vertex_info.second;
    adj_sets_array[undirected] = other_adj_sets_array[undirected];
    adj_sets_array[directed] = other_adj_sets_array[directed];
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST::ADJ_LIST(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vo_ptr,
    const VertexContainerPointerType vc_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type ge_type):
    vertex_owner(vo_ptr),
    multiset_graph_vertex_container(vc_ptr),
    adj_sets_array({nullptr,nullptr}) {
    if ( ge_type != undirected && ge_type != directed ) {
        adj_sets_array[undirected] =
             &(
                 static_cast<
                    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<
                        VertexContainerPointerType
                    >
                    *
                 >(vc_ptr)->undirected_adj
             );
        adj_sets_array[directed] =
             &(
                 static_cast<
                    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<
                        VertexContainerPointerType
                    >
                    *
                 >(vc_ptr)->directed_adj
             );
    }
    else {
        adj_sets_array[ge_type] =
             &(
                 static_cast<
                    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<
                        VertexContainerPointerType
                    >
                    *
                 >(vc_ptr)->adj
             );
    }
    /*
    switch(ge_type) {
        case undirected:
            multiset_graph_undirected_adj =
                 &(
                     static_cast<
                        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<
                            VertexContainerPointerType
                        >
                        *
                     >(vc_ptr)->adj
                 );
            break;
        case directed:
            multiset_graph_directed_adj =
                 &(
                     static_cast<
                        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<
                            VertexContainerPointerType
                        >
                        *
                     >(vc_ptr)->adj
                 );
            break;
        default:
            multiset_graph_undirected_adj =
                 &(
                     static_cast<
                        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<
                            VertexContainerPointerType
                        >
                        *
                     >(vc_ptr)->undirected_adj
                 );
            multiset_graph_directed_adj =
                 &(
                     static_cast<
                        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<
                            VertexContainerPointerType
                        >
                        *
                     >(vc_ptr)->directed_adj
                 );
            break;
    }
    */
}

#endif //HANDLERS_IMPLEMENTATIONS_H