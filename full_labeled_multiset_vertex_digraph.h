#ifndef FULL_LABELED_MULTISET_VERTEX_DIGRAPH_H
#define FULL_LABELED_MULTISET_VERTEX_DIGRAPH_H

#include "graph.h"
#include "labeled_vertex_graph.h"
#include "labeled_vertex_multiset_vertex_graph.h"
#include "labeled_edge_graph.h"
#include "labeled_edge_non_mixed_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template<
        typename VertexType,
        typename VertexLabelType,
        typename EdgeLabelType,
        typename T1 = DefaultVertexLabellerType<VertexType,VertexLabelType>, //TODO:: find a better name for T1
        typename T2 = DefaultEdgeLabellerType<VertexType,EdgeLabelType> // TODO: find a better name for T2
    >
    class full_labeled_multiset_vertex_digraph final :
        virtual public labeled_vertex_multiset_vertex_graph<VertexType,VertexLabelType,T1>,
        virtual public labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2> {
            public:
                full_labeled_multiset_vertex_digraph();
                full_labeled_multiset_vertex_digraph(const T1& v_lab, const T2& e_lab);
                full_labeled_multiset_vertex_digraph(const T1& v_lab, T2&& e_lab = T2());
                full_labeled_multiset_vertex_digraph(T1&& v_lab, const T2& e_lab);
                explicit full_labeled_multiset_vertex_digraph(T1&& v_lab, T2&& e_lab = T2());

                ~full_labeled_multiset_vertex_digraph() override;

                [[nodiscard]] std::size_t order() const override;
                [[nodiscard]] const VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const override;
                [[nodiscard]] const EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const override;

                void erase_vertex(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) override; //TODO: look out to memory leaks in ADJ
                [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME erase_edge(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override; //TODO: look out to memory leaks in ADJ
                [[nodiscard]] VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) override;
                using MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::insert_vertex;
                [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&, const VertexLabelType&) override;
                [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(const VertexType&, VertexLabelType&&) override;
                [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&, const VertexLabelType&) override;
                [[nodiscard]] typename multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME insert_vertex(VertexType&&, VertexLabelType&&) override;
                [[nodiscard]] EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override;
                using MAIN_LIBRARY_NAMESPACE::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>::insert_edge;
                void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const EdgeLabelType&) override;
                void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, EdgeLabelType&&) override;
    };
}

//TODO: class implementation

#endif //FULL_LABELED_MULTISET_VERTEX_DIGRAPH_H