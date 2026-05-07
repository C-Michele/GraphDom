#ifndef LABELED_EDGE_NON_MIXED_GRAPH_H
#define LABELED_EDGE_NON_MIXED_GRAPH_H

#include "labeled_edge_graph.h"
#include "non_mixed_graph.h"

namespace graphdom {
    /// Every labeled-edge non-mixed graph created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <
        typename VertexType,
        typename EdgeLabelType,
        typename EdgeLabellerType = default_edge_labeller<VertexType,EdgeLabelType>
    >
    class labeled_edge_non_mixed_graph : virtual public labeled_edge_graph<VertexType,EdgeLabelType>, virtual public non_mixed_graph<VertexType> {
        public:
            labeled_edge_non_mixed_graph();
            explicit labeled_edge_non_mixed_graph(const EdgeLabellerType& edge_labeller);
            explicit labeled_edge_non_mixed_graph(EdgeLabellerType&& edge_labeller);
        
            /// To be polymorphic, this class has a virtual destructor.
            ~labeled_edge_non_mixed_graph() override = default;

            [[nodiscard]] constexpr const EdgeLabellerType& get_edges_labeller() const;

            using non_mixed_graph<VertexType>::insert_edge;

            /**
             * If `*this` is an [ugraph](@ref mathematical_ugraph_definition) then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint, @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If `*this` is a [digraph](@ref mathematical_digraph_definition) then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to `( this->get_edges_labeller() )()`
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             */
            void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint) final;

            /**
             * If `*this` is an [ugraph](@ref mathematical_ugraph_definition) then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint, @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If `*this` is a [digraph](@ref mathematical_digraph_definition) then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             */
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, const EdgeLabelType& edge_label) = 0;

            /**
             * If `*this` is an [ugraph](@ref mathematical_ugraph_definition) then inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint, @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If `*this` is a [digraph](@ref mathematical_digraph_definition) then inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p first_endpoint as [tail](@ref mathematical_directed_edge_tail_definition) and @p second_endpoint as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             */
            virtual void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, EdgeLabelType&& edge_label) = 0;
        private:
            const EdgeLabellerType edges_labeller;
    };

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph() : edges_labeller() {}

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph(const EdgeLabellerType& edge_labeller) : edges_labeller(edge_labeller) {}

    template<typename VertexType, typename EdgeLabelType, typename EdgeLabellerType>
    labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::labeled_edge_non_mixed_graph(EdgeLabellerType&& edge_labeller) : edges_labeller(std::move(edge_labeller)) {}

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