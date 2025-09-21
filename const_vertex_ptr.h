#ifndef CONST_VERTEX_PTR_H
#define CONST_VERTEX_PTR_H

#include "graph.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME final {
    public:
        CONSTANT_VERTEX_PTR_NAME() = delete;
        CONSTANT_VERTEX_PTR_NAME(const CONSTANT_VERTEX_PTR_NAME&);
        CONSTANT_VERTEX_PTR_NAME(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME&);

        [[nodiscard]] const VertexType& operator*() const;
        [[nodiscard]] const VertexType* operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_VERTEX_PTR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_VERTEX_PTR_NAME&) const;

        CONSTANT_VERTEX_PTR_NAME& operator=(const CONSTANT_VERTEX_PTR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME begin(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME end(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
};

//TODO: class implementation

#endif //CONST_VERTEX_PTR_H