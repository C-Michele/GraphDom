#ifndef HANDLERS_IMPLEMENTATIONS_H
#define HANDLERS_IMPLEMENTATIONS_H

#include <stdexcept>

#include "graph.h"
#include "handlers_declarations.h"

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    set_graph_vertex_container(nullptr),
    multiset_graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME() const {
    return typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME(*this);
}

template<typename VertexType>
const VertexType& MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator*() const {
    if (set_graph_vertex_container!=nullptr) {
        return set_graph_vertex_container->vertex;
    }
    if (multiset_graph_vertex_container!=nullptr) {
        return multiset_graph_vertex_container->vertex;
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
const VertexType* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator->() const {
    if (set_graph_vertex_container!=nullptr) {
        return &(set_graph_vertex_container->vertex);
    }
    if (multiset_graph_vertex_container!=nullptr) {
        return &(multiset_graph_vertex_container->vertex);
    }
    throw std::runtime_error("Impossible to dereference a vertex_ptr"); //TODO: write a better message
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator==(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    if (vertex_owner != other.vertex_owner ) {
        return false;
    }
    if (set_graph_vertex_container != nullptr ) {
        return set_graph_vertex_container == other.graph_vertex_container;
    }
    return multiset_graph_vertex_container == other.graph_vertex_container;
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator!=(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& other) const {
    return ! ( (*this) == other );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::adj_list() const {
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
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::adj_list(const MAIN_LIBRARY_NAMESPACE::edge_type et) const {
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
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::const_adj_list() const {
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
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::const_adj_list(const MAIN_LIBRARY_NAMESPACE::edge_type et) const {
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
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vc_ref,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) :
    vertex_owner(vo),
    set_graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    multiset_graph_vertex_container(nullptr) {
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
    set_graph_vertex_container(static_cast<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>(&vc_ref)),
    multiset_graph_vertex_container(nullptr),
    edges_type(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type::mixed) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(nullptr),
    edges_type(other.edges_type) {
    if (other.set_graph_vertex_container != nullptr) {
        graph_vertex_container = other.set_graph_vertex_container;
    }else {
        graph_vertex_container = other.multiset_graph_vertex_container;
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
    set_graph_vertex_container(nullptr),
    set_graph_undirected_adj(nullptr),
    set_graph_directed_adj(nullptr),
    multiset_graph_vertex_container(other.multiset_graph_vertex_container),
    multiset_graph_undirected_adj(other.multiset_graph_undirected_adj),
    multiset_graph_directed_adj(other.multiset_graph_directed_adj) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST::ADJ_LIST(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* const vc_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type ge_type) :
    vertex_owner(vo),
    set_graph_vertex_container(vc_ptr),
    set_graph_undirected_adj(nullptr),
    set_graph_directed_adj(nullptr),
    multiset_graph_vertex_container(nullptr),
    multiset_graph_undirected_adj(nullptr),
    multiset_graph_directed_adj(nullptr) {
    switch(ge_type) {
        case mixed:
            set_graph_undirected_adj =
                 &(
                    static_cast<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                    >(vc_ptr)->undirected_adj
                 );
            set_graph_directed_adj =
                &(
                    static_cast<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                    >(vc_ptr)->directed_adj
                );
            break;
        case undirected:
            set_graph_undirected_adj =
                 &(
                     static_cast<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                     >(vc_ptr)->adj
                 );
            break;
        case directed:
            set_graph_directed_adj =
                 &(
                     static_cast<
                        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                     >(vc_ptr)->adj
                 );
            break;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST::ADJ_LIST(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* const vc_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type ge_type) :
    vertex_owner(vo),
    set_graph_vertex_container(nullptr),
    set_graph_undirected_adj(nullptr),
    set_graph_directed_adj(nullptr),
    multiset_graph_vertex_container(vc_ptr),
    multiset_graph_undirected_adj(nullptr),
    multiset_graph_directed_adj(nullptr) {
    switch(ge_type) {
        case mixed:
            multiset_graph_undirected_adj =
                 &(
                     static_cast<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                     >(vc_ptr) -> undirected_adj
                 );
            multiset_graph_directed_adj =
                &(
                    static_cast<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                    >(vc_ptr)->directed_adj
                );
            break;
        case undirected:
            multiset_graph_undirected_adj =
                 &(
                     static_cast<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                     >(vc_ptr)->adj
                 );
            break;
        case directed:
            multiset_graph_directed_adj =
                 &(
                     static_cast<
                        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                        >
                        *
                     >(vc_ptr)->adj
                 );
            break;
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST::CONSTANT_ADJ_LIST(const ADJ_LIST& other) :
vertex_owner(other.vertex_owner),
vertex_container(nullptr),
set_graph_undirected_adj(nullptr),
set_graph_directed_adj(nullptr),
multiset_graph_undirected_adj(nullptr),
multiset_graph_directed_adj(nullptr) {
    if ( vertex_owner != nullptr ) {
        if ( other.set_graph_vertex_container != nullptr ) {
            vertex_container = other.set_graph_vertex_container;
            set_graph_undirected_adj = other.set_graph_undirected_adj;
            set_graph_directed_adj = other.set_graph_directed_adj;
        }
        else {
            vertex_container = other.multiset_graph_vertex_container;
            multiset_graph_undirected_adj = other.multiset_graph_undirected_adj;
            multiset_graph_directed_adj = other.multiset_graph_directed_adj;
        }
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST::CONSTANT_ADJ_LIST(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST& other ) :
    vertex_owner(other.vertex_owner),
    vertex_container(other.multiset_graph_vertex_container),
    set_graph_undirected_adj(nullptr),
    set_graph_directed_adj(nullptr),
    multiset_graph_undirected_adj(other.multiset_graph_undirected_adj),
    multiset_graph_directed_adj(other.multiset_graph_directed_adj){}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST::CONSTANT_ADJ_LIST(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const vo,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* const vc_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type ge_type) :
    vertex_owner(vo),
    vertex_container(vc_ptr),
    set_graph_undirected_adj(nullptr),
    set_graph_directed_adj(nullptr),
    multiset_graph_undirected_adj(nullptr),
    multiset_graph_directed_adj(nullptr) {
    if ( dynamic_cast<const MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>*>(vertex_owner) != nullptr ) {
        switch(ge_type) {
            case mixed:
                set_graph_undirected_adj =
                     &(
                        static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                        >(vc_ptr)->undirected_adj
                     );
                set_graph_directed_adj =
                    &(
                        static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                        >(vc_ptr)->directed_adj
                    );
                break;
            case undirected:
                set_graph_undirected_adj =
                     &(
                         static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                         >(vc_ptr)->adj
                     );
                break;
            case directed:
                set_graph_directed_adj =
                     &(
                         static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                         >(vc_ptr)->adj
                     );
                break;
        }

    }
    else {
        switch(ge_type) {
            case mixed:
                multiset_graph_undirected_adj =
                     &(
                         static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                         >(vc_ptr) -> undirected_adj
                     );
                multiset_graph_directed_adj =
                    &(
                        static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<
                                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                        >(vc_ptr)->directed_adj
                    );
                break;
            case undirected:
                multiset_graph_undirected_adj =
                     &(
                         static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                         >(vc_ptr)->adj
                     );
                break;
            case directed:
                multiset_graph_directed_adj =
                     &(
                         static_cast<
                            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<
                                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
                            >
                            *
                         >(vc_ptr)->adj
                     );
                break;
        }
    }
}


template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME::VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(dynamic_cast<const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*>(other.vertex_owner)),
    multiset_graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type) {
    if ( vertex_owner == nullptr ) {
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
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::const_vertex_ptr& other) const {
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
    multiset_graph_vertex_container(other.multiset_graph_vertex_container),
    multiset_graph_undirected_adj(other.multiset_graph_undirected_adj),
    multiset_graph_directed_adj(other.multiset_graph_directed_adj) {
    if ( vertex_owner == nullptr ) {
        throw std::runtime_error("Impossible to convert"); //TODO: write a better message
    }
}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST::ADJ_LIST(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vo_ptr,
    const VertexContainerPointerType vc_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type ge_type):
    vertex_owner(vo_ptr),
    multiset_graph_vertex_container(vc_ptr),
    multiset_graph_undirected_adj(nullptr),
    multiset_graph_directed_adj(nullptr) {
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
}

#endif //HANDLERS_IMPLEMENTATIONS_H