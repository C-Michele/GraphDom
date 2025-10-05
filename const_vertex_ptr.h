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

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list() const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type, Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type, Compare comp) const;
};

//TODO: class implementation

#endif //CONST_VERTEX_PTR_H