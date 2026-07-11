#ifndef GRAPHDOM_ADJ_LIST_ITERATOR_H
#define GRAPHDOM_ADJ_LIST_ITERATOR_H

#include "../graph.h"
#include "vertex_container.h"
#include "adj_list_base_iterator.h"
#include "../multiset_graph.h"

namespace graphdom {
    template <typename VertexType>
    class graph<VertexType>::adj_list_iterator final : public graph<VertexType>::adj_list_base_iterator< const graph<VertexType>::vertex_container* > {
        public:
            adj_list_iterator() = default;
            adj_list_iterator(const adj_list_iterator& other_iterator);
            adj_list_iterator(const typename multiset_graph<VertexType>::adj_list_iterator& other_iterator);

            ~adj_list_iterator() = default;

            operator typename multiset_graph<VertexType>::adj_list_iterator() const;
            graph<VertexType>::vertex_handle operator->() const;
            graph<VertexType>::vertex_handle operator*() const;

            adj_list_iterator& operator=(const adj_list_iterator& other);
            adj_list_iterator& operator++();
            [[nodiscard]] adj_list_iterator operator++(int);

            friend class graph<VertexType>::adj_list_const_iterator;
            friend class multiset_graph<VertexType>::adj_list_iterator;
            friend class graph<VertexType>::adj_list;
    };
}

#include "impl/adj_list_iterator.h"

#endif //GRAPHDOM_ADJ_LIST_ITERATOR_H