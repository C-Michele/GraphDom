/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

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

            /// \cond DEV_DOC
            friend class graph<VertexType>::const_adj_list;
            friend class graph<VertexType>::adj_list;
            friend class multiset_graph<VertexType>::adj_list;
            friend class graph<VertexType>;
            friend class set_graph<VertexType>;
            friend class multiset_graph<VertexType>;
            /// \endcond DEV_DOC
        private:
            adj_list_const_iterator( const graph<VertexType>::adj_list_base_iterator< const graph<VertexType>::vertex_container* >& other );
            adj_list_const_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                const typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type
            );
            adj_list_const_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                const typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::template adj_set<typename graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );
            adj_list_const_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                const typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::template adj_set<const typename graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );
    };
}

#include "impl/adj_list_const_iterator.h"

#endif //GRAPHDOM_ADJ_LIST_CONST_ITERATOR_H