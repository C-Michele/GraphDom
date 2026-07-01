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
            class vertex_container {
                public:
                    vertex_container() = delete;
                    vertex_container(const vertex_container&) = delete;
                    vertex_container(vertex_container&&) = delete;
                    explicit vertex_container(const VertexType& v) : vertex(v) {}
                    explicit vertex_container(VertexType&& v) : vertex(std::move(v)) {}

                    ~vertex_container() = default;

                    VertexType vertex;
            };
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
                undirected = graphdom::edge_type::undirected,
                directed = graphdom::edge_type::directed,
                mixed
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

#include "detail/edge_endpoint.h"
#include "detail/labeled_directed_edge_endpoint.h"
#include "detail/labeled_undirected_edge_endpoint.h"
#include "detail/custom_edge_endpoint_less.h"
#include "detail/non_mixed_graph_vertex_container.h"
#include "detail/mixed_graph_vertex_container.h"
#include "detail/non_mixed_graph_labeled_vertex_container.h"
#include "detail/mixed_graph_labeled_vertex_container.h"

namespace graphdom {
    /// Every [set graph](@ref mathematical_set_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <typename VertexType>
    class set_graph : virtual public graph<VertexType>  {
        public:
            /// To be polymorphic, this class has a virtual destructor.
            ~set_graph() override = default;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.
             *
             * @param v_core
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType& v_core) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core, if `*this` doesn't already contain a vertex with an equivalent core.
             *
             * @param v_core
             * @return A pair consisting of a valid handle of the inserted vertex (or the vertex that prevented the insertion) and a bool value set to true if and only if the insertion took place.
             */
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&& v_core) = 0;

        /// \cond DEV_DOC
        protected:
            using VertexContainerPointerType = const typename graphdom::graph<VertexType>::vertex_container*;
            using edge_endpoint = typename graphdom::graph<VertexType>::template edge_endpoint< VertexContainerPointerType >;
            template <typename EdgeLabelType>
            using labeled_directed_edge_endpoint = typename graphdom::graph<VertexType>::template labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using labeled_undirected_edge_endpoint = typename graphdom::graph<VertexType>::template labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            using custom_edge_endpoint_less = typename graphdom::graph<VertexType>::template custom_edge_endpoint_less<VertexContainerPointerType>;
            using adj_set = typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>;
            using non_mixed_graph_vertex_container = typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>;
            using mixed_graph_vertex_container = typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>;
            template <typename EdgeLabelType>
            using non_mixed_graph_labeled_vertex_container = typename graphdom::graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using mixed_graph_labeled_vertex_container = typename graphdom::graph<VertexType>::template mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;

            static typename adj_set::const_iterator get_inner_iterator(const typename graphdom::graph<VertexType>::adj_list_const_iterator&);

            static typename graphdom::graph<VertexType>::adj_list_iterator edge_iterator_factory(
                const graphdom::set_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
                const non_mixed_graph_vertex_container* edge_begin_point_ptr,
                graphdom::edge_type edge_set_vertex_graph_owner_edges_type,
                typename adj_set::iterator inner_itr
            );

            static typename graphdom::graph<VertexType>::adj_list_iterator edge_iterator_factory(
                const graphdom::set_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
                const mixed_graph_vertex_container* edge_begin_point_ptr,
                typename adj_set::iterator inner_itr,
                graphdom::edge_type inner_itr_edge_type,
                bool inner_itr_is_limited_by_edge_type = false
            );
        /// \endcond DEV_DOC
    };
}

namespace graphdom {
    /// Every [multiset graph](@ref mathematical_multiset_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    /**
     * Creating an object of a user-defined class derived, directly or indirectly, from this one will cause undefined behavior.
     */
    template <typename VertexType>
    class multiset_graph : virtual public graph<VertexType>  {
        public:
            class vertex_handle;
            class adj_list;
            class adj_list_iterator;

            /// To be polymorphic, this class has a virtual destructor.
            ~multiset_graph() override = default;

            /**
             * Inserts in `*this` a vertex having @p v_core as core.
             *
             * @param v_core
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] virtual vertex_handle insert_vertex(const VertexType& v_core) = 0;

            /**
             * Inserts in `*this` a vertex having @p v_core as core.
             *
             * @param v_core
             * @return A valid handle of the inserted vertex.
             */
            [[nodiscard]] virtual vertex_handle insert_vertex(VertexType&& v_core) = 0;

        /// \cond DEV_DOC
        protected:
            using VertexContainerPointerType = typename graphdom::graph<VertexType>::vertex_container*;
            using edge_endpoint = typename graphdom::graph<VertexType>::template edge_endpoint< VertexContainerPointerType >;
            template <typename EdgeLabelType>
            using labeled_directed_edge_endpoint = typename graphdom::graph<VertexType>::template labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using labeled_undirected_edge_endpoint = typename graphdom::graph<VertexType>::template labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            using custom_edge_endpoint_less = typename graphdom::graph<VertexType>::template custom_edge_endpoint_less<VertexContainerPointerType>;
            using adj_set = typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>;
            using non_mixed_graph_vertex_container = typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>;
            using mixed_graph_vertex_container = typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>;
            template <typename EdgeLabelType>
            using non_mixed_graph_labeled_vertex_container = typename graphdom::graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using mixed_graph_labeled_vertex_container = typename graphdom::graph<VertexType>::template mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;

            static vertex_handle vertex_ptr_factory(
                const graphdom::multiset_graph<VertexType>*,
                typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
                graphdom::edge_type non_mixed_graph_type
            );

            static vertex_handle vertex_ptr_factory(
                const graphdom::multiset_graph<VertexType>*,
                typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
            );

            static typename graphdom::graph<VertexType>::vertex_const_handle const_vertex_ptr_factory(
                const graphdom::multiset_graph<VertexType>*,
                const typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
                graphdom::edge_type non_mixed_graph_type
            );

            static typename graphdom::graph<VertexType>::vertex_const_handle const_vertex_ptr_factory(
                const graphdom::multiset_graph<VertexType>*,
                const typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
            );

            static VertexContainerPointerType get_vertex_container(const graphdom::multiset_graph<VertexType>::vertex_handle&);

            static typename adj_set::const_iterator get_inner_iterator(const typename graphdom::graph<VertexType>::adj_list_const_iterator&);

            static typename graphdom::graph<VertexType>::adj_list_iterator edge_iterator_factory(
                const graphdom::multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
                non_mixed_graph_vertex_container* edge_begin_point_ptr,
                graphdom::edge_type edge_multiset_vertex_graph_owner_edges_type,
                typename adj_set::iterator inner_itr
            );

            static typename graphdom::graph<VertexType>::adj_list_iterator edge_iterator_factory(
                const graphdom::set_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
                mixed_graph_vertex_container* edge_begin_point_ptr,
                typename adj_set::iterator inner_itr,
                graphdom::edge_type inner_itr_edge_type,
                bool inner_itr_is_limited_by_edge_type = false
            );
        /// \endcond DEV_DOC
    };
}

#include "handlers_declarations.h"
#include "handlers_implementations.h"

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    return graphdom::graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    return graphdom::graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::const_vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    graphdom::edge_type const non_mixed_graph_type) {
    return graphdom::graph<VertexType>::vertex_const_handle(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::graph<VertexType>::const_vertex_ptr_factory(
    const graphdom::graph<VertexType>* const graph_ptr,
    const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    return graphdom::graph<VertexType>::vertex_const_handle(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
const graphdom::graph<VertexType>* graphdom::graph<VertexType>::get_owner_graph(
    const graphdom::graph<VertexType>::vertex_const_handle& ptr) {
    return ptr.vertex_owner;
}

template<typename VertexType>
const typename graphdom::graph<VertexType>::vertex_container* graphdom::graph<VertexType>::get_vertex_container(
    const graphdom::graph<VertexType>::vertex_const_handle& ptr) {
    return ptr.graph_vertex_container;
}

template<typename VertexType>
const graphdom::graph<VertexType>* graphdom::graph<VertexType>::get_owner_graph(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    return const_edge_itr.edge_graph_owner;
}

template<typename VertexType>
const typename graphdom::graph<VertexType>::vertex_container* graphdom::graph<VertexType>::get_begin_point(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    return const_edge_itr.edge_vertex_container_owner;
}

template<typename VertexType>
bool graphdom::graph<VertexType>::is_limited_by_edge_type(
    const graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    return const_edge_itr.is_limited_by_edge_type();
}

template<typename VertexType>
typename graphdom::set_graph<VertexType>::adj_set::const_iterator
graphdom::set_graph<VertexType>::get_inner_iterator(
const typename graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    const auto& set_vertex_graph_edge_info_pair =
        std::get<typename graphdom::graph<VertexType>::adj_list_const_iterator::set_vertex_graph_edge_info>( const_edge_itr.type_dependent_edge_info );
    const auto& inner_itr = set_vertex_graph_edge_info_pair.first;
    return std::get<
        typename graphdom::graph<VertexType>::adj_list_const_iterator::real_set_vertex_graph_vertex_container_edge_iterator_type
    >(
        inner_itr
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::set_graph<VertexType>::edge_iterator_factory(
    const graphdom::set_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const non_mixed_graph_vertex_container* const edge_begin_point_ptr,
    const graphdom::edge_type edge_set_vertex_graph_owner_edges_type,
    const typename adj_set::iterator inner_itr) {
    return typename graphdom::graph<VertexType>::adj_list_iterator(
        edge_set_vertex_graph_owner_ptr,
        edge_begin_point_ptr,
        edge_set_vertex_graph_owner_edges_type,
        inner_itr
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::set_graph<VertexType>::edge_iterator_factory(
    const graphdom::set_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const mixed_graph_vertex_container* const edge_begin_point_ptr,
    const typename adj_set::iterator inner_itr,
    const graphdom::edge_type inner_itr_edge_type,
    const bool inner_itr_is_limited_by_edge_type) {
    return graphdom::graph<VertexType>::adj_list_iterator(
        edge_set_vertex_graph_owner_ptr,
        edge_begin_point_ptr,
        inner_itr,
        inner_itr_edge_type,
        inner_itr_is_limited_by_edge_type
    );
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle graphdom::multiset_graph<VertexType>::vertex_ptr_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    return graphdom::multiset_graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::vertex_handle graphdom::multiset_graph<VertexType>::vertex_ptr_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return graphdom::multiset_graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::multiset_graph<VertexType>::const_vertex_ptr_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    const typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    const graphdom::edge_type non_mixed_graph_type) {
    return graphdom::graph<VertexType>::vertex_const_handle(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename graphdom::graph<VertexType>::vertex_const_handle graphdom::multiset_graph<VertexType>::const_vertex_ptr_factory(
    const graphdom::multiset_graph<VertexType>* const graph_ptr,
    const typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return graphdom::multiset_graph<VertexType>::vertex_const_handle(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::VertexContainerPointerType
graphdom::multiset_graph<VertexType>::get_vertex_container(
    const graphdom::multiset_graph<VertexType>::vertex_handle& ptr) {
    return ptr.multiset_graph_vertex_container;
}

template<typename VertexType>
typename graphdom::multiset_graph<VertexType>::adj_set::const_iterator
graphdom::multiset_graph<VertexType>::get_inner_iterator(
const typename graphdom::graph<VertexType>::adj_list_const_iterator& const_edge_itr) {
    const auto& multiset_vertex_graph_edge_info_pair =
        std::get<typename graphdom::graph<VertexType>::adj_list_const_iterator::multiset_vertex_graph_edge_info>( const_edge_itr.type_dependent_edge_info );
    const auto& inner_itr = multiset_vertex_graph_edge_info_pair.first;
    return std::get<
        typename graphdom::graph<VertexType>::adj_list_const_iterator::real_multiset_vertex_graph_vertex_container_edge_iterator_type
    >(
        inner_itr
    );
}

template<typename VertexType>
typename graphdom::graph<VertexType>::adj_list_iterator
graphdom::multiset_graph<VertexType>::edge_iterator_factory(
    const graphdom::multiset_graph<VertexType>* const edge_multiset_vertex_graph_owner_ptr,
    non_mixed_graph_vertex_container* const edge_begin_point_ptr,
    const graphdom::edge_type edge_multiset_vertex_graph_owner_edges_type,
    const typename adj_set::iterator inner_itr) {
    return typename graphdom::graph<VertexType>::adj_list_iterator(
        edge_multiset_vertex_graph_owner_ptr,
        edge_begin_point_ptr,
        edge_multiset_vertex_graph_owner_edges_type,
        inner_itr
    );
}

#endif //GRAPHDOM_GRAPH_H
