/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_LABELED_EDGE_GRAPH_H
#define GRAPHDOM_LABELED_EDGE_GRAPH_H

#include "graph.h"

namespace graphdom {
    /// Every [labeled-edge graph](@ref mathematical_labeled_edge_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     *
     * Every labeled-edge graph created with this library can be considered equivalent to a labeled-edge graph consistent with the [definition found on the "Mathematical Introduction" page](@ref mathematical_labeled_edge_graph_definition):<br>
     * referring to the symbols used in [that definition](@ref mathematical_labeled_edge_graph_definition), \f$ C_{l_E} \f$ is the set of all possible instances of @p EdgeLabelType .
     */
    template <typename VertexType, typename EdgeLabelType>
    class labeled_edge_graph : virtual public graph<VertexType> {
        public:
            /// To be polymorphic, this class has a virtual destructor.
            ~labeled_edge_graph() override = default;

            [[nodiscard]] virtual const EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) const = 0;

            [[nodiscard]] virtual EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) = 0;
    };
}

namespace graphdom {
    template <typename VertexType, typename EdgeLabelType>
    class default_edge_labeller final {
        public:
            [[nodiscard]] constexpr EdgeLabelType operator()(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&) const {
                return EdgeLabelType();
            }
            [[nodiscard]] constexpr EdgeLabelType operator()(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, edge_type) const {
                return EdgeLabelType();
            }
    };
}

#endif //GRAPHDOM_LABELED_EDGE_GRAPH_H