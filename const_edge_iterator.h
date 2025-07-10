#ifndef CONST_EDGE_ITERATOR_H
#define CONST_EDGE_ITERATOR_H

#include "graph_base.h"
#include "labeled_vertex_multi_vertex_graph.h"
#include "labeled_edge_graph_base.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_EDGE_ITERATOR_NAME final {
    public:
        CONSTANT_EDGE_ITERATOR_NAME() = delete;
        CONSTANT_EDGE_ITERATOR_NAME(const CONSTANT_EDGE_ITERATOR_NAME&);
        CONSTANT_EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME operator*() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_EDGE_ITERATOR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_EDGE_ITERATOR_NAME&) const;

        CONSTANT_EDGE_ITERATOR_NAME& operator=(const CONSTANT_EDGE_ITERATOR_NAME&);
        CONSTANT_EDGE_ITERATOR_NAME& operator++();
        [[nodiscard]] CONSTANT_EDGE_ITERATOR_NAME operator++(int);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::edge_type edge_type() const;
};

//TODO: class implementation

#endif //CONST_EDGE_ITERATOR_H