#ifndef LABELED_VERTEX_MULTI_VERTEX_GRAPH_H
#define LABELED_VERTEX_MULTI_VERTEX_GRAPH_H

#include <utility>

#include "multi_vertex_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType>
    class labeled_vertex_multi_vertex_graph : virtual public multi_vertex_graph<VertexType> {
        public:
            ~labeled_vertex_multi_vertex_graph() override = default;

            [[nodiscard]] virtual const VertexLabelType& get_vertex_label(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const = 0;

            [[nodiscard]] virtual VertexLabelType& get_vertex_label(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME&) = 0; //TODO: check the signature correctness
            [[nodiscard]] virtual typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(const std::pair<VertexType,VertexLabelType>&) = 0;
            [[nodiscard]] virtual typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(std::pair<VertexType,VertexLabelType>&&) = 0;
    };
}

#endif //LABELED_VERTEX_MULTI_VERTEX_GRAPH_H