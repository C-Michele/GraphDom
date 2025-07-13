#ifndef LABELED_EDGE_GRAPH_BASE_H
#define LABELED_EDGE_GRAPH_BASE_H

#include "graph_base.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename EdgeLabelType, typename T> //TODO: find a better name for "T"
    class labeled_edge_graph_base : virtual public graph_base<VertexType> {
        public:
            ~labeled_edge_graph_base() override = default;

            [[nodiscard]] virtual const EdgeLabelType& get_edge_label(const typename graph_base<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const = 0;

            [[nodiscard]] virtual EdgeLabelType& get_edge_label(const typename graph_base<VertexType>::EDGE_ITERATOR_NAME&) = 0; //TODO: check the signature correctness
            using graph_base<VertexType>::insert_edge;
            void insert_edge(const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME& first, const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME& second, typename graph_base<VertexType>::edge_type et) final;
            virtual void insert_edge(const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const EdgeLabelType&,  typename graph_base<VertexType>::edge_type) = 0;
            virtual void insert_edge(const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&, EdgeLabelType&&,  typename graph_base<VertexType>::edge_type) = 0;
    };

    template<typename VertexType, typename EdgeLabelType, typename T> //TODO: find a better name for "T"
    void labeled_edge_graph_base<VertexType,EdgeLabelType,T>::insert_edge(
        const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME& first,
        const typename graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME& second,
        const typename graph_base<VertexType>::edge_type et) {
        insert_edge(first,second,T()(first,second,et),et);
    }
}

#endif //LABELED_EDGE_GRAPH_BASE_H