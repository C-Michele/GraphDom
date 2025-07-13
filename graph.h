#ifndef GRAPH_H
#define GRAPH_H

#include <utility>

#include "graph_base.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class graph : virtual public graph_base<VertexType> {
        public:
            ~graph() override = default;

            [[nodiscard]] virtual std::pair<typename graph_base<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual std::pair<typename graph_base<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(VertexType&&) = 0;
    };
}

#endif //GRAPH_H
