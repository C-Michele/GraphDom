/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_MIXED_GRAPH_H
#define GRAPHDOM_MIXED_GRAPH_H

#include "graph.h"

namespace graphdom {
    /// Every [mixed graph](@ref mathematical_mixed_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <typename VertexType>
    class mixed_graph : virtual public graph<VertexType> {
        public:
            /// To be polymorphic, this class has a virtual destructor.
            ~mixed_graph() override = default;

            /**
             * If @p et is equal to `undirected` then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint and @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If @p et is equal to `directed` then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param et The type of edge to insert
             */
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, edge_type et) = 0;
    };
}

#endif //GRAPHDOM_MIXED_GRAPH_H