#ifndef LABELED_VERTEX_GRAPH_H
#define LABELED_VERTEX_GRAPH_H

#include "graph.h"

namespace graphdom {
    /// Every [labeled-vertex graph](@ref mathematical_labeled_vertex_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     *
     * Every labeled-vertex graph created with this library can be considered equivalent to a labeled-vertex graph consistent with the [definition found on the "Mathematical Introduction" page](@ref mathematical_labeled_vertex_graph_definition):<br>
     * referring to the symbols used in [that definition](@ref mathematical_labeled_vertex_graph_definition), \f$ C_{l_V} \f$ is the set of all possible instances of @p VertexLabelType .
     */
    template <typename VertexType, typename VertexLabelType>
    class labeled_vertex_graph : virtual public graph<VertexType> {
        public:
            /// To be polymorphic, this class has a virtual destructor.
            ~labeled_vertex_graph() override = default;

            /**
             * If @p vertex is valid then returns a const reference to the [label of the vertex](@ref mathematical_vertex_label_definition) identified by @p vertex (with respect to `*this`).
             *
             * @param vertex This handle must be valid and must identify a vertex belonging to `*this`, otherwise this method will cause undefined behavior.
             * @return A const reference to [label of the vertex](@ref mathematical_vertex_label_definition) identified by @p vertex (with respect to `*this`).
             * @par Complexity
             * Constant.
             */
            [[nodiscard]] virtual const VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle& vertex) const = 0;

            /**
             * If @p vertex is valid then returns a reference to the [label of the vertex](@ref mathematical_vertex_label_definition) identified by @p vertex (with respect to `*this`).
             *
             * @param vertex This handle must be valid and must identify a vertex belonging to `*this`, otherwise this method will cause undefined behavior.
             * @return A reference to [label of the vertex](@ref mathematical_vertex_label_definition) identified by @p vertex (with respect to `*this`).
             * @par Complexity
             * Constant.
             */
            [[nodiscard]] virtual VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle& vertex) = 0;
    };
}

namespace graphdom {
    template <typename VertexType, typename VertexLabelType>
    class default_vertex_labeller final {
        public:
            [[nodiscard]] constexpr VertexLabelType operator()(const VertexType&) const {
                return VertexLabelType();
            }
    };
}

#endif //LABELED_VERTEX_GRAPH_H