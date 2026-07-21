/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_ADJ_LIST_CONST_ITERATOR_H
#define GRAPHDOM_ADJ_LIST_CONST_ITERATOR_H

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
     * -# `itr` is constructed using an invalid instance of [graphdom::graph< VertexType >::adj_list_iterator](@ref graphdom::graph::adj_list_iterator);
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
    class graph<VertexType>::adj_list_const_iterator final : public graph<VertexType>::adj_list_base_iterator< const graph<VertexType>::vertex_container* > {
        public:
            adj_list_const_iterator();
            /**
             * If @p other_iterator is valid then immediately after the construction of `*this` we will have `*this == other_iterator`.<br>
             * If @p other_iterator is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other_iterator The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            adj_list_const_iterator(const adj_list_const_iterator& other_iterator);
            /**
             * If @p other_iterator is valid then immediately after the construction of `*this` we will have `*this == other_iterator`.<br>
             * If @p other_iterator is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other_iterator The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            adj_list_const_iterator(const graph<VertexType>::adj_list_iterator& other_iterator);
            /**
             * If @p other_iterator is valid then immediately after the construction of `*this` we will have `*this == other_iterator`.<br>
             * If @p other_iterator is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other_iterator The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            adj_list_const_iterator(const typename multiset_graph<VertexType>::adj_list_iterator& other_iterator);

            ~adj_list_const_iterator() = default;

            /**
             * If `*this` is valid then the expression `(*this)->...` is equal to `( *(*this) )->...`.<br>
             * If `*this` is invalid then the expression `(*this)->...` will cause undefined behavior.
             *
             * @return `*(*this)`
             * @par Complexity
             * Constant.
             */
            graph<VertexType>::vertex_const_handle operator->() const;
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
            graph<VertexType>::vertex_const_handle operator*() const;

            adj_list_const_iterator& operator=(const adj_list_const_iterator& other);
            adj_list_const_iterator& operator++();
            [[nodiscard]] adj_list_const_iterator operator++(int);

            /// \cond DEV_DOC
            friend class graph<VertexType>::const_adj_list;
            friend class graph<VertexType>::adj_list;
            friend class multiset_graph<VertexType>::adj_list;
            friend class graph<VertexType>;
            friend class set_graph<VertexType>;
            friend class multiset_graph<VertexType>;
            /// \endcond DEV_DOC
        private:
            adj_list_const_iterator( const graph<VertexType>::adj_list_base_iterator< const graph<VertexType>::vertex_container* >& other );
            adj_list_const_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                const typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type
            );
            adj_list_const_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                const typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::template adj_set<typename graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );
            adj_list_const_iterator(
                const graph<VertexType>* iterator_owner_pointer,
                typename graph<VertexType>::graph_edges_type iterator_owner_graph_edges_type,
                const typename graph<VertexType>::vertex_container* edge_begin_point_vertex_container,
                typename graph<VertexType>::edges_type_selection_type edges_type_restriction,
                graphdom::edge_type inner_iterator_edge_current_type,
                const typename graph<VertexType>::template adj_set<const typename graph<VertexType>::vertex_container*>::iterator& inner_iterator
            );
    };
}

#include "impl/adj_list_const_iterator.h"

#endif //GRAPHDOM_ADJ_LIST_CONST_ITERATOR_H