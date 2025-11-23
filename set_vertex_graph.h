#ifndef SET_VERTEX_GRAPH_H
#define SET_VERTEX_GRAPH_H

#include <utility>

#include "graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class set_vertex_graph : virtual public graph<VertexType>  {
        public:
            ~set_vertex_graph() override = default;

            [[nodiscard]] virtual std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(VertexType&&) = 0;
        protected:
            using VertexContainerPointerType = const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*;
            using edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template edge_endpoint< VertexContainerPointerType >;
            template <typename EdgeLabelType>
            using labeled_directed_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using labeled_undirected_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            using non_mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>;
            using mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>;
            template <typename EdgeLabelType>
            using non_mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
    };
}

#endif //SET_VERTEX_GRAPH_H