#ifndef LABELED_VERTEX_MULTISET_VERTEX_GRAPH_H
#define LABELED_VERTEX_MULTISET_VERTEX_GRAPH_H

#include <utility>

#include "labeled_vertex_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType, typename T = DefaultVertexLabellerType<VertexType,VertexLabelType>>  //TODO: find a better name for "T"
    class labeled_vertex_multiset_vertex_graph : virtual public labeled_vertex_graph<VertexType,VertexLabelType>, virtual public multiset_vertex_graph<VertexType> {
        public:
            labeled_vertex_multiset_vertex_graph() = default;
            explicit labeled_vertex_multiset_vertex_graph(const T&);
            explicit labeled_vertex_multiset_vertex_graph(T&&);

            ~labeled_vertex_multiset_vertex_graph() override = default;

            using labeled_vertex_graph<VertexType,VertexLabelType>::insert_vertex;
            [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&) final;
            [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&) final;
            [[nodiscard]] virtual typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&, const VertexLabelType&) = 0;
            [[nodiscard]] virtual typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&, VertexLabelType&&) = 0;
            [[nodiscard]] virtual typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&, const VertexLabelType&) = 0;
            [[nodiscard]] virtual typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&, VertexLabelType&&) = 0;
        protected:
            T vertices_labeller;
    };

    template<typename VertexType, typename VertexLabelType, typename T>  //TODO: find a better name for "T"
    labeled_vertex_multiset_vertex_graph<VertexType,VertexLabelType,T>::labeled_vertex_multiset_vertex_graph(const T& vl) : vertices_labeller(vl) {}

    template<typename VertexType, typename VertexLabelType, typename T>  //TODO: find a better name for "T"
    labeled_vertex_multiset_vertex_graph<VertexType,VertexLabelType,T>::labeled_vertex_multiset_vertex_graph(T&& vl) : vertices_labeller(std::move(vl)) {}

    template <typename VertexType, typename VertexLabelType, typename T>  //TODO: find a better name for "T"
    typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME labeled_vertex_multiset_vertex_graph<VertexType,VertexLabelType,T>::insert_vertex(const VertexType& vertex_to_insert) {
        return  insert_vertex(vertex_to_insert,vertices_labeller(vertex_to_insert));
    }

    template <typename VertexType, typename VertexLabelType, typename T>  //TODO: find a better name for "T"
    typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME labeled_vertex_multiset_vertex_graph<VertexType,VertexLabelType,T>::insert_vertex(VertexType&& vertex_to_insert) {
        return insert_vertex(std::move(vertex_to_insert),vertices_labeller(vertex_to_insert));
    }
}

#endif //LABELED_VERTEX_MULTISET_VERTEX_GRAPH_H