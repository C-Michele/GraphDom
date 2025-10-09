#ifndef MULTISET_VERTEX_GRAPH_H
#define MULTISET_VERTEX_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class multiset_vertex_graph : virtual public graph<VertexType>  {
        public:
            ~multiset_vertex_graph() override = default;

            [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&) = 0;
            [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, const VertexType&) = 0; //TODO: check the signature correctness
            [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, VertexType&&) = 0; //TODO: check the signature correctness
    };
}

#endif //MULTISET_VERTEX_GRAPH_H