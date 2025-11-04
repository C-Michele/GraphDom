#ifndef MULTISET_VERTEX_GRAPH_EDGE_ITERATOR_H
#define MULTISET_VERTEX_GRAPH_EDGE_ITERATOR_H

#include "graph.h"
#include "multiset_vertex_graph.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME final {
public:
    EDGE_ITERATOR_NAME() = delete;
    EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&);
    explicit EDGE_ITERATOR_NAME(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME&);

    [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME operator*() const;
    [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME operator->() const;
    [[nodiscard]] bool operator==(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const;
    [[nodiscard]] bool operator!=(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const;

    EDGE_ITERATOR_NAME& operator=(const EDGE_ITERATOR_NAME&);
    EDGE_ITERATOR_NAME& operator++();
    [[nodiscard]] EDGE_ITERATOR_NAME operator++(int);

    [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type edge_type() const;

    friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
    friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST;
    friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME;
};

//TODO: class implementation

#endif //MULTISET_VERTEX_GRAPH_EDGE_ITERATOR_H