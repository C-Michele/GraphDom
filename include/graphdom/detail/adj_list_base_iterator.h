#ifndef GRAPHDOM_ADJ_LIST_BASE_ITERATOR_H
#define GRAPHDOM_ADJ_LIST_BASE_ITERATOR_H

#include <variant>

#include "../graph.h"
#include "vertex_container.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::adj_list_base_iterator {
        public:
            static_assert(
                std::is_same< VertexContainerPointerType , graph<VertexType>::vertex_container* >::value ||
                std::is_same< VertexContainerPointerType , const graph<VertexType>::vertex_container* >::value
                ,
                "The typename 'VertexContainerPointerType' of 'graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType>' class must be a pointer to graphdom::graph<VertexType>::vertex_container"
            );

            ~adj_list_base_iterator() = default;

            template<typename K>
            [[nodiscard]] constexpr bool operator==(const adj_list_base_iterator<K>& other_iterator) const;
            template<typename K>
            [[nodiscard]] constexpr bool operator!=(const adj_list_base_iterator<K>& other_iterator) const;

            [[nodiscard]] constexpr graphdom::edge_type edge_type() const;

            template<typename>
            friend class graph<VertexType>::adj_list_base_iterator;
            template<typename>
            friend class graph<VertexType>::base_adj_list;
        protected:
            using special_begin_end_indicator = std::monostate;
            using iterator_type =
                std::variant<
                    special_begin_end_indicator,
                    typename graph<VertexType>::adj_set<graph<VertexType>::vertex_container*>::iterator,
                    typename graph<VertexType>::adj_set<const graph<VertexType>::vertex_container*>::iterator
                >;

            adj_list_base_iterator();
            adj_list_base_iterator(const adj_list_base_iterator&) = default;
            adj_list_base_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                VertexContainerPointerType edge_begin_point_vertex_container,
                graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type
            );
            adj_list_base_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                VertexContainerPointerType edge_begin_point_vertex_container,
                graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::adj_set<graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );
            adj_list_base_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                VertexContainerPointerType edge_begin_point_vertex_container,
                graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::adj_set<const graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );

            constexpr adj_list_base_iterator& internal_single_increment();

            const graph<VertexType>* iterator_owner_graph;
            graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type;
            VertexContainerPointerType edge_begin_point_vertex_container;
            graph<VertexType>::edges_type_selection_type edges_type_restriction;
            graphdom::edge_type inner_iterator_edge_current_type;
            iterator_type inner_iterator;
        private:
            template <typename K>
            constexpr adj_list_base_iterator& specialized_internal_single_increment();

            template <typename K>
            constexpr graph<VertexType>::adj_set<K>* get_adj_set_if_accessible(graphdom::edge_type edge_type) const;
    };
}

#include "impl/adj_list_base_iterator.h"

#endif //GRAPHDOM_ADJ_LIST_BASE_ITERATOR_H