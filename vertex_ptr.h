#ifndef VERTEX_PTR_H
#define VERTEX_PTR_H

#include "graph.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME final {
    public:
        VERTEX_PTR_NAME() = delete;
        VERTEX_PTR_NAME(const VERTEX_PTR_NAME&);

        [[nodiscard]] VertexType& operator*() const;
        [[nodiscard]] VertexType* operator->() const;
        [[nodiscard]] bool operator==(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;
        [[nodiscard]] bool operator!=(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;

        VERTEX_PTR_NAME& operator=(const VERTEX_PTR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME begin(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME end(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME;
};

//TODO: class implementation

#endif //VERTEX_PTR_H