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

namespace MAIN_LIBRARY_NAMESPACE {
    enum edge_type : std::uint8_t {
        undirected,
        directed
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
            };
            template<typename VertexContainerPointerType>
            using adj_set = std::set< edge_endpoint<VertexContainerPointerType>* , custom_edge_endpoint_less<VertexContainerPointerType> >;
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
    };
}

#include "vertex_ptr.h"
#include "const_vertex_ptr.h"
#include "adj_list.h"
#include "const_adj_list.h"
#include "edge_iterator.h"
#include "const_edge_iterator.h"

#endif //GRAPH_H