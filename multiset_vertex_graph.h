#ifndef MULTISET_VERTEX_GRAPH_H
#define MULTISET_VERTEX_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class multiset_vertex_graph : virtual public graph<VertexType>  {
        public:
            ~multiset_vertex_graph() override = default;

            [[nodiscard]] virtual graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&) = 0;
    };
}

#endif //MULTISET_VERTEX_GRAPH_H