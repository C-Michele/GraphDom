#ifndef GRAPHDOM_ADJ_LIST_BASE_ITERATOR_H
#define GRAPHDOM_ADJ_LIST_BASE_ITERATOR_H

#include <variant>

#include "../graph.h"
#include "vertex_container.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType, typename EdgesEndpointsContainerType>
    class graph<VertexType>::adj_list_base_iterator {
        public:
            static_assert(
                std::is_same< VertexContainerPointerType , graphdom::graph<VertexType>::vertex_container* >::value ||
                std::is_same< VertexContainerPointerType , const graphdom::graph<VertexType>::vertex_container* >::value
                ,
                "The typename 'VertexContainerPointerType' of 'graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType,EdgesEndpointsContainerType>' class must be a pointer to graphdom::graph<VertexType>::vertex_container"
            );
            static_assert(
                std::is_same< EdgesEndpointsContainerType , graph<VertexType>::adj_set<VertexContainerPointerType> >::value ||
                std::is_same< EdgesEndpointsContainerType , const graph<VertexType>::adj_set<VertexContainerPointerType> >::value
                ,
                "The typename 'EdgesEndpointsContainerType' of 'graphdom::graph<VertexType>::adj_list_base_iterator<VertexContainerPointerType,EdgesEndpointsContainerType>' class must be graph<VertexType>::adj_set<VertexContainerPointerType> or const graph<VertexType>::adj_set<VertexContainerPointerType>"
            );

            ~adj_list_base_iterator() = default;

            template<typename, typename>
            friend class graph<VertexType>::adj_list_base_iterator;
            template<typename K, typename J>
            [[nodiscard]] constexpr bool operator==(const adj_list_base_iterator<K,J>& other_iterator) const;
            template<typename K, typename J>
            [[nodiscard]] constexpr bool operator!=(const adj_list_base_iterator<K,J>& other_iterator) const;

        protected:
            using special_begin_end_indicator = std::monostate;
            using iterator_type =
                std::variant<
                    special_begin_end_indicator,
                    typename EdgesEndpointsContainerType::iterator
                >;

            adj_list_base_iterator();
            adj_list_base_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                EdgesEndpointsContainerType* edge_begin_point_undirected_adj,
                EdgesEndpointsContainerType* edge_begin_point_directed_adj,
                graphdom::edge_type inner_iterator_edge_current_type
            );
            adj_list_base_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                EdgesEndpointsContainerType* edge_begin_point_undirected_adj,
                EdgesEndpointsContainerType* edge_begin_point_directed_adj,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename EdgesEndpointsContainerType::iterator& inner_iterator
            );

            const graph<VertexType>* iterator_owner_graph;
            graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type;
            EdgesEndpointsContainerType* edge_begin_point_undirected_adj;
            EdgesEndpointsContainerType* edge_begin_point_directed_adj;
            graphdom::edge_type inner_iterator_edge_current_type;
            iterator_type inner_iterator;
    };
}

#include "impl/adj_list_base_iterator.h"

#endif //GRAPHDOM_ADJ_LIST_BASE_ITERATOR_H