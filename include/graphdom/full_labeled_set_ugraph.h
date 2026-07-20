/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_FULL_LABELED_SET_UGRAPH_H
#define GRAPHDOM_FULL_LABELED_SET_UGRAPH_H

#include <set>

#include "labeled_vertex_graph.h"
#include "labeled_vertex_set_graph.h"
#include "labeled_edge_graph.h"
#include "labeled_edge_non_mixed_graph.h"

namespace graphdom {
    /**
     *
     * @tparam VertexType
     * @tparam VertexLabelType
     * @tparam EdgeLabelType
     * @tparam Compare
     * @tparam VertexLabellerType
     * @tparam EdgeLabellerType
     */
    template<
        typename VertexType,
        typename VertexLabelType,
        typename EdgeLabelType,
        typename Compare = std::less<VertexType>,
        typename VertexLabellerType = default_vertex_labeller<VertexType,VertexLabelType>,
        typename EdgeLabellerType = default_edge_labeller<VertexType,EdgeLabelType>
    >
    class full_labeled_set_ugraph final :
    virtual public labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>,
    virtual public labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType> {
        public:
            full_labeled_set_ugraph() = default;
            full_labeled_set_ugraph(const Compare& v_comp, const VertexLabellerType& v_lab, const EdgeLabellerType& e_lab);
            full_labeled_set_ugraph(const Compare& v_comp, const VertexLabellerType& v_lab, EdgeLabellerType&& e_lab = EdgeLabellerType());
            full_labeled_set_ugraph(const Compare& v_comp, VertexLabellerType&& v_lab, const EdgeLabellerType& e_lab);
            explicit full_labeled_set_ugraph(const Compare& v_comp, VertexLabellerType&& v_lab = VertexLabellerType(), EdgeLabellerType&& e_lab = EdgeLabellerType());
            full_labeled_set_ugraph(Compare&& v_comp, const VertexLabellerType& v_lab, const EdgeLabellerType& e_lab);
            full_labeled_set_ugraph(Compare&& v_comp, const VertexLabellerType& v_lab, EdgeLabellerType&& e_lab = EdgeLabellerType());
            full_labeled_set_ugraph(Compare&& v_comp, VertexLabellerType&& v_lab, const EdgeLabellerType& e_lab);
            explicit full_labeled_set_ugraph(Compare&& v_comp, VertexLabellerType&& v_lab = VertexLabellerType(), EdgeLabellerType&& e_lab = EdgeLabellerType());

            ~full_labeled_set_ugraph() override;

            /**
             * @copydoc graphdom::graph::order()
             * @par Complexity
             * Constant.
             */
            [[nodiscard]] std::size_t order() const override;
            /**
             * @copydoc graphdom::labeled_vertex_graph::get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) const
             */
            [[nodiscard]] const VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle& vertex) const override;
            /**
             * @copydoc graphdom::labeled_edge_graph::get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) const
             */
            [[nodiscard]] const EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) const override;

            /**
             * @copydoc graphdom::graph::erase_vertex()
             */
            void erase_vertex(const typename graphdom::graph<VertexType>::vertex_const_handle&) override;
            /**
             * @copydoc graphdom::graph::erase_edge()
             */
            [[nodiscard]] typename graphdom::graph<VertexType>::adj_list_iterator erase_edge(const typename graph<VertexType>::adj_list_const_iterator&) override;
            /**
             * @copydoc graphdom::labeled_vertex_graph::get_vertex_label(const typename graph<VertexType>::vertex_const_handle&)
             */
            [[nodiscard]] VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle& vertex) override;
            using graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex;
            /**
             * @copydoc graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(const VertexType&, const VertexLabelType&)
             * @par Complexity
             * Logarithmic in the order of the graph, `O(log(this->order()))`.
             */
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType& v_core, const VertexLabelType& vertex_label) override;
            /**
             * @copydoc graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(const VertexType&, VertexLabelType&&)
             * @par Complexity
             * Logarithmic in the order of the graph, `O(log(this->order()))`.
             */
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType& v_core, VertexLabelType&& vertex_label) override;
            /**
             * @copydoc graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(VertexType&&, const VertexLabelType&)
             * @par Complexity
             * Logarithmic in the order of the graph, `O(log(this->order()))`.
             */
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&& v_core, const VertexLabelType& vertex_label) override;
            /**
             * @copydoc graphdom::labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(VertexType&&, VertexLabelType&&)
             * @par Complexity
             * Logarithmic in the order of the graph, `O(log(this->order()))`.
             */
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&& v_core, VertexLabelType&& vertex_label) override;
            /**
             * @copydoc graphdom::labeled_edge_graph::get_edge_label()
             */
            [[nodiscard]] EdgeLabelType& get_edge_label(const typename graph<VertexType>::adj_list_const_iterator&) override;
            using graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,EdgeLabellerType>::insert_edge;
            /**
             * Inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint, @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             */
            void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, const EdgeLabelType& edge_label) override;
            /**
             * Inserts in `*this` an [undirected edge](@ref mathematical_undirected_edge_definition) having @p first_endpoint, @p second_endpoint as [endpoints](@ref mathematical_edge_endpoint_definition), if `*this` doesn't already contain the same edge.<br>
             * If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .<br>
             * If the insertion did not take place, @p edge_label remains unchanged.
             *
             * @param first_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param second_endpoint This handle must be valid and must identify a vertex belonging to `*this`, otherwise the insertion will cause undefined behavior.
             * @param edge_label If and as soon as the insertion took place, the [label of the inserted edge](@ref mathematical_edge_label_definition) is equal to @p edge_label .
             */
            void insert_edge(const typename graph<VertexType>::vertex_const_handle& first_endpoint, const typename graph<VertexType>::vertex_const_handle& second_endpoint, EdgeLabelType&& edge_label) override;
        private:
            using VertexContainerPointerType = typename graphdom::set_graph<VertexType>::VertexContainerPointerType;
            using edge_endpoint = typename graphdom::set_graph<VertexType>::template labeled_undirected_edge_endpoint<EdgeLabelType>;
            using adj_set = typename graphdom::set_graph<VertexType>::adj_set;
            using vertex_container = typename graphdom::set_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexLabelType>;

            static void safe_edge_endpoint_deallocation(typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>*);

            class custom_vertices_set_compare {
                public:
                    custom_vertices_set_compare() = default;
                    explicit custom_vertices_set_compare(const Compare& comp) : external_compare_functor(comp){}
                    explicit custom_vertices_set_compare(Compare&& comp) : external_compare_functor(std::move(comp)){}

                    bool constexpr operator()(
                        const vertex_container& left,
                        const vertex_container& right ) const {
                        return external_compare_functor(left.vertex,right.vertex);
                    }

                    using is_transparent = void;

                    bool constexpr operator()(
                        const vertex_container& left,
                        const VertexType& right ) const {
                        return external_compare_functor(left.vertex,right);
                    }

                    bool constexpr operator()(
                        const VertexType& left,
                        const vertex_container& right ) const {
                        return external_compare_functor(left,right.vertex);
                    }
                private:
                    Compare external_compare_functor;
            };

            std::set<
                vertex_container,
                custom_vertices_set_compare
            > vertices;
    };
}

#include "impl/full_labeled_set_ugraph.h"

#endif //GRAPHDOM_FULL_LABELED_SET_UGRAPH_H
