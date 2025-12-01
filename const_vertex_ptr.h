#ifndef CONST_VERTEX_PTR_H
#define CONST_VERTEX_PTR_H

#include "graph.h"
#include "multiset_vertex_graph.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME final {
    public:
        CONSTANT_VERTEX_PTR_NAME() = delete;
        CONSTANT_VERTEX_PTR_NAME(const CONSTANT_VERTEX_PTR_NAME&) = default;
        CONSTANT_VERTEX_PTR_NAME(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME&);
        CONSTANT_VERTEX_PTR_NAME(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME&);

        [[nodiscard]] const VertexType& operator*() const;
        [[nodiscard]] const VertexType* operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_VERTEX_PTR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_VERTEX_PTR_NAME&) const;

        CONSTANT_VERTEX_PTR_NAME& operator=(const CONSTANT_VERTEX_PTR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list() const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>;
    private:
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
            MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
        );
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
        );
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<vertex_container*>&,
            MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
        );
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<vertex_container*>&
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* vertex_owner;
        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* graph_vertex_container;
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type edges_type;
};

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type) {}

template<typename VertexType>
MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME::CONSTANT_VERTEX_PTR_NAME(
    const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME& other) :
    vertex_owner(other.vertex_owner),
    graph_vertex_container(other.multiset_graph_vertex_container),
    edges_type(other.edges_type){}

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

//TODO: class implementation

#endif //CONST_VERTEX_PTR_H