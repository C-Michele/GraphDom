#ifndef MIXED_GRAPH_H
#define MIXED_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class mixed_graph : virtual public graph<VertexType> {
        public:
            ~mixed_graph() override = default;

            virtual void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, typename graph<VertexType>::edge_type) = 0;
    };
}

#endif //MIXED_GRAPH_H