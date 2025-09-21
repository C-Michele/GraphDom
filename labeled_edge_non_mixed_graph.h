#ifndef LABELED_EDGE_NON_MIXED_GRAPH_H
#define LABELED_EDGE_NON_MIXED_GRAPH_H

#include "labeled_edge_graph.h"
#include "non_mixed_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename EdgeLabelType, typename T> //TODO: find a better name for "T"
    class labeled_edge_non_mixed_graph : virtual public labeled_edge_graph<VertexType, EdgeLabelType>, virtual public non_mixed_graph<VertexType> {
        public:
            ~labeled_edge_non_mixed_graph() override = default;

            using non_mixed_graph<VertexType>::insert_edge;
            void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& first, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& second) final;
            virtual void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const EdgeLabelType&) = 0;
            virtual void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, EdgeLabelType&&) = 0;
    };

    template<typename VertexType, typename EdgeLabelType, typename T> //TODO: find a better name for "T"
    void labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T>::insert_edge(
        const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& first,
        const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& second) {
        insert_edge(first,second,T()(first,second));
    }
}

#endif //LABELED_EDGE_NON_MIXED_GRAPH_H