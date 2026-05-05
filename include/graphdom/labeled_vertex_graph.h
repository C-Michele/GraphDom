#ifndef LABELED_VERTEX_GRAPH_H
#define LABELED_VERTEX_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType>
    class labeled_vertex_graph : virtual public graph<VertexType> {
        public:
            ~labeled_vertex_graph() override = default;

            [[nodiscard]] virtual const VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) const = 0;

            [[nodiscard]] virtual VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) = 0;
    };
}

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType>
    class default_vertex_labeller final {
    public:
        [[nodiscard]] constexpr VertexLabelType operator()(const VertexType&) const {
            return VertexLabelType();
        }
    };
}

#endif //LABELED_VERTEX_GRAPH_H