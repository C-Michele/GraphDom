#ifndef GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_H
#define GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_H

#include "../graph.h"
#include "adj_list_base_iterator.h"
#include "../multiset_graph.h"

namespace graphdom {
    template <typename VertexType>
    class multiset_graph<VertexType>::adj_list_iterator final : public graph<VertexType>::template adj_list_base_iterator<typename graph<VertexType>::vertex_container* > {
        public:
            adj_list_iterator() = default;
            adj_list_iterator(const adj_list_iterator& other);
            adj_list_iterator(const typename graph<VertexType>::adj_list_iterator& other);

            ~adj_list_iterator() = default;

            multiset_graph<VertexType>::vertex_handle operator->() const;
            multiset_graph<VertexType>::vertex_handle operator*() const;

            adj_list_iterator& operator=(const adj_list_iterator& other);
            adj_list_iterator& operator++();
            [[nodiscard]] adj_list_iterator operator++(int);

            friend class graph<VertexType>::adj_list_const_iterator;
            friend class graph<VertexType>::adj_list_iterator;
            friend class multiset_graph<VertexType>::adj_list;
        private:
            adj_list_iterator( const typename graph<VertexType>::template adj_list_base_iterator<typename graph<VertexType>::vertex_container* >& other );
            adj_list_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type
            );
            adj_list_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::template adj_set<typename graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );
    };
}

#include "impl/multiset_graph_adj_list_iterator.h"

#endif //GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_H