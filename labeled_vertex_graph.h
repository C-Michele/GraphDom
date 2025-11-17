#ifndef LABELED_VERTEX_GRAPH_H
#define LABELED_VERTEX_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType>
    class labeled_vertex_graph : virtual public graph<VertexType> {
        public:
            ~labeled_vertex_graph() override = default;

            [[nodiscard]] virtual const VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const = 0;

            [[nodiscard]] virtual VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) = 0; //TODO: check the signature correctness
    };
}


#endif //LABELED_VERTEX_GRAPH_H