/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_FULL_LABELED_MULTISET_DIGRAPH_H
#define GRAPHDOM_FULL_LABELED_MULTISET_DIGRAPH_H

#include <forward_list>

#include "labeled_vertex_graph.h"
#include "labeled_vertex_multiset_graph.h"
#include "labeled_edge_graph.h"
#include "labeled_edge_non_mixed_graph.h"

namespace graphdom {
    template<
        typename VertexType,
        typename VertexLabelType,
        typename EdgeLabelType,
        typename VertexLabellerType = default_vertex_labeller<VertexType,VertexLabelType>,
        typename EdgeLabellerType = default_edge_labeller<VertexType,EdgeLabelType>
    >
    class full_labeled_multiset_digraph final :
        virtual public labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>,
        virtual public labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType> {
            public:
                full_labeled_multiset_digraph();
                full_labeled_multiset_digraph(const VertexLabellerType& v_lab, const EdgeLabellerType& e_lab);
                explicit full_labeled_multiset_digraph(const VertexLabellerType& v_lab, EdgeLabellerType&& e_lab = EdgeLabellerType());
                full_labeled_multiset_digraph(VertexLabellerType&& v_lab, const EdgeLabellerType& e_lab);
                explicit full_labeled_multiset_digraph(VertexLabellerType&& v_lab, EdgeLabellerType&& e_lab = EdgeLabellerType());

                ~full_labeled_multiset_digraph() override;

                [[nodiscard]] std::size_t order() const override;
                [[nodiscard]] const VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) const override;
                [[nodiscard]] const EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) const override;

                void erase_vertex(const typename graphdom::graph<VertexType>::vertex_const_handle&) override;
                [[nodiscard]] typename graphdom::graph<VertexType>::adj_list_iterator erase_edge(const typename graph<VertexType>::adj_list_const_iterator&) override;
                [[nodiscard]] VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) override;
                using graphdom::multiset_graph<VertexType>::insert_vertex;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(const VertexType&, const VertexLabelType&) override;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(const VertexType&, VertexLabelType&&) override;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(VertexType&&, const VertexLabelType&) override;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(VertexType&&, VertexLabelType&&) override;
                [[nodiscard]] EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) override;
                using graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::insert_edge;

                /**
                 * Inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p tail as [tail](@ref mathematical_directed_edge_tail_definition) and @p head as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
                 * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
                 *
                 * @param tail This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
                 * @param head This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
                 * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
                 */
                void insert_edge(const typename graph<VertexType>::vertex_const_handle& tail, const typename graph<VertexType>::vertex_const_handle& head, const EdgeLabelType& edge_label) override;

                /**
                 * Inserts in `*this` a [directed edge](@ref mathematical_directed_edge_definition) having @p tail as [tail](@ref mathematical_directed_edge_tail_definition) and @p head as [head](@ref mathematical_directed_edge_head_definition), if `*this` doesn't already contain the same edge.<br>
                 * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
                 *
                 * @param tail This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
                 * @param head This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
                 * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
                 */
                void insert_edge(const typename graph<VertexType>::vertex_const_handle& tail, const typename graph<VertexType>::vertex_const_handle& head, EdgeLabelType&& edge_label) override;
            private:
                using VertexContainerPointerType = typename graphdom::multiset_graph<VertexType>::VertexContainerPointerType;
                using edge_endpoint = typename graphdom::multiset_graph<VertexType>::template labeled_directed_edge_endpoint<EdgeLabelType>;
                using vertex_container = typename graphdom::multiset_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexLabelType>;

                static void safe_edge_endpoint_deallocation(typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>*);

                std::forward_list<vertex_container> vertices;
                std::size_t number_of_vertices_inserted;
    };
}

#include "impl/full_labeled_multiset_digraph.h"

#endif //GRAPHDOM_FULL_LABELED_MULTISET_DIGRAPH_H