#ifndef GRAPHDOM_ADJ_LIST_CONST_ITERATOR_H
#define GRAPHDOM_ADJ_LIST_CONST_ITERATOR_H

#include "../graph.h"
#include "adj_list_base_iterator.h"
#include "../multiset_graph.h"

namespace graphdom {
    template <typename VertexType>
    class graphdom::graph<VertexType>::adj_list_const_iterator final : public graph<VertexType>::adj_list_base_iterator< const graph<VertexType>::vertex_container* > {
        public:
            adj_list_const_iterator();
            adj_list_const_iterator(const adj_list_const_iterator& other_iterator);
            adj_list_const_iterator(const graph<VertexType>::adj_list_iterator& other_iterator);
            adj_list_const_iterator(const typename multiset_graph<VertexType>::adj_list_iterator& other_iterator);

            ~adj_list_const_iterator() = default;

            graph<VertexType>::vertex_const_handle operator->() const;
            graph<VertexType>::vertex_const_handle operator*() const;

            adj_list_const_iterator& operator=(const adj_list_const_iterator& other);
            adj_list_const_iterator& operator++();
            [[nodiscard]] adj_list_const_iterator operator++(int);

            friend class graph<VertexType>::const_adj_list;
            friend class graph<VertexType>::adj_list;
            friend class multiset_graph<VertexType>::adj_list;
        private:
            adj_list_const_iterator( const graph<VertexType>::adj_list_base_iterator< const graph<VertexType>::vertex_container* >& other );
    };
}

#include "impl/adj_list_const_iterator.h"

#endif //GRAPHDOM_ADJ_LIST_CONST_ITERATOR_H