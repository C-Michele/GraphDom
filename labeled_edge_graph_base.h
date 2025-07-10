#ifndef LABELED_EDGE_GRAPH_BASE_H
#define LABELED_EDGE_GRAPH_BASE_H

#include "graph_base.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename EdgeLabelType>
    class labeled_edge_graph_base : virtual public graph_base<VertexType> {
        public:
            ~labeled_edge_graph_base() override = default;

            [[nodiscard]] virtual const EdgeLabelType& get_edge_label(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const = 0;

            [[nodiscard]] virtual EdgeLabelType& get_edge_label(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::EDGE_ITERATOR_NAME&) = 0; //TODO: check the signature correctness
            virtual void insert_edge(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const EdgeLabelType&,  typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::edge_type) = 0;
            virtual void insert_edge(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, EdgeLabelType&&,  typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::edge_type) = 0;
    };
}

#endif //LABELED_EDGE_GRAPH_BASE_H