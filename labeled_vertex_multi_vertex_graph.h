#ifndef LABELED_VERTEX_MULTI_VERTEX_GRAPH_H
#define LABELED_VERTEX_MULTI_VERTEX_GRAPH_H

#include <utility>

#include "multi_vertex_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType, typename T> //TODO: find a better name for "T"
    class labeled_vertex_multi_vertex_graph : virtual public multi_vertex_graph<VertexType> {
        public:
            ~labeled_vertex_multi_vertex_graph() override = default;

            [[nodiscard]] virtual const VertexLabelType& get_vertex_label(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const = 0;

            [[nodiscard]] virtual VertexLabelType& get_vertex_label(const typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME&) = 0; //TODO: check the signature correctness
            using multi_vertex_graph<VertexType>::insert_vertex;
            [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType& vertex_to_insert) final;
            [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&) final;
            [[nodiscard]] virtual typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(const std::pair<VertexType,VertexLabelType>&) = 0;
            [[nodiscard]] virtual typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME insert_vertex(std::pair<VertexType,VertexLabelType>&&) = 0;
    };

    template<typename VertexType, typename VertexLabelType, typename T> //TODO: find a better name for "T"
    typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME labeled_vertex_multi_vertex_graph<VertexType,VertexLabelType,T>::insert_vertex(const VertexType& vertex_to_insert) {
        return insert_vertex( std::pair( vertex_to_insert,T()(this,vertex_to_insert) ) );
    }

    template<typename VertexType, typename VertexLabelType, typename T> //TODO: find a better name for "T"
    typename MAIN_LIBRARY_NAMESPACE::graph_base<VertexType>::VERTEX_PTR_NAME labeled_vertex_multi_vertex_graph<VertexType,VertexLabelType,T>::insert_vertex(VertexType&& vertex_to_insert) {
        return insert_vertex( std::pair( vertex_to_insert,T()(this,vertex_to_insert) ) );
    }
}

#endif //LABELED_VERTEX_MULTI_VERTEX_GRAPH_H