/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_LABELED_VERTEX_SET_GRAPH_H
#define GRAPHDOM_LABELED_VERTEX_SET_GRAPH_H

#include <utility>

#include "labeled_vertex_graph.h"

namespace graphdom {
    /// Every labeled-vertex set graph created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <
        typename VertexType,
        typename VertexLabelType,
        typename VertexLabellerType = default_vertex_labeller<VertexType,VertexLabelType>
    >
    class labeled_vertex_set_graph : virtual public labeled_vertex_graph<VertexType,VertexLabelType>, virtual public set_graph<VertexType> {
        public:
            labeled_vertex_set_graph();
            explicit labeled_vertex_set_graph(const VertexLabellerType&);
            explicit labeled_vertex_set_graph(VertexLabellerType&&);

            /// To be polymorphic, this class has a virtual destructor.
            ~labeled_vertex_set_graph() override = default;

            [[nodiscard]] constexpr const VertexLabellerType& get_vertices_labeller() const;

            using set_graph<VertexType>::insert_vertex;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.<br>
             * If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to `( this->get_vertices_labeller() )()`
             *
             * @param v_core
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType& v_core) final;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.<br>
             * If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to `( this->get_vertices_labeller() )()`
             *
             * @param v_core
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&& v_core) final;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.<br>
             * If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             *
             * @param v_core
             * @param vertex_label If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType& v_core, const VertexLabelType& vertex_label) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.<br>
             * If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             *
             * @param v_core
             * @param vertex_label If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType& v_core, VertexLabelType&& vertex_label) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.<br>
             * If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             *
             * @param v_core
             * @param vertex_label If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&& v_core, const VertexLabelType& vertex_label) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.<br>
             * If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             *
             * @param v_core
             * @param vertex_label If and as soon as the insertion took place, the [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&& v_core, VertexLabelType&& vertex_label) = 0;
        private:
            VertexLabellerType vertices_labeller;
    };
}

#include "impl/labeled_vertex_set_graph.h"

#endif //GRAPHDOM_LABELED_VERTEX_SET_GRAPH_H