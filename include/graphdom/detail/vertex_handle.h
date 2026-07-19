/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_HANDLE_H
#define GRAPHDOM_VERTEX_HANDLE_H

#include "../graph.h"
#include "vertex_container.h"
#include "vertex_base_handle.h"
#include "../multiset_graph.h"
#include "multiset_graph_vertex_handle.h"

namespace graphdom {
    /**
     * @brief Every valid instance of this class can be used to identify a specific [vertex](@ref mathematical_vertex_definition) of a [graph](@ref graphdom::graph) and to access its [core](@ref mathematical_vertex_core_definition) by reference or pointer.
     *
     * An instance `hndl` of this class is invalidated as soon as one of the following scenarios occurs:
     * -# `hndl` is constructed using an invalid instance of this class.
     * -# `hndl` is constructed using an invalid instance of [graphdom::multiset_graph< VertexType >::vertex_handle](@ref graphdom::multiset_graph::vertex_handle).
     * -# `hndl = other_hndl;` is executed where `other_hndl` is an invalid instance of this class.
     *
     * A valid instance `hndl` of this class is invalidated as soon as the vertex it is associated with is erased.
     *
     * An invalid instance `hndl` of this class is validated as soon as `hndl = other_hndl;` is executed where `other_hndl` is a valid instance of this class.
     *
     * If `*this` is invalid then any operation other than `*this = other;` and the destruction of `*this` will cause undefined behavior.
     */
    template <typename VertexType>
    class graph<VertexType>::vertex_handle final : public graph<VertexType>::vertex_base_handle< const graph<VertexType>::vertex_container* > {
        public:
            vertex_handle() = delete;
            /**
             * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            vertex_handle(const vertex_handle& other);
            /**
             * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            vertex_handle(const typename multiset_graph<VertexType>::vertex_handle& other);

            ~vertex_handle() = default;

            /**
             * If `*this` is invalid, invoking this conversion operator via `*this` will cause undefined behavior.<br>
             * If `*this` is valid and identifies a vertex belonging to a set-vertex graph, invoking this conversion operator via `*this` will throw an instance of a class publicly derived, directly or indirectly, from `std::exception`.
             *
             * @par Complexity
             * Constant.
             */
            explicit operator typename multiset_graph<VertexType>::vertex_handle() const;

            vertex_handle& operator=(const vertex_handle& other);

            [[nodiscard]] graph<VertexType>::adj_list adj_list() const;
            [[nodiscard]] graph<VertexType>::adj_list adj_list(edge_type edge_type) const;
            [[nodiscard]] graph<VertexType>::const_adj_list const_adj_list() const;
            [[nodiscard]] graph<VertexType>::const_adj_list const_adj_list(edge_type edge_type) const;

            /// \cond DEV_DOC
            friend typename graph<VertexType>::vertex_const_handle;
            friend typename multiset_graph<VertexType>::vertex_handle;
            friend typename graph<VertexType>::adj_list_iterator;
            friend graph<VertexType>;
            /// \endcond DEV_DOC
        private:
            vertex_handle(
                const graph<VertexType>* vertex_container_owner_ptr,
                graph<VertexType>::graph_edges_type vertex_container_owner_et,
                const graph<VertexType>::vertex_container* vertex_container_ptr
            );
    };
}

#include "impl/vertex_handle.h"

#endif //GRAPHDOM_VERTEX_HANDLE_H