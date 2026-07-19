/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_BASE_ADJ_LIST_H
#define GRAPHDOM_BASE_ADJ_LIST_H

#include "../graph.h"
#include "adj_list_base_iterator.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::base_adj_list {
        public:
            static_assert(
                std::is_same< VertexContainerPointerType , graph<VertexType>::vertex_container* >::value ||
                std::is_same< VertexContainerPointerType , const graph<VertexType>::vertex_container* >::value
                ,
                "The typename 'VertexContainerPointerType' of 'graphdom::graph<VertexType>::base_adj_list<VertexContainerPointerType>' class must be a pointer to graphdom::graph<VertexType>::vertex_container"
            );

            base_adj_list() = delete;

            ~base_adj_list() = default;

            base_adj_list& operator=(const base_adj_list&) = delete;
            base_adj_list& operator=(base_adj_list&&) = delete;

            /// \endcond DEV_DOC
            template<typename>
            friend class graph<VertexType>::base_adj_list;
            /// \endcond DEV_DOC
        protected:
            base_adj_list(const base_adj_list&) = default;
            base_adj_list(
                const graph<VertexType>* adj_list_owner_graph_pointer,
                graph_edges_type adj_list_owner_graph_edges_type,
                VertexContainerPointerType adj_list_common_begin_point_vertex_container_pointer,
                graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection = none
            );

            template <typename K>
            constexpr graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType> internal_begin() const;

            template <typename K>
            constexpr graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType> internal_end() const;

            template <typename K>
            constexpr graph<VertexType>::adj_set<K>* get_adj_set_if_accessible(graphdom::edge_type edge_type) const;

            const graph<VertexType>* adj_list_owner_graph_pointer;
            graph_edges_type adj_list_owner_graph_edges_type;
            VertexContainerPointerType adj_list_common_begin_point_vertex_container_pointer;
            edges_type_selection_type adj_list_edges_type_selection;
    };
}

#include "impl/base_adj_list.h"

#endif //GRAPHDOM_BASE_ADJ_LIST_H