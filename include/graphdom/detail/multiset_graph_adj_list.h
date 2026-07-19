/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_H
#define GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_H

#include "../graph.h"
#include "vertex_container.h"
#include "base_adj_list.h"
#include "../multiset_graph.h"

namespace graphdom {
    template <typename VertexType>
    class multiset_graph<VertexType>::adj_list : public graph<VertexType>::template base_adj_list< typename graph<VertexType>::vertex_container* > {
        public:
            adj_list() = delete;
            adj_list(const adj_list& other);
            explicit adj_list(const typename graph<VertexType>::adj_list& other);

            ~adj_list() = default;

            [[nodiscard]] multiset_graph<VertexType>::adj_list_iterator begin() const;
            [[nodiscard]] multiset_graph<VertexType>::adj_list_iterator end() const;
            [[nodiscard]] typename graph<VertexType>::adj_list_const_iterator cbegin() const;
            [[nodiscard]] typename graph<VertexType>::adj_list_const_iterator cend() const;

            friend class graph<VertexType>::const_adj_list;
            friend class graph<VertexType>::adj_list;
            friend class multiset_graph<VertexType>::vertex_handle;
        private:
            adj_list(
                const graph<VertexType>* adj_list_owner_graph_pointer,
                typename graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
                typename graph<VertexType>::vertex_container* adj_list_common_begin_point_vertex_container_pointer,
                typename graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection = graph<VertexType>::edges_type_selection_type::none
            );
    };
}

#include "impl/multiset_graph_adj_list.h"

#endif //GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_H