/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_ADJ_LIST_H
#define GRAPHDOM_ADJ_LIST_H

#include "../graph.h"
#include "vertex_container.h"
#include "base_adj_list.h"
#include "../multiset_graph.h"
#include "multiset_graph_adj_list.h"

namespace graphdom {
    template <typename VertexType>
    class graph<VertexType>::adj_list : public graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* > {
        public:
            adj_list() = delete;
            adj_list(const adj_list& other);
            adj_list(const typename multiset_graph<VertexType>::adj_list& other);

            ~adj_list() = default;

            explicit operator typename multiset_graph<VertexType>::adj_list() const;

            [[nodiscard]] graph<VertexType>::adj_list_iterator begin() const;
            [[nodiscard]] graph<VertexType>::adj_list_iterator end() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator cbegin() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator cend() const;

            /// \cond DEV_DOC
            friend typename graph<VertexType>::const_adj_list;
            friend typename multiset_graph<VertexType>::adj_list;
            friend typename graph<VertexType>::vertex_handle;
            /// \endcond DEV_DOC
        private:
            adj_list(
                const graph<VertexType>* adj_list_owner_graph_pointer,
                graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
                const graph<VertexType>::vertex_container* adj_list_common_begin_point_vertex_container_pointer,
                typename graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection = none
            );
    };
}

#include "impl/adj_list.h"

#endif //GRAPHDOM_ADJ_LIST_H