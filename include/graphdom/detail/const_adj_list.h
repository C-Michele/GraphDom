/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_CONST_ADJ_LIST_H
#define GRAPHDOM_CONST_ADJ_LIST_H

#include "../graph.h"
#include "vertex_container.h"
#include "base_adj_list.h"
#include "adj_list.h"
#include "../multiset_graph.h"
#include "multiset_graph_adj_list.h"

namespace graphdom {
    /**
     * @brief Every valid instance of this class is a "container-like and non-owning" handle to a subset of the set of all [out-edges](@ref mathematical_vertex_out_edge_definition) of a [vertex](@ref mathematical_vertex_definition).<br>
     * A valid instance `adj` of this class cannot create objects that allow modification of the graph to which the vertex associated with `adj` belongs without a non-constant reference to that graph.
     *
     * An instance `adj` of this class is invalidated as soon as one of the following scenarios occurs:
     * -# `adj` is constructed using an invalid instance of this class.
     * -# `adj` is constructed using an invalid instance of [graphdom::graph< VertexType >::adj_list](@ref graphdom::graph::adj_list).
     * -# `adj` is constructed using an invalid instance of [graphdom::multiset_graph< VertexType >::adj_list](@ref graphdom::multiset_graph::adj_list).
     *
     * A valid instance `adj` of this class is invalidated as soon as the vertex it is associated with is erased.
     *
     * If `*this` is invalid then any operation other than the destruction of `*this` will cause undefined behavior.
     *
     * \warning
     * Users of the library MUST ABSOLUTELY NOT write code whose flow depends on the order of the elements in this container, even if the order relationship in which the elements are arranged is (obviously) deterministic.
     */
    template <typename VertexType>
    class graph<VertexType>::const_adj_list : public graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* > {
        public:
            const_adj_list() = delete;
            const_adj_list(const const_adj_list& other);
            const_adj_list(const graph<VertexType>::adj_list& other);
            const_adj_list(const typename multiset_graph<VertexType>::adj_list& other);

            ~const_adj_list() = default;

            const_adj_list& operator=(const const_adj_list&) = delete;
            const_adj_list& operator=(const_adj_list&&) = delete;

            [[nodiscard]] graph<VertexType>::adj_list_const_iterator begin() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator end() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator cbegin() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator cend() const;

            /// \cond DEV_DOC
            friend class graph<VertexType>::vertex_handle;
            friend class graph<VertexType>::vertex_const_handle;
            friend class multiset_graph<VertexType>::vertex_handle;
            /// \endcond DEV_DOC
        private:
            const_adj_list(
                const graphdom::graph<VertexType>* adj_list_owner_graph_pointer,
                graphdom::graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
                const graphdom::graph<VertexType>::vertex_container* adj_list_common_begin_point_vertex_container_pointer,
                typename graphdom::graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection = none
            );
    };
}

#include "impl/const_adj_list.h"

#endif //GRAPHDOM_CONST_ADJ_LIST_H