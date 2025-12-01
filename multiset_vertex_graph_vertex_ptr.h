#ifndef MULTISET_VERTEX_GRAPH_VERTEX_PTR_H
#define MULTISET_VERTEX_GRAPH_VERTEX_PTR_H

#include <stdexcept>

#include "graph.h"
#include "multiset_vertex_graph.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME final {
    public:
        VERTEX_PTR_NAME() = delete;
        VERTEX_PTR_NAME(const VERTEX_PTR_NAME&) = default;
        explicit VERTEX_PTR_NAME(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME&);

        [[nodiscard]] VertexType& operator*() const;
        [[nodiscard]] VertexType* operator->() const;
        [[nodiscard]] bool operator==(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;
        [[nodiscard]] bool operator!=(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;

        VERTEX_PTR_NAME& operator=(const VERTEX_PTR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list() const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list(Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const;
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const;
        template <typename Compare>
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(Compare comp) const;
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const;
        template <typename Compare>
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>;
    private:
        VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
            MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
        );
        VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
        );

        const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vertex_owner;
        VertexContainerPointerType multiset_graph_vertex_container;
        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type edges_type;
};

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

//TODO: class implementation

#endif //MULTISET_VERTEX_GRAPH_VERTEX_PTR_H