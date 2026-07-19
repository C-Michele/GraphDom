/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_LABELED_EDGE_MIXED_GRAPH_H
#define GRAPHDOM_LABELED_EDGE_MIXED_GRAPH_H

#include "labeled_edge_graph.h"
#include "mixed_graph.h"

namespace graphdom {
    /// Every labeled-edge mixed graph created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <
        typename VertexType,
        typename EdgeLabelType,
        typename EdgeLabellerType = default_edge_labeller<VertexType,EdgeLabelType>
    >
    class labeled_edge_mixed_graph : virtual public labeled_edge_graph<VertexType,EdgeLabelType>, virtual public mixed_graph<VertexType> {
        public:
            labeled_edge_mixed_graph();
            explicit labeled_edge_mixed_graph(const EdgeLabellerType& el);
            explicit labeled_edge_mixed_graph(EdgeLabellerType&& el);

            /// To be polymorphic, this class has a virtual destructor.
            ~labeled_edge_mixed_graph() override = default;

            [[nodiscard]] constexpr const EdgeLabellerType& get_edges_labeller() const;

            using mixed_graph<VertexType>::insert_edge;

            /**
             * If @p et is equal to `undirected` then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint and @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If @p et is equal to `directed` then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to `( this->get_edges_labeller() )()`
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param et The type of edge to insert
             */
            void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, edge_type et) final;

            /**
             * If @p et is equal to `undirected` then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint and @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If @p et is equal to `directed` then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param et The type of edge to insert
             * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             */
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, edge_type et, const EdgeLabelType& edge_label) = 0;

            /**
             * If @p et is equal to `undirected` then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint and @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If @p et is equal to `directed` then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param et The type of edge to insert
             * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             */
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, edge_type et, EdgeLabelType&& edge_label) = 0;
        private:
            EdgeLabellerType edges_labeller;
    };
}

#include "impl/labeled_edge_mixed_graph.h"

#endif //GRAPHDOM_LABELED_EDGE_MIXED_GRAPH_H