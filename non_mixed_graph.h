#ifndef NON_MIXED_GRAPH_H
#define NON_MIXED_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class non_mixed_graph : virtual public graph<VertexType> {
        public:
            ~non_mixed_graph() override = default;

            virtual void insert_edge(const graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) = 0;
    };
}

#endif //NON_MIXED_GRAPH_H