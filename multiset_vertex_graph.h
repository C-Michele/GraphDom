#ifndef MULTISET_VERTEX_GRAPH_H
#define MULTISET_VERTEX_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class multiset_vertex_graph : virtual public graph<VertexType>  {
        public:
            class VERTEX_PTR_NAME;
            class ADJ_LIST;
            class EDGE_ITERATOR_NAME;

            ~multiset_vertex_graph() override = default;

            [[nodiscard]] virtual multiset_vertex_graph::VERTEX_PTR_NAME insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual multiset_vertex_graph::VERTEX_PTR_NAME insert_vertex(VertexType&&) = 0;
            // [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, const VertexType&) = 0; //TODO: check the signature correctness
            // [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, VertexType&&) = 0; //TODO: check the signature correctness
    };
}

#include "multiset_vertex_graph_vertex_ptr.h"

#endif //MULTISET_VERTEX_GRAPH_H