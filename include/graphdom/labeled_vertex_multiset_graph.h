#ifndef GRAPHDOM_LABELED_VERTEX_MULTISET_GRAPH_H
#define GRAPHDOM_LABELED_VERTEX_MULTISET_GRAPH_H

#include <utility>

#include "labeled_vertex_graph.h"

namespace graphdom {
    /// Every labeled-vertex multiset graph created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <
        typename VertexType,
        typename VertexLabelType,
        typename VertexLabellerType = default_vertex_labeller<VertexType,VertexLabelType>
    >
    class labeled_vertex_multiset_graph : virtual public labeled_vertex_graph<VertexType,VertexLabelType>, virtual public multiset_graph<VertexType> {
        public:
            labeled_vertex_multiset_graph();
            explicit labeled_vertex_multiset_graph(const VertexLabellerType&);
            explicit labeled_vertex_multiset_graph(VertexLabellerType&&);

            /// To be polymorphic, this class has a virtual destructor.
            ~labeled_vertex_multiset_graph() override = default;

            [[nodiscard]] constexpr const VertexLabellerType& get_vertices_labeller() const;

            using multiset_graph<VertexType>::insert_vertex;

            /**
             * Inserts in `*this` a vertex having @p v_core as core and `( this->get_vertices_labeller() )()` as [label](@ref mathematical_vertex_label_definition).
             *
             * @param v_core
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(const VertexType& v_core) final;

            /**
             * Inserts in `*this` a vertex having @p v_core as core and `( this->get_vertices_labeller() )()` as [label](@ref mathematical_vertex_label_definition).
             *
             * @param v_core
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(VertexType&& v_core) final;

            /**
             * Inserts in `*this` a vertex having @p v_core as core and @p vertex_label as [label](@ref mathematical_vertex_label_definition).
             *
             * @param v_core
             * @param vertex_label The [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] virtual typename multiset_graph<VertexType>::vertex_handle insert_vertex(const VertexType& v_core, const VertexLabelType& vertex_label) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core and @p vertex_label as [label](@ref mathematical_vertex_label_definition).
             *
             * @param v_core
             * @param vertex_label The [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] virtual typename multiset_graph<VertexType>::vertex_handle insert_vertex(const VertexType& v_core, VertexLabelType&& vertex_label) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core and @p vertex_label as [label](@ref mathematical_vertex_label_definition).
             *
             * @param v_core
             * @param vertex_label The [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] virtual typename multiset_graph<VertexType>::vertex_handle insert_vertex(VertexType&& v_core, const VertexLabelType& vertex_label) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core and @p vertex_label as [label](@ref mathematical_vertex_label_definition).
             *
             * @param v_core
             * @param vertex_label The [label of the inserted vertex](@ref mathematical_vertex_label_definition) is equal to @p vertex_label .
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] virtual typename multiset_graph<VertexType>::vertex_handle insert_vertex(VertexType&& v_core, VertexLabelType&& vertex_label) = 0;
        private:
            VertexLabellerType vertices_labeller;
    };

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_multiset_graph() : vertices_labeller() {}

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_multiset_graph(const VertexLabellerType& vl) : vertices_labeller(vl) {}

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_multiset_graph(VertexLabellerType&& vl) : vertices_labeller(std::move(vl)) {}

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    constexpr const VertexLabellerType& labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>::get_vertices_labeller() const {
        return vertices_labeller;
    }

    template <typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    typename multiset_graph<VertexType>::vertex_handle labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(const VertexType& v_core) {
        return  insert_vertex(v_core,vertices_labeller(v_core));
    }

    template <typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    typename multiset_graph<VertexType>::vertex_handle labeled_vertex_multiset_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(VertexType&& v_core) {
        return insert_vertex(std::move(v_core),vertices_labeller(v_core));
    }
}

#endif //GRAPHDOM_LABELED_VERTEX_MULTISET_GRAPH_H