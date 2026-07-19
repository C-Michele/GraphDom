/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_FULL_LABELED_SET_DIGRAPH_H
#define GRAPHDOM_FULL_LABELED_SET_DIGRAPH_H

#include <set>

#include "labeled_vertex_graph.h"
#include "labeled_vertex_set_graph.h"
#include "labeled_edge_graph.h"
#include "labeled_edge_non_mixed_graph.h"

namespace graphdom {
    template<
        typename VertexType,
        typename VertexLabelType,
        typename EdgeLabelType,
        typename Compare = std::less<VertexType>,
        typename T1 = default_vertex_labeller<VertexType,VertexLabelType>, //TODO:: find a better name for T1
        typename T2 = default_edge_labeller<VertexType,EdgeLabelType> // TODO: find a better name for T2
    >
    class full_labeled_set_digraph final :
    virtual public labeled_vertex_set_graph<VertexType,VertexLabelType,T1>,
    virtual public labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2> {
        public:
            full_labeled_set_digraph() = default;
            full_labeled_set_digraph(const Compare& v_comp, const T1& v_lab, const T2& e_lab);
            full_labeled_set_digraph(const Compare& v_comp, const T1& v_lab, T2&& e_lab = T2());
            full_labeled_set_digraph(const Compare& v_comp, T1&& v_lab, const T2& e_lab);
            explicit full_labeled_set_digraph(const Compare& v_comp, T1&& v_lab = T1(), T2&& e_lab = T2());
            full_labeled_set_digraph(Compare&& v_comp, const T1& v_lab, const T2& e_lab);
            full_labeled_set_digraph(Compare&& v_comp, const T1& v_lab, T2&& e_lab = T2());
            full_labeled_set_digraph(Compare&& v_comp, T1&& v_lab, const T2& e_lab);
            explicit full_labeled_set_digraph(Compare&& v_comp, T1&& v_lab = T1(), T2&& e_lab = T2());

            ~full_labeled_set_digraph() override;

            [[nodiscard]] std::size_t order() const override;
            [[nodiscard]] const VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) const override;
            [[nodiscard]] const EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) const override;

            void erase_vertex(const typename graphdom::graph<VertexType>::vertex_const_handle&) override; //TODO: look out to memory leaks in ADJ
            [[nodiscard]] typename graphdom::graph<VertexType>::adj_list_iterator erase_edge(const typename graph<VertexType>::adj_list_const_iterator&) override; //TODO: look out to memory leaks in ADJ
            [[nodiscard]] VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) override;
            using graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,T1>::insert_vertex;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&, const VertexLabelType&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&, VertexLabelType&&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&, const VertexLabelType&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&, VertexLabelType&&) override;
            [[nodiscard]] EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) override;
            using graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>::insert_edge;
            void insert_edge(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, const EdgeLabelType&) override;
            void insert_edge(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, EdgeLabelType&&) override;
        private:
            using VertexContainerPointerType = typename graphdom::set_graph<VertexType>::VertexContainerPointerType;
            using edge_endpoint = typename graphdom::set_graph<VertexType>::template labeled_directed_edge_endpoint<EdgeLabelType>;
            using adj_set = typename graphdom::set_graph<VertexType>::adj_set;
            using vertex_container = typename graphdom::set_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexLabelType>;

            static void safe_edge_endpoint_deallocation(typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>*);

            class custom_vertices_set_compare {
                public:
                    custom_vertices_set_compare() = default;
                    explicit custom_vertices_set_compare(const Compare& comp) : external_vertex_less_functor(comp){}
                    explicit custom_vertices_set_compare(Compare&& comp) : external_vertex_less_functor(std::move(comp)){}

                    bool constexpr operator()(
                        const vertex_container& left,
                        const vertex_container& right ) const {
                        return external_vertex_less_functor(left.vertex,right.vertex);
                    }

                    using is_transparent = void;

                    bool constexpr operator()(
                        const vertex_container& left,
                        const VertexType& right ) const {
                        return external_vertex_less_functor(left.vertex,right);
                    }

                    bool constexpr operator()(
                        const VertexType& left,
                        const vertex_container& right ) const {
                        return external_vertex_less_functor(left,right.vertex);
                    }
                private:
                    Compare external_vertex_less_functor;
            };

            std::set<
                vertex_container,
                custom_vertices_set_compare
            > vertices;
    };
}

#include "impl/full_labeled_set_digraph.h"

#endif //GRAPHDOM_FULL_LABELED_SET_DIGRAPH_H