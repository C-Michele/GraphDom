/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_H
#define GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_H

#include "../graph.h"
#include "adj_list_base_iterator.h"
#include "../multiset_graph.h"

namespace graphdom {
    /**
     * @brief Every valid instance of this class is conceptually associated with an ordered pair \f$ ( v , e ) \f$  such that \f$ v \f$ is a vertex called "begin point" and \f$ e \f$ is an [out-edge](@ref mathematical_vertex_out_edge_definition) of \f$ v \f$.
     *
     * An instance `itr` of this class is invalidated as soon as one of the following scenarios occurs:
     * -# `itr` is constructed using the default constructor;
     * -# `itr` is constructed using an invalid instance of this class;
     * -# `itr` is constructed using an invalid instance of [graphdom::multiset_graph< VertexType >::adj_list_iterator](@ref graphdom::multiset_graph::adj_list_iterator);
     * -# `itr = other_itr;` is executed where `itr` is an invalid instance of this class;
     *
     * A valid instance `itr` of this class is invalidated as soon as the "begin point" vertex it is associated with is erased.
     *
     * A valid instance `itr` of this class is invalidated as soon as the [out-edge](@ref mathematical_vertex_out_edge_definition) it is associated with is erased.
     *
     * If `*this` is invalid then any operation other than `*this = other;` and the destruction of `*this` will cause undefined behavior.
     */
    template <typename VertexType>
    class multiset_graph<VertexType>::adj_list_iterator final : public graph<VertexType>::template adj_list_base_iterator<typename graph<VertexType>::vertex_container* > {
        public:
            adj_list_iterator() = default;
            /**
             * If @p other is valid then immediately after the construction of `*this` we will have `*this == other_iterator`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            adj_list_iterator(const adj_list_iterator& other);
            /**
             * If @p other is valid and the "begin point" of @p other belongs to a multiset graph, then immediately after the construction of `*this` we will have `*this == other`.<br>
             * If @p other is valid but the "begin point" of @p other belongs to a set graph, then this constructor will throw an instance of a class publicly derived, directly or indirectly, from `std::exception`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            adj_list_iterator(const typename graph<VertexType>::adj_list_iterator& other);

            ~adj_list_iterator() = default;

            /**
             * If `*this` is valid then the expression `(*this)->...` is equal to `( *(*this) )->...`.<br>
             * If `*this` is invalid then the expression `(*this)->...` will cause undefined behavior.
             *
             * @return `*(*this)`
             * @par Complexity
             * Constant.
             */
            multiset_graph<VertexType>::vertex_handle operator->() const;
            /**
             * If \f$ ( v , e ) \f$ is the ordered pair to which `*this` is conceptually associated and \f$ e \f$ is a @ref mathematical_directed_edge_definition "directed edge",<br>
             * then `*(*this)` returns an handle "pointing" to the @ref mathematical_directed_edge_head_definition "head" of \f$ e \f$.
             *
             * If \f$ ( v , e ) \f$ is the ordered pair to which `*this` is conceptually associated and \f$ e \f$ is an @ref mathematical_undirected_edge_definition "undirected edge" such that \f$ e = { v , w } \f$ with \f$ w \neq v \f$,<br>
             * then `*(*this)` returns an handle "pointing" to \f$ w \f$.
             *
             * If \f$ ( v , e ) \f$ is the ordered pair to which `*this` is conceptually associated and \f$ e \f$ is an @ref mathematical_undirected_edge_definition "undirected edge" such that \f$ e = { v } \f$,<br>
             * then `*(*this)` returns an handle "pointing" to \f$ v \f$.
             *
             * @par Complexity
             * Constant.
             */
            multiset_graph<VertexType>::vertex_handle operator*() const;

            adj_list_iterator& operator=(const adj_list_iterator& other);
            adj_list_iterator& operator++();
            [[nodiscard]] adj_list_iterator operator++(int);

            friend class graph<VertexType>::adj_list_const_iterator;
            friend class graph<VertexType>::adj_list_iterator;
            friend class multiset_graph<VertexType>::adj_list;
        private:
            adj_list_iterator( const typename graph<VertexType>::template adj_list_base_iterator<typename graph<VertexType>::vertex_container* >& other );
            adj_list_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type
            );
            adj_list_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::template adj_set<typename graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );
    };
}

#include "impl/multiset_graph_adj_list_iterator.h"

#endif //GRAPHDOM_MULTISET_GRAPH_ADJ_LIST_ITERATOR_H