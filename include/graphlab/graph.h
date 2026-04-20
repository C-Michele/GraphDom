#ifndef GRAPH_H
#define GRAPH_H

/* TODO: once you have chosen the appropriate names, remove the following macros */
#define CONSTANT_VERTEX_PTR_NAME vertex_const_handle
#define ADJ_LIST adj_list
#define CONSTANT_ADJ_LIST const_adj_list
#define EDGE_ITERATOR_NAME edge_iterator
#define CONSTANT_EDGE_ITERATOR_NAME edge_const_iterator

#include <cstdint>
#include <cstddef>
#include <memory>
#include <set>
#include <utility>

/** All entities defined in this library are defined directly or indirectly in this namespace */
namespace MAIN_LIBRARY_NAMESPACE{}

namespace MAIN_LIBRARY_NAMESPACE {
    /// The enumerated type whose values represent the two types of [edges](@ref mathematical_edge_definition) of a [graph](@ref mathematical_graph_definition).
    enum edge_type : std::uint8_t {
        undirected = 0, ///< This enum value means [undirected edge](@ref mathematical_undirected_edge_definition)
        directed = 1 ///< This enum value means [directed edge](@ref mathematical_undirected_edge_definition)
    };
}

namespace MAIN_LIBRARY_NAMESPACE {
    /// Every [graph](@ref mathematical_graph_definition) created using this library is an instance of a concrete class publicly derived, directly or indirectly, from this polymorphic template class.
    template <typename VertexType>
    class graph {
        public:
            class vertex_handle;
            class CONSTANT_VERTEX_PTR_NAME;
            class ADJ_LIST;
            class CONSTANT_ADJ_LIST;
            class EDGE_ITERATOR_NAME;
            class CONSTANT_EDGE_ITERATOR_NAME;

            /// To be polymorphic, this class has a virtual destructor.
            virtual ~graph() = default;

            /// This method returns the order of the graph, i.e. the number of vertices inside it.
            /**
             * @return The order of the graph.
             */
            [[nodiscard]] virtual std::size_t order() const = 0;

            /// This method removes the vertex associated with @p vertex object.
            /**
             * @param vertex The object associated with the vertex to be erased.
             */
            virtual void erase_vertex(const CONSTANT_VERTEX_PTR_NAME& vertex) = 0;
            [[nodiscard]] virtual EDGE_ITERATOR_NAME erase_edge(const CONSTANT_EDGE_ITERATOR_NAME&) = 0;
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
            class edge_endpoint {
                public:
                    edge_endpoint() = delete;
                    edge_endpoint(const edge_endpoint&) = delete;
                    edge_endpoint(edge_endpoint&&) = delete;
                    explicit edge_endpoint(const VertexContainerPointerType ptr) : vertex_container_ptr(ptr){}

                    ~edge_endpoint() = default;

                    VertexContainerPointerType vertex_container_ptr;
            };
            template <typename VertexContainerPointerType, typename EdgeLabelType>
            class labeled_directed_edge_endpoint final : public edge_endpoint<VertexContainerPointerType> {
                public:
                    labeled_directed_edge_endpoint() = delete;
                    labeled_directed_edge_endpoint(const labeled_directed_edge_endpoint&) = delete;
                    labeled_directed_edge_endpoint(labeled_directed_edge_endpoint&&) = delete;
                    labeled_directed_edge_endpoint(const VertexContainerPointerType ptr, const EdgeLabelType& edge) :
                        edge_endpoint<VertexContainerPointerType>(ptr),
                        edge_label(edge) {}
                    labeled_directed_edge_endpoint(const VertexContainerPointerType ptr, EdgeLabelType&& edge) :
                        edge_endpoint<VertexContainerPointerType>(ptr),
                        edge_label(std::move(edge)) {}

                    ~labeled_directed_edge_endpoint() = default;

                    mutable EdgeLabelType edge_label;
            };
            template <typename VertexContainerPointerType, typename EdgeLabelType>
            class labeled_undirected_edge_endpoint final : public edge_endpoint<VertexContainerPointerType> {
                public:
                    labeled_undirected_edge_endpoint() = delete;
                    labeled_undirected_edge_endpoint(const labeled_undirected_edge_endpoint&) = delete;
                    labeled_undirected_edge_endpoint(labeled_undirected_edge_endpoint&&) = delete;
                    labeled_undirected_edge_endpoint(const VertexContainerPointerType ptr, const EdgeLabelType& edge) :
                        edge_endpoint<VertexContainerPointerType>(ptr),
                        edge_label_ptr(std::make_shared<EdgeLabelType>(edge)) {}
                    labeled_undirected_edge_endpoint(const VertexContainerPointerType ptr, EdgeLabelType&& edge) :
                        edge_endpoint<VertexContainerPointerType>(ptr),
                        edge_label_ptr(std::make_shared<EdgeLabelType>(std::move(edge))) {}
                    labeled_undirected_edge_endpoint(const VertexContainerPointerType ptr, const std::shared_ptr<EdgeLabelType>& existent_edge_label_ptr) :
                        edge_endpoint<VertexContainerPointerType>(ptr),
                        edge_label_ptr(existent_edge_label_ptr) {}

                    ~labeled_undirected_edge_endpoint() = default;

                    mutable std::shared_ptr<EdgeLabelType> edge_label_ptr;
            };
            template<typename VertexContainerPointerType>
            class custom_edge_endpoint_less {
                public:
                    bool operator()(const edge_endpoint<VertexContainerPointerType>* const left, const edge_endpoint<VertexContainerPointerType>* const right) const {
                        return std::less<VertexContainerPointerType>()( left->vertex_container_ptr , right->vertex_container_ptr );
                    }

                    using is_transparent = void;

                    bool operator()(const edge_endpoint<VertexContainerPointerType>* const left, const vertex_container* const right) const {
                        return std::less<const vertex_container*>()( left->vertex_container_ptr , right );
                    }

                    bool operator()(const vertex_container* const left, const edge_endpoint<VertexContainerPointerType>* const right) const {
                        return std::less<const vertex_container*>()( left , right->vertex_container_ptr );
                    }
            };
            template<typename VertexContainerPointerType>
            using adj_set = std::set< edge_endpoint<VertexContainerPointerType>* , custom_edge_endpoint_less<VertexContainerPointerType> >;
            enum graph_edges_type : std::uint8_t {
                undirected = MAIN_LIBRARY_NAMESPACE::edge_type::undirected,
                directed = MAIN_LIBRARY_NAMESPACE::edge_type::directed,
                mixed
            };
            enum begin_or_end : std::uint8_t {
                begin,
                end
            };
            template<typename VertexContainerPointerType>
            class non_mixed_graph_vertex_container : public vertex_container {
                public:
                    non_mixed_graph_vertex_container() = delete;
                    non_mixed_graph_vertex_container(const non_mixed_graph_vertex_container&) = delete;
                    non_mixed_graph_vertex_container(non_mixed_graph_vertex_container&&) = delete;
                    explicit non_mixed_graph_vertex_container(const VertexType& v) : vertex_container(v) {}
                    explicit non_mixed_graph_vertex_container(VertexType&& v) : vertex_container(std::move(v)) {}

                    ~non_mixed_graph_vertex_container() = default;

                    mutable adj_set<VertexContainerPointerType> adj;
            };
            template<typename VertexContainerPointerType>
            class mixed_graph_vertex_container : public vertex_container {
                public:
                    mixed_graph_vertex_container() = delete;
                    mixed_graph_vertex_container(const mixed_graph_vertex_container&) = delete;
                    mixed_graph_vertex_container(mixed_graph_vertex_container&&) = delete;
                    explicit mixed_graph_vertex_container(const VertexType& v) : vertex_container(v) {}
                    explicit mixed_graph_vertex_container(VertexType&& v) : vertex_container(std::move(v)) {}

                    ~mixed_graph_vertex_container() = default;

                    mutable adj_set<VertexContainerPointerType> directed_adj;
                    mutable adj_set<VertexContainerPointerType> undirected_adj;
            };
            template<typename VertexContainerPointerType, typename VertexLabelType>
            class non_mixed_graph_labeled_vertex_container final : public non_mixed_graph_vertex_container<VertexContainerPointerType> {
                public:
                    non_mixed_graph_labeled_vertex_container() = delete;
                    non_mixed_graph_labeled_vertex_container(const non_mixed_graph_labeled_vertex_container&) = delete;
                    non_mixed_graph_labeled_vertex_container(non_mixed_graph_labeled_vertex_container&&) = delete;
                    non_mixed_graph_labeled_vertex_container(const VertexType& v, const VertexLabelType& vl) :
                        non_mixed_graph_vertex_container<VertexContainerPointerType>(v),
                        vertex_label(vl) {}
                    non_mixed_graph_labeled_vertex_container(const VertexType& v, VertexLabelType&& vl) :
                        non_mixed_graph_vertex_container<VertexContainerPointerType>(v),
                        vertex_label(std::move(vl)) {}
                    non_mixed_graph_labeled_vertex_container(VertexType&& v, const VertexLabelType& vl) :
                        non_mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
                        vertex_label(vl) {}
                    non_mixed_graph_labeled_vertex_container(VertexType&& v, VertexLabelType&& vl) :
                        non_mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
                        vertex_label(std::move(vl)) {}

                    ~non_mixed_graph_labeled_vertex_container() = default;

                    mutable VertexLabelType vertex_label;
            };
            template<typename VertexContainerPointerType, typename VertexLabelType>
            class mixed_graph_labeled_vertex_container final : public mixed_graph_vertex_container<VertexContainerPointerType> {
                public:
                    mixed_graph_labeled_vertex_container() = delete;
                    mixed_graph_labeled_vertex_container(const mixed_graph_labeled_vertex_container&) = delete;
                    mixed_graph_labeled_vertex_container(mixed_graph_labeled_vertex_container&&) = delete;
                    mixed_graph_labeled_vertex_container(const VertexType& v, const VertexLabelType& vl) :
                        mixed_graph_vertex_container<VertexContainerPointerType>(v),
                        vertex_label(vl) {}
                    mixed_graph_labeled_vertex_container(const VertexType& v, VertexLabelType&& vl) :
                        mixed_graph_vertex_container<VertexContainerPointerType>(v),
                        vertex_label(std::move(vl)) {}
                    mixed_graph_labeled_vertex_container(VertexType&& v, const VertexLabelType& vl) :
                        mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
                        vertex_label(vl) {}
                    mixed_graph_labeled_vertex_container(VertexType&& v, VertexLabelType&& vl) :
                        mixed_graph_vertex_container<VertexContainerPointerType>(std::move(v)),
                        vertex_label(std::move(vl)) {}

                    ~mixed_graph_labeled_vertex_container() = default;

                    mutable VertexLabelType vertex_label;
            };

            static vertex_handle vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static vertex_handle vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
            );

            static CONSTANT_VERTEX_PTR_NAME const_vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static CONSTANT_VERTEX_PTR_NAME const_vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
            );

            static const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* get_owner_graph(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&);

            static const vertex_container* get_vertex_container(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&);

            static const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* get_owner_graph(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&);

            static const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* get_begin_point(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&);

            static bool is_limited_by_edge_type(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&);
        /// \endcond DEV_DOC
    };
}

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class set_vertex_graph : virtual public graph<VertexType>  {
        public:
            ~set_vertex_graph() override = default;

            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&) = 0;
        protected:
            using VertexContainerPointerType = const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*;
            using edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template edge_endpoint< VertexContainerPointerType >;
            template <typename EdgeLabelType>
            using labeled_directed_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using labeled_undirected_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            using custom_edge_endpoint_less = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template custom_edge_endpoint_less<VertexContainerPointerType>;
            using adj_set = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template adj_set<VertexContainerPointerType>;
            using non_mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>;
            using mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>;
            template <typename EdgeLabelType>
            using non_mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;

            static bool inner_iterator_is_real(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&);

            static typename adj_set::const_iterator get_inner_iterator(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&);

            static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME edge_iterator_factory(
                const MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
                const non_mixed_graph_vertex_container* edge_begin_point_ptr,
                MAIN_LIBRARY_NAMESPACE::edge_type edge_set_vertex_graph_owner_edges_type,
                typename adj_set::iterator inner_itr
            );

            static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME edge_iterator_factory(
                const MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
                const mixed_graph_vertex_container* edge_begin_point_ptr,
                typename adj_set::iterator inner_itr,
                MAIN_LIBRARY_NAMESPACE::edge_type inner_itr_edge_type,
                bool inner_itr_is_limited_by_edge_type = false
            );
    };
}

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class multiset_vertex_graph : virtual public graph<VertexType>  {
        public:
            class vertex_handle;
            class ADJ_LIST;
            class EDGE_ITERATOR_NAME;

            ~multiset_vertex_graph() override = default;

            [[nodiscard]] virtual multiset_vertex_graph::vertex_handle insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual multiset_vertex_graph::vertex_handle insert_vertex(VertexType&&) = 0;
            // [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, const VertexType&) = 0; //TODO: check the signature correctness
            // [[nodiscard]] virtual typename graph<VertexType>::VERTEX_PTR_NAME replace_vertex(typename graph<VertexType>::VERTEX_PTR_NAME&, VertexType&&) = 0; //TODO: check the signature correctness
        protected:
            using VertexContainerPointerType = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*;
            using edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template edge_endpoint< VertexContainerPointerType >;
            template <typename EdgeLabelType>
            using labeled_directed_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using labeled_undirected_edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>;
            using custom_edge_endpoint_less = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template custom_edge_endpoint_less<VertexContainerPointerType>;
            using adj_set = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template adj_set<VertexContainerPointerType>;
            using non_mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>;
            using mixed_graph_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>;
            template <typename EdgeLabelType>
            using non_mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;
            template <typename EdgeLabelType>
            using mixed_graph_labeled_vertex_container = typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_labeled_vertex_container<VertexContainerPointerType,EdgeLabelType>;

            static vertex_handle vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static vertex_handle vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
            );

            static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME const_vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME const_vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
            );

            static VertexContainerPointerType get_vertex_container(const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_handle&);

            static bool inner_iterator_is_real(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&);

        static typename adj_set::const_iterator get_inner_iterator(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&);

        static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME edge_iterator_factory(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            non_mixed_graph_vertex_container* edge_begin_point_ptr,
            MAIN_LIBRARY_NAMESPACE::edge_type edge_multiset_vertex_graph_owner_edges_type,
            typename adj_set::iterator inner_itr
        );

        static typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME edge_iterator_factory(
            const MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            mixed_graph_vertex_container* edge_begin_point_ptr,
            typename adj_set::iterator inner_itr,
            MAIN_LIBRARY_NAMESPACE::edge_type inner_itr_edge_type,
            bool inner_itr_is_limited_by_edge_type = false
        );
    };
}

#include "handlers_declarations.h"
#include "handlers_implementations.h"

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const graph_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    const MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const graph_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::graph<VertexType>::const_vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const graph_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    MAIN_LIBRARY_NAMESPACE::edge_type const non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::graph<VertexType>::const_vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const graph_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& ptr) {
    return ptr.vertex_owner;
}

template<typename VertexType>
const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& ptr) {
    return ptr.graph_vertex_container;
}

template<typename VertexType>
const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& const_edge_itr) {
    return const_edge_itr.edge_graph_owner;
}

template<typename VertexType>
const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_begin_point(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& const_edge_itr) {
    return const_edge_itr.edge_vertex_container_owner;
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::is_limited_by_edge_type(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& const_edge_itr) {
    return const_edge_itr.is_limited_by_edge_type();
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::inner_iterator_is_real(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& const_edge_itr) {
    const auto& set_vertex_graph_edge_info_pair =
        std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::set_vertex_graph_edge_info>( const_edge_itr.type_dependent_edge_info );
    const auto& inner_itr = set_vertex_graph_edge_info_pair.first;
    return std::holds_alternative<
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::real_set_vertex_graph_vertex_container_edge_iterator_type
    >(
        inner_itr
    );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::adj_set::const_iterator
MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::get_inner_iterator(
const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& const_edge_itr) {
    const auto& set_vertex_graph_edge_info_pair =
        std::get<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::set_vertex_graph_edge_info>( const_edge_itr.type_dependent_edge_info );
    const auto& inner_itr = set_vertex_graph_edge_info_pair.first;
    return std::get<
        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::real_set_vertex_graph_vertex_container_edge_iterator_type
    >(
        inner_itr
    );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME
MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::edge_iterator_factory(
    const MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const non_mixed_graph_vertex_container* const edge_begin_point_ptr,
    const MAIN_LIBRARY_NAMESPACE::edge_type edge_set_vertex_graph_owner_edges_type,
    const typename adj_set::iterator inner_itr) {
    return typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME(
        edge_set_vertex_graph_owner_ptr,
        edge_begin_point_ptr,
        edge_set_vertex_graph_owner_edges_type,
        inner_itr
    );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME
MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::edge_iterator_factory(
    const MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>* const edge_set_vertex_graph_owner_ptr,
    const mixed_graph_vertex_container* const edge_begin_point_ptr,
    const typename adj_set::iterator inner_itr,
    const MAIN_LIBRARY_NAMESPACE::edge_type inner_itr_edge_type,
    const bool inner_itr_is_limited_by_edge_type) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME(
        edge_set_vertex_graph_owner_ptr,
        edge_begin_point_ptr,
        inner_itr,
        inner_itr_edge_type,
        inner_itr_is_limited_by_edge_type
    );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_handle MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    const MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_handle MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_handle(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::const_vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    const MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::const_vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::CONSTANT_VERTEX_PTR_NAME(graph_ptr,vertex_container_reference);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VertexContainerPointerType
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::get_vertex_container(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_handle& ptr) {
    return ptr.multiset_graph_vertex_container;
}

template<typename VertexType>
bool MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::inner_iterator_is_real(
const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& const_edge_itr) {
    const auto& multiset_vertex_graph_edge_info_pair =
        std::get<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::multiset_vertex_graph_edge_info>( const_edge_itr.type_dependent_edge_info );
    const auto& inner_itr = multiset_vertex_graph_edge_info_pair.first;
    return std::holds_alternative<
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::real_multiset_vertex_graph_vertex_container_edge_iterator_type
    >(
        inner_itr
    );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::adj_set::const_iterator
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::get_inner_iterator(
const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& const_edge_itr) {
    const auto& multiset_vertex_graph_edge_info_pair =
        std::get<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::multiset_vertex_graph_edge_info>( const_edge_itr.type_dependent_edge_info );
    const auto& inner_itr = multiset_vertex_graph_edge_info_pair.first;
    return std::get<
        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME::real_multiset_vertex_graph_vertex_container_edge_iterator_type
    >(
        inner_itr
    );
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME
MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::edge_iterator_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const edge_multiset_vertex_graph_owner_ptr,
    non_mixed_graph_vertex_container* const edge_begin_point_ptr,
    const MAIN_LIBRARY_NAMESPACE::edge_type edge_multiset_vertex_graph_owner_edges_type,
    const typename adj_set::iterator inner_itr) {
    return typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME(
        edge_multiset_vertex_graph_owner_ptr,
        edge_begin_point_ptr,
        edge_multiset_vertex_graph_owner_edges_type,
        inner_itr
    );
}

#endif //GRAPH_H