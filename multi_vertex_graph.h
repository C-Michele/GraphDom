#ifndef MULTI_VERTEX_GRAPH_H
#define MULTI_VERTEX_GRAPH_H

#include "graph_base.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class multi_vertex_graph : virtual public graph_base<VertexType> {
        public:
            ~multi_vertex_graph() override = default;

            [[nodiscard]] virtual typename graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual typename graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&) = 0;
    };
}

#endif //MULTI_VERTEX_GRAPH_H
