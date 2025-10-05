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

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list() const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list(Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type, Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(Compare comp) const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type) const;
        template <typename Compare>
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::graph<VertexType>::edge_type, Compare comp) const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME;
};

//TODO: class implementation

#endif //VERTEX_PTR_H