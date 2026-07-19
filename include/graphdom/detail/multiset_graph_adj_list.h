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
    /**
     * @brief Every valid instance of this class is a "container-like and non-owning" handle to a subset of the set of all [out-edges](@ref mathematical_vertex_out_edge_definition) of a [vertex](@ref mathematical_vertex_definition) belongings to a [multiset graph](@ref graphdom::multiset_graph).
     *
     * An instance `adj` of this class is invalidated as soon as one of the following scenarios occurs:
     * -# `adj` is constructed using an invalid instance of this class.
     * -# `adj` is constructed using an invalid instance of [graphdom::graph< VertexType >::adj_list](@ref graphdom::graph::adj_list).
     *
     * A valid instance `adj` of this class is invalidated as soon as the vertex it is associated with is erased.
     *
     * If `*this` is invalid then any operation other than the destruction of `*this` will cause undefined behavior.
     *
     * \warning
     * Users of the library MUST ABSOLUTELY NOT write code whose flow depends on the order of the elements in this container, even if the order relationship in which the elements are arranged is (obviously) deterministic.
     */
    template <typename VertexType>
    class multiset_graph<VertexType>::adj_list : public graph<VertexType>::template base_adj_list< typename graph<VertexType>::vertex_container* > {
        public:
            adj_list() = delete;
            adj_list(const adj_list& other);
            explicit adj_list(const typename graph<VertexType>::adj_list& other);

            ~adj_list() = default;

            adj_list& operator=(const adj_list&) = delete;
            adj_list& operator=(adj_list&&) = delete;

            [[nodiscard]] multiset_graph<VertexType>::adj_list_iterator begin() const;
            [[nodiscard]] multiset_graph<VertexType>::adj_list_iterator end() const;
            [[nodiscard]] typename graph<VertexType>::adj_list_const_iterator cbegin() const;
            [[nodiscard]] typename graph<VertexType>::adj_list_const_iterator cend() const;

            /// \cond DEV_DOC
            friend class graph<VertexType>::const_adj_list;
            friend class graph<VertexType>::adj_list;
            friend class multiset_graph<VertexType>::vertex_handle;
            /// \endcond DEV_DOC
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