#ifndef SET_VERTEX_GRAPH_H
#define SET_VERTEX_GRAPH_H

#include <utility>

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class set_vertex_graph : virtual public graph<VertexType>  {
        public:
            ~set_vertex_graph() override = default;

            [[nodiscard]] virtual std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(VertexType&&) = 0;
    };
}

#endif //SET_VERTEX_GRAPH_H