#ifndef GRAPHDOM_GRAPH_H
#define GRAPHDOM_GRAPH_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <set>
#include <utility>

/** All entities defined in this library are defined directly or indirectly in this namespace */
namespace graphdom{}

namespace graphdom {
    /// The enumerated type whose values represent the two types of [edges](@ref mathematical_edge_definition) of a [graph](@ref mathematical_graph_definition).
    enum edge_type : std::uint8_t {
        undirected = 0, ///< This enum value means [undirected edge](@ref mathematical_undirected_edge_definition)
        directed = 1 ///< This enum value means [directed edge](@ref mathematical_directed_edge_definition)
    };
}

namespace graphdom {
    /// Every [graph](@ref mathematical_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     *
     * Every graph created with this library can be considered equivalent, with the necessary precautions listed below, to a graph consistent with the [definition found on the "Mathematical Introduction" page](@ref mathematical_graph_definition).<br>
     * Referring to the symbols used in [that definition](@ref mathematical_graph_definition) and considering a non-const reference `g` to this class, the "precautions" are as follows:
     * - \f$ V_\text{type} \f$ is the set of all possible instances of @p VertexType ;
     * - The set \f$ V \f$  must be considered dynamic, to allow, obviously, the insertion and erasion of vertices from `g`;
     * - If `c` is a reference to the [core of a vertex](@ref mathematical_vertex_core_definition) \f$ v \f$ in `g`, then \f$ v = ( \f$ `c` \f$ , \f$ `&c` \f$ ) \f$;
     * - `g` stores only the [cores of its vertices](@ref mathematical_vertex_core_definition); (this is a direct consequence of the previous point)
     * - The sets \f$ E_\text{di} \f$ and \f$ E_\text{un} \f$ must be considered dynamic to allow, obviously, the insertion and erasion of edges from `g`;
     * - If `g` is a [labeled-vertex graph](@ref mathematical_labeled_vertex_graph_definition) and \f$ v \f$ is a vertex in `g`, then \f$ l_V(v) \f$ must be considered dynamic to allow, obviously, the label of \f$ v \f$ to be changed;
     * - If `g` is a [labeled-edge graph](@ref mathematical_labeled_edge_graph_definition) and \f$ y \f$ is an edge in `g`, then \f$ l_E(y) \f$ must be considered dynamic to allow, obviously, the label of \f$ y \f$ to be changed;
     */
    template <typename VertexType>
    class graph {
        public:
            class vertex_handle;
            class vertex_const_handle;
            class adj_list;
            class const_adj_list;
            class adj_list_iterator;
            class adj_list_const_iterator;

            /// To be polymorphic, this class has a virtual destructor.
            virtual ~graph() = default;

            /// Returns the order of `*this`, i.e. the number of vertices inside the graph.
            /**
             * @return The number of vertices inside `*this`.
             */
            [[nodiscard]] virtual std::size_t order() const = 0;

            /// Removes the vertex identified by @p vertex.
            /**
             * After erasion, @p vertex and all its equivalents are invalidated.
             *
             * @param vertex An object that identifies the vertex to be erased.<br>
             * @p vertex must be valid and must identify a vertex belonging to `*this`, otherwise the erasion will cause undefined behavior.
             */
            virtual void erase_vertex(const vertex_const_handle& vertex) = 0;
            [[nodiscard]] virtual adj_list_iterator erase_edge(const adj_list_const_iterator&) = 0;

        /// \cond DEV_DOC
        protected:
            template <typename VertexContainerPointerType>
            class vertex_base_handle;
            template <typename VertexContainerPointerType>
            class base_adj_list;
            template <typename VertexContainerPointerType>
            class adj_list_base_iterator;

            class vertex_container;
            template<typename VertexContainerPointerType>
            class edge_endpoint;
            template <typename VertexContainerPointerType, typename EdgeLabelType>
            class labeled_directed_edge_endpoint;
            template <typename VertexContainerPointerType, typename EdgeLabelType>
            class labeled_undirected_edge_endpoint;
            template<typename VertexContainerPointerType>
            class custom_edge_endpoint_less;
            template<typename VertexContainerPointerType>
            using adj_set = std::set< edge_endpoint<VertexContainerPointerType>* , custom_edge_endpoint_less<VertexContainerPointerType> >;
            enum graph_edges_type : std::uint8_t {
                undirected = edge_type::undirected,
                directed = edge_type::directed,
                mixed
            };
            enum edges_type_selection_type : uint8_t {
                undirected_edges = edge_type::undirected,
                directed_edges = edge_type::directed,
                none
            };
            enum begin_or_end : std::uint8_t {
                begin,
                end
            };
            template<typename VertexContainerPointerType>
            class non_mixed_graph_vertex_container;
            template<typename VertexContainerPointerType>
            class mixed_graph_vertex_container;
            template<typename VertexContainerPointerType, typename VertexLabelType>
            class non_mixed_graph_labeled_vertex_container;
            template<typename VertexContainerPointerType, typename VertexLabelType>
            class mixed_graph_labeled_vertex_container;

            static vertex_handle vertex_ptr_factory(
                const graphdom::graph<VertexType>*,
                const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
                graphdom::edge_type non_mixed_graph_type
            );

            static vertex_handle vertex_ptr_factory(
                const graphdom::graph<VertexType>*,
                const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
            );

            static vertex_const_handle const_vertex_ptr_factory(
                const graphdom::graph<VertexType>*,
                const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
                graphdom::edge_type non_mixed_graph_type
            );

            static vertex_const_handle const_vertex_ptr_factory(
                const graphdom::graph<VertexType>*,
                const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
            );

            static const graphdom::graph<VertexType>* get_owner_graph(const graphdom::graph<VertexType>::vertex_const_handle&);

            static const vertex_container* get_vertex_container(const graphdom::graph<VertexType>::vertex_const_handle&);

            static const graphdom::graph<VertexType>* get_owner_graph(const graphdom::graph<VertexType>::adj_list_const_iterator&);

            static const graphdom::graph<VertexType>::vertex_container* get_begin_point(const graphdom::graph<VertexType>::adj_list_const_iterator&);

            static bool is_limited_by_edge_type(const graphdom::graph<VertexType>::adj_list_const_iterator&);
        /// \endcond DEV_DOC
    };
}

#include "detail/vertex_container.h"
#include "detail/edge_endpoint.h"
#include "detail/labeled_directed_edge_endpoint.h"
#include "detail/labeled_undirected_edge_endpoint.h"
#include "detail/custom_edge_endpoint_less.h"
#include "detail/non_mixed_graph_vertex_container.h"
#include "detail/mixed_graph_vertex_container.h"
#include "detail/non_mixed_graph_labeled_vertex_container.h"
#include "detail/mixed_graph_labeled_vertex_container.h"

#include "detail/vertex_base_handle.h"
#include "detail/vertex_handle.h"
#include "detail/vertex_const_handle.h"
#include "detail/base_adj_list.h"
#include "detail/adj_list.h"
#include "detail/const_adj_list.h"
#include "detail/adj_list_base_iterator.h"
#include "detail/adj_list_iterator.h"
#include "detail/adj_list_const_iterator.h"

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    //TODO: implementation
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    //TODO: implementation
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::const_vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    graphdom::edge_type const non_mixed_graph_type) {
    //TODO: implementation
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::const_vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    //TODO: implementation
}

template<typename VertexType>
const graphdom::graph<VertexType>* graphdom::graph<VertexType>::get_owner_graph(
    const graphdom::graph<VertexType>::vertex_const_handle& ptr) {
    //TODO: implementation
}

template<typename VertexType>
const typename graphdom::graph<VertexType>::vertex_container* graphdom::graph<VertexType>::get_vertex_container(
    const graphdom::graph<VertexType>::vertex_const_handle& ptr) {
    //TODO: implementation
}

template<typename VertexType>
const graphdom::graph<VertexType>* graphdom::graph<VertexType>::get_owner_graph(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    //TODO: implementation
}

template<typename VertexType>
const typename graphdom::graph<VertexType>::vertex_container* graphdom::graph<VertexType>::get_begin_point(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    //TODO: implementation
}

template<typename VertexType>
bool graphdom::graph<VertexType>::is_limited_by_edge_type(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    //TODO: implementation
}

#endif //GRAPHDOM_GRAPH_H
