#ifndef LABELED_EDGE_GRAPH_H
#define LABELED_EDGE_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename EdgeLabelType>
    class labeled_edge_graph : virtual public graph<VertexType> {
        public:
            ~labeled_edge_graph() override = default;

            [[nodiscard]] virtual const EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const = 0;

            [[nodiscard]] virtual EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) = 0;
    };
}

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename EdgeLabelType>
    class default_edge_labeller final {
        public:
            [[nodiscard]] constexpr EdgeLabelType operator()(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&) const {
                return EdgeLabelType();
            }
            [[nodiscard]] constexpr EdgeLabelType operator()(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, edge_type) const {
                return EdgeLabelType();
            }
    };
}

#endif //LABELED_EDGE_GRAPH_H