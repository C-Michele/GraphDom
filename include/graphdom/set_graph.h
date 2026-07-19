/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_SET_GRAPH_H
#define GRAPHDOM_SET_GRAPH_H

#include "graph.h"

namespace graphdom {
    /// Every [set graph](@ref mathematical_set_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <typename VertexType>
    class set_graph : virtual public graph<VertexType>  {
        public:
            /// To be polymorphic, this class has a virtual destructor.
            ~set_graph() override = default;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.
             *
             * @param v_core
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType& v_core) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.
             *
             * @param v_core
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&& v_core) = 0;

        /// \cond DEV_DOC
        protected:
            using VertexContainerPointerType = const typename graphdom::graph<VertexType>::vertex_container*;
            using edge_endpoint = typename graphdom::graph<VertexType>::template edge_endpoint< VertexContainerPointerType >;
            template <typename EdgeLabelType>
            using labeled_directed_edge_endpoint = typename graphdom::graph<VertexType>::template labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using labeled_undirected_edge_endpoint = typename graphdom::graph<VertexType>::template labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            using custom_edge_endpoint_less = typename graphdom::graph<VertexType>::template custom_edge_endpoint_less<VertexContainerPointerType>;
            using adj_set = typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>;
            using non_mixed_graph_vertex_container = typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>;
            using mixed_graph_vertex_container = typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>;
            template <typename EdgeLabelType>
            using non_mixed_graph_labeled_vertex_container = typename graphdom::graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using mixed_graph_labeled_vertex_container = typename graphdom::graph<VertexType>::template mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;

            static typename adj_set::const_iterator get_inner_iterator(const typename graphdom::graph<VertexType>::adj_list_const_iterator&);

            static typename graphdom::graph<VertexType>::adj_list_iterator adj_list_iterator_factory(
                const graphdom::set_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
                const non_mixed_graph_vertex_container* edge_begin_point_ptr,
                graphdom::edge_type edge_set_vertex_graph_owner_edges_type,
                typename adj_set::iterator inner_itr
            );

            static typename graphdom::graph<VertexType>::adj_list_iterator adj_list_iterator_factory(
                const graphdom::set_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
                const mixed_graph_vertex_container* edge_begin_point_ptr,
                typename adj_set::iterator inner_itr,
                graphdom::edge_type inner_itr_edge_type,
                bool inner_itr_is_limited_by_edge_type = false
            );
        /// \endcond DEV_DOC
    };
}

#include "impl/set_graph.h"

#endif //GRAPHDOM_SET_GRAPH_H