#ifndef MIXED_GRAPH_H
#define MIXED_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    /// Every [mixed graph](@ref mathematical_mixed_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <typename VertexType>
    class mixed_graph : virtual public graph<VertexType> {
        public:
            /// To be polymorphic, this class has a virtual destructor.
            ~mixed_graph() override = default;

            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, edge_type) = 0;
    };
}

#endif //MIXED_GRAPH_H