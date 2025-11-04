#ifndef LABELED_VERTEX_MULTISET_VERTEX_GRAPH_H
#define LABELED_VERTEX_MULTISET_VERTEX_GRAPH_H

#include <utility>

#include "labeled_vertex_graph.h"
#include "multiset_vertex_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType, typename T>  //TODO: find a better name for "T"
    class labeled_vertex_multiset_vertex_graph : virtual public labeled_vertex_graph<VertexType,VertexLabelType>, virtual public multiset_vertex_graph<VertexType> {
        public:
            ~labeled_vertex_multiset_vertex_graph() override = default;

            using labeled_vertex_graph<VertexType,VertexLabelType>::insert_vertex;
            [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&) final;
            [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&) final;
            [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const std::pair<VertexType,VertexLabelType>&) = 0;
            [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(std::pair<VertexType,VertexLabelType>&&) = 0;
    };

    template <typename VertexType, typename VertexLabelType, typename T>  //TODO: find a better name for "T"
    typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME labeled_vertex_multiset_vertex_graph<VertexType,VertexLabelType,T>::insert_vertex(const VertexType& vertex_to_insert) {
        return insert_vertex(vertex_to_insert,T()(vertex_to_insert));
    }

    template <typename VertexType, typename VertexLabelType, typename T>  //TODO: find a better name for "T"
    typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME labeled_vertex_multiset_vertex_graph<VertexType,VertexLabelType,T>::insert_vertex(VertexType&& vertex_to_insert) {
        return insert_vertex(vertex_to_insert,T()(vertex_to_insert));
    }
}

#endif //LABELED_VERTEX_MULTISET_VERTEX_GRAPH_H