#ifndef MULTISET_VERTEX_GRAPH_ADJ_LIST_H
#define MULTISET_VERTEX_GRAPH_ADJ_LIST_H

#include "graph.h"
#include "multiset_vertex_graph.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST {
    public:
        ADJ_LIST() = delete;
        ADJ_LIST(const ADJ_LIST&);
        explicit ADJ_LIST(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST;
};

//TODO: class implementation

#endif //MULTISET_VERTEX_GRAPH_ADJ_LIST_H