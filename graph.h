#ifndef GRAPH_H
#define GRAPH_H

/* TODO: once you have chosen the appropriate names, remove the following macros */
#define VERTEX_PTR_NAME vertex_ptr
#define CONSTANT_VERTEX_PTR_NAME const_vertex_ptr
#define ADJ_LIST adj_list
#define CONSTANT_ADJ_LIST const_adj_list
#define EDGE_ITERATOR_NAME edge_iterator
#define CONSTANT_EDGE_ITERATOR_NAME const_edge_iterator

#include <cstdint>
#include <cstddef>
#include <memory>
#include <set>
#include <utility>

namespace MAIN_LIBRARY_NAMESPACE {
    enum edge_type : std::uint8_t {
        undirected = 0,
        directed = 1
    };

    template <typename VertexType>
    class graph {
        public:
            class VERTEX_PTR_NAME;
            class CONSTANT_VERTEX_PTR_NAME;
            class ADJ_LIST;
            class CONSTANT_ADJ_LIST;
            class EDGE_ITERATOR_NAME;
            class CONSTANT_EDGE_ITERATOR_NAME;

            virtual ~graph() = default;

            [[nodiscard]] virtual std::size_t order() const = 0;
            // [[nodiscard]] virtual std::size_t size() const = 0;

            //  template <typename... Args >
            //  [[nodiscard]] VERTEX_PTR_NAME emplace_vertex( Args&&... args );
            virtual void erase_vertex(const CONSTANT_VERTEX_PTR_NAME&) = 0;
            [[nodiscard]] virtual EDGE_ITERATOR_NAME erase_edge(const CONSTANT_EDGE_ITERATOR_NAME&) = 0;
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

            template<typename VertexContainerPointerType>
            static void safe_non_labeled_edge_endpoint_deallocation(edge_endpoint<VertexContainerPointerType>*);

            template<typename VertexContainerPointerType, typename EdgeLabelType>
            static void safe_labeled_edge_endpoint_deallocation(edge_endpoint<VertexContainerPointerType>*,edge_type);

            static VERTEX_PTR_NAME vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static VERTEX_PTR_NAME vertex_ptr_factory(
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

            static const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* get_ptr_owner(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&);

            static const vertex_container* get_vertex_container(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&);
    };
}

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class set_vertex_graph : virtual public graph<VertexType>  {
        public:
            ~set_vertex_graph() override = default;

            [[nodiscard]] virtual std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(VertexType&&) = 0;
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

            static void safe_non_labeled_edge_endpoint_deallocation(edge_endpoint*);

            template<typename EdgeLabelType>
            static void safe_labeled_edge_endpoint_deallocation(edge_endpoint*,edge_type);
    };
}

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class multiset_vertex_graph : virtual public graph<VertexType>  {
        public:
            class VERTEX_PTR_NAME;
            class ADJ_LIST;
            class EDGE_ITERATOR_NAME;

            ~multiset_vertex_graph() override = default;

            [[nodiscard]] virtual multiset_vertex_graph::VERTEX_PTR_NAME insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual multiset_vertex_graph::VERTEX_PTR_NAME insert_vertex(VertexType&&) = 0;
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

            static void safe_non_labeled_edge_endpoint_deallocation(edge_endpoint*);

            template<typename VertexLabelType>
            static void safe_labeled_edge_endpoint_deallocation(edge_endpoint*,edge_type);

            static VERTEX_PTR_NAME vertex_ptr_factory(
                const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
                MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
            );

            static VERTEX_PTR_NAME vertex_ptr_factory(
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

            static VertexContainerPointerType get_vertex_container(const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME&);
    };
}

#include "handlers_declarations.h"
#include "handlers_implementations.h"

template<typename VertexType>
template<typename VertexContainerPointerType>
void MAIN_LIBRARY_NAMESPACE::graph<VertexType>::safe_non_labeled_edge_endpoint_deallocation(edge_endpoint<VertexContainerPointerType>* const ee_ptr) {
    delete ee_ptr;
}

template<typename VertexType>
template<typename VertexContainerPointerType, typename EdgeLabelType>
void MAIN_LIBRARY_NAMESPACE::graph<VertexType>::safe_labeled_edge_endpoint_deallocation(
    edge_endpoint<VertexContainerPointerType>* const ee_ptr,
    const edge_type et) {
    switch (et) {
        case undirected:
            delete static_cast< labeled_undirected_edge_endpoint<VertexContainerPointerType,EdgeLabelType>* >(ee_ptr);
            break;
        case directed:
            delete static_cast< labeled_directed_edge_endpoint<VertexContainerPointerType,EdgeLabelType>* >(ee_ptr);
            break;
    }
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const graph_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference,
    const MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* const graph_ptr,
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME(graph_ptr,vertex_container_reference);
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
const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_ptr_owner(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& ptr) {
    return ptr.vertex_owner;
}

template<typename VertexType>
const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container(
    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& ptr) {
    return ptr.graph_vertex_container;
}

template<typename VertexType>
void MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::safe_non_labeled_edge_endpoint_deallocation(edge_endpoint* const ee_ptr) {
    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template safe_non_labeled_edge_endpoint_deallocation<VertexContainerPointerType>(ee_ptr);
}

template<typename VertexType>
template<typename EdgeLabelType>
void MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::safe_labeled_edge_endpoint_deallocation(
    edge_endpoint* const ee_ptr,
    const edge_type ee_type) {
    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template safe_labeled_edge_endpoint_deallocation<VertexContainerPointerType,EdgeLabelType>(ee_ptr,ee_type);
}

template<typename VertexType>
void MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::safe_non_labeled_edge_endpoint_deallocation(edge_endpoint* const ee_ptr) {
    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template safe_non_labeled_edge_endpoint_deallocation<VertexContainerPointerType>(ee_ptr);
}

template<typename VertexType>
template<typename EdgeLabelType>
void MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::safe_labeled_edge_endpoint_deallocation(
    edge_endpoint* const ee_ptr,
    const edge_type ee_type) {
    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template safe_labeled_edge_endpoint_deallocation<VertexContainerPointerType,EdgeLabelType>(ee_ptr,ee_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference,
    const MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type) {
    return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME(graph_ptr,vertex_container_reference,non_mixed_graph_type);
}

template<typename VertexType>
typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::vertex_ptr_factory(
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* const graph_ptr,
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>& vertex_container_reference) {
    return MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME(graph_ptr,vertex_container_reference);
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
    const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME& ptr) {
    return ptr.multiset_graph_vertex_container;
}

#endif //GRAPH_H