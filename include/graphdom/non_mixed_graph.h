#ifndef NON_MIXED_GRAPH_H
#define NON_MIXED_GRAPH_H

#include "graph.h"

namespace graphdom {
    /// Every [non-mixed graph](@ref mathematical_non_mixed_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <typename VertexType>
    class non_mixed_graph : virtual public graph<VertexType> {
        public:
            /// To be polymorphic, this class has a virtual destructor.
            ~non_mixed_graph() override = default;

            /**
             * If `*this` is an [ugraph](@ref mathematical_ugraph_definition) then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint and @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If `*this` is a [digraph](@ref mathematical_digraph_definition) then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             */
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint) = 0;
    };
}

#endif //NON_MIXED_GRAPH_H