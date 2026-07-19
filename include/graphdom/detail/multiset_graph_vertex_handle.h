/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_MULTISET_GRAPH_VERTEX_HANDLE_H
#define GRAPHDOM_MULTISET_GRAPH_VERTEX_HANDLE_H

#include "../graph.h"
#include "vertex_container.h"
#include "vertex_handle.h"
#include "../multiset_graph.h"

namespace graphdom {
    /**
     * @brief Every valid instance of this class can be used to identify a specific [vertex](@ref mathematical_vertex_definition) of a [multiset graph](@ref graphdom::multiset_graph) and to access its [core](@ref mathematical_vertex_core_definition) by reference or pointer.
     *
     * An instance `hndl` of this class is invalidated as soon as one of the following scenarios occurs:
     * -# `hndl` is constructed using an invalid instance of this class.
     * -# `hndl` is constructed using an invalid instance of [graphdom::graph< VertexType >::vertex_handle](@ref graphdom::graph::vertex_handle).
     * -# `hndl = other_hndl;` is executed where `other_hndl` is an invalid instance of this class.
     *
     * A valid instance `hndl` of this class is invalidated as soon as the vertex it is associated with is erased.
     *
     * An invalid instance `hndl` of this class is validated as soon as `hndl = other_hndl;` is executed where `other_hndl` is a valid instance of this class.
     *
     * If `*this` is invalid then any operation other than `*this = other;` and the destruction of `*this` will cause undefined behavior.
     */
    template <typename VertexType>
    class multiset_graph<VertexType>::vertex_handle final : public graph<VertexType>::template vertex_base_handle< typename graph<VertexType>::vertex_container* > {
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
             * If @p other is valid and identifies a vertex of a multiset-vertex graph, then immediately after the construction of `*this` we will have `*this == other`.<br>
             * If @p other is valid but identifies a vertex of a set-vertex graph, then this constructor will throw an instance of a class publicly derived, directly or indirectly, from `std::exception`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The object to compare with `*this`.
             * @par Complexity
             * Constant.
             */
            explicit vertex_handle(const typename graph<VertexType>::vertex_handle& other);

            ~vertex_handle() = default;

            vertex_handle& operator=(const vertex_handle& other);

            [[nodiscard]] multiset_graph<VertexType>::adj_list adj_list() const;
            [[nodiscard]] multiset_graph<VertexType>::adj_list adj_list(edge_type edge_type) const;
            [[nodiscard]] typename graph<VertexType>::const_adj_list const_adj_list() const;
            [[nodiscard]] typename graph<VertexType>::const_adj_list const_adj_list(edge_type edge_type) const;

            friend typename graph<VertexType>::vertex_const_handle;
            friend typename graph<VertexType>::vertex_handle;
            friend typename multiset_graph<VertexType>::adj_list_iterator;
            friend typename graphdom::multiset_graph<VertexType>;
        private:
            vertex_handle(
                const graph<VertexType>* vertex_container_owner_ptr,
                typename graph<VertexType>::graph_edges_type vertex_container_owner_et,
                typename graph<VertexType>::vertex_container* vertex_container_ptr
            );
    };
}

#include "impl/multiset_graph_vertex_handle.h"

#endif //GRAPHDOM_MULTISET_GRAPH_VERTEX_HANDLE_H