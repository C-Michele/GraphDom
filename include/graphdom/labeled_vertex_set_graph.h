#ifndef LABELED_VERTEX_SET_GRAPH_H
#define LABELED_VERTEX_SET_GRAPH_H

#include <utility>

#include "labeled_vertex_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType, typename VertexLabelType, typename VertexLabellerType = default_vertex_labeller<VertexType,VertexLabelType>>
    class labeled_vertex_set_graph : virtual public labeled_vertex_graph<VertexType,VertexLabelType>, virtual public set_graph<VertexType> {
        public:
            labeled_vertex_set_graph();
            explicit labeled_vertex_set_graph(const VertexLabellerType&);
            explicit labeled_vertex_set_graph(VertexLabellerType&&);

            ~labeled_vertex_set_graph() override = default;

            [[nodiscard]] constexpr const VertexLabellerType& get_vertices_labeller() const;

            using set_graph<VertexType>::insert_vertex;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&) final;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&) final;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&, const VertexLabelType&) = 0;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&, VertexLabelType&&) = 0;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&, const VertexLabelType&) = 0;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&, VertexLabelType&&) = 0;
        private:
            const VertexLabellerType vertices_labeller;
    };

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    constexpr const VertexLabellerType& labeled_vertex_set_graph<VertexType, VertexLabelType, VertexLabellerType>::get_vertices_labeller() const {
        return vertices_labeller;
    }

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_set_graph() : vertices_labeller() {}

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_set_graph(const VertexLabellerType& vl) : vertices_labeller(vl) {}

    template<typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::labeled_vertex_set_graph(VertexLabellerType&& vl) : vertices_labeller(std::move(vl)) {}

    template <typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    std::pair<typename graph<VertexType>::vertex_handle,bool> labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(const VertexType& vertex_to_insert) {
        return insert_vertex(vertex_to_insert,vertices_labeller(vertex_to_insert));
    }

    template <typename VertexType, typename VertexLabelType, typename VertexLabellerType>
    std::pair<typename graph<VertexType>::vertex_handle,bool> labeled_vertex_set_graph<VertexType,VertexLabelType,VertexLabellerType>::insert_vertex(VertexType&& vertex_to_insert) {
        return insert_vertex(std::move(vertex_to_insert),vertices_labeller(vertex_to_insert));
    }
}

#endif //LABELED_VERTEX_SET_GRAPH_H