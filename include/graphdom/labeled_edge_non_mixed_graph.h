#ifndef LABELED_EDGE_NON_MIXED_GRAPH_H
#define LABELED_EDGE_NON_MIXED_GRAPH_H

#include "labeled_edge_graph.h"
#include "non_mixed_graph.h"

namespace graphdom {
    template <typename VertexType, typename EdgeLabelType, typename EdgeLabellerType = default_edge_labeller<VertexType,EdgeLabelType>>
    class labeled_edge_non_mixed_graph : virtual public labeled_edge_graph<VertexType,EdgeLabelType>, virtual public non_mixed_graph<VertexType> {
        public:
            labeled_edge_non_mixed_graph();
            explicit labeled_edge_non_mixed_graph(const EdgeLabellerType& el);
            explicit labeled_edge_non_mixed_graph(EdgeLabellerType&& el);

            ~labeled_edge_non_mixed_graph() override = default;

            [[nodiscard]] constexpr const EdgeLabellerType& get_edges_labeller() const;

            using non_mixed_graph<VertexType>::insert_edge;
            void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint) final;
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, const EdgeLabelType&) = 0;
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, EdgeLabelType&&) = 0;
        private:
            const EdgeLabellerType edges_labeller;
    };

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph() : edges_labeller() {}

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph(const EdgeLabellerType& el) : edges_labeller(el) {}

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph(EdgeLabellerType&& el) : edges_labeller(std::move(el)) {}

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    constexpr const EdgeLabellerType& labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::get_edges_labeller() const {
        return edges_labeller;
    }

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    void labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::insert_edge(
        const typename graph<VertexType>::vertex_const_handle& first_endpoint,
        const typename graph<VertexType>::vertex_const_handle& second_endpoint) {
        insert_edge(first_endpoint,second_endpoint,edges_labeller(first_endpoint,second_endpoint));
    }
}

#endif //LABELED_EDGE_NON_MIXED_GRAPH_H