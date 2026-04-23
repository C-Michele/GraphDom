#ifndef LABELED_EDGE_GRAPH_H
#define LABELED_EDGE_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename EdgeLabelType>
    class DefaultEdgeLabellerType {
        public:
            EdgeLabelType operator()(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&) const {
                return EdgeLabelType();
            }
            EdgeLabelType operator()(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, edge_type) const {
                return EdgeLabelType();
            }
    };

    template <typename VertexType, typename EdgeLabelType>
    class labeled_edge_graph : virtual public graph<VertexType> {
        public:
            ~labeled_edge_graph() override = default;

            [[nodiscard]] virtual const EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const = 0;

            [[nodiscard]] virtual EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) = 0; //TODO: check the signature correctness
    };
}

#endif //LABELED_EDGE_GRAPH_H