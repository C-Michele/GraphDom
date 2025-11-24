#ifndef LABELED_EDGE_MIXED_GRAPH_H
#define LABELED_EDGE_MIXED_GRAPH_H

#include "labeled_edge_graph.h"
#include "mixed_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename EdgeLabelType, typename T> //TODO: find a better name for "T"
    class labeled_edge_mixed_graph : virtual public labeled_edge_graph<VertexType,EdgeLabelType>, virtual public mixed_graph<VertexType> {
        public:
            labeled_edge_mixed_graph() = default;
            explicit labeled_edge_mixed_graph(const T& el);
            explicit labeled_edge_mixed_graph(T&& el);

            ~labeled_edge_mixed_graph() override = default;

            using mixed_graph<VertexType>::insert_edge;
            void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& first, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& second, edge_type) final;
            virtual void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, edge_type, const EdgeLabelType&) = 0;
            virtual void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, edge_type, EdgeLabelType&&) = 0;
        protected:
            T edges_labeller;
    };

    template<typename VertexType, typename EdgeLabelType, typename T>
    labeled_edge_mixed_graph<VertexType,EdgeLabelType,T>::labeled_edge_mixed_graph(const T& el) : edges_labeller(el) {}

    template<typename VertexType, typename EdgeLabelType, typename T>
    labeled_edge_mixed_graph<VertexType,EdgeLabelType,T>::labeled_edge_mixed_graph(T&& el) : edges_labeller(std::move(el)) {}

    template<typename VertexType, typename EdgeLabelType, typename T> //TODO: find a better name for "T"
    void labeled_edge_mixed_graph<VertexType,EdgeLabelType,T>::insert_edge(
        const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& first,
        const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& second,
        edge_type et) {
        insert_edge(first,second,et,edges_labeller(first,second,et));
    }
}

#endif //LABELED_EDGE_MIXED_GRAPH_H