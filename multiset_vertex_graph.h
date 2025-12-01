#ifndef MULTISET_VERTEX_GRAPH_H
#define MULTISET_VERTEX_GRAPH_H

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class multiset_vertex_graph : virtual public graph<VertexType>  {
        public:
            class VERTEX_PTR_NAME;
            class ADJ_LIST;
            class EDGE_ITERATOR_NAME;

            ~multiset_vertex_graph() override = default;

            [[nodiscard]] virtual multiset_vertex_graph::VERTEX_PTR_NAME insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual multiset_vertex_graph::VERTEX_PTR_NAME insert_vertex(VertexType&&) = 0;
            // [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, const VertexType&) = 0; //TODO: check the signature correctness
            // [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, VertexType&&) = 0; //TODO: check the signature correctness
        protected:
            using VertexContainerPointerType = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*;
            using edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template edge_endpoint< VertexContainerPointerType >;
            template <typename EdgeLabelType>
            using labeled_directed_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using labeled_undirected_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            using custom_edge_endpoint_less = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template custom_edge_endpoint_less<VertexContainerPointerType>;
            using adj_set = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template adj_set<VertexContainerPointerType>;
            using non_mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>;
            using mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>;
            template <typename EdgeLabelType>
            using non_mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;

            static VERTEX_PTR_NAME vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static VERTEX_PTR_NAME vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
            );

            static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME const_vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME const_vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
            );
    };

}

#include "multiset_vertex_graph_vertex_ptr.h"

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::const_vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::const_vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME(graph_ptr,vertex_container_reference);
}

#endif //MULTISET_VERTEX_GRAPH_H