#ifndef GRAPHDOM_VERTEX_CONST_HANDLE_H
#define GRAPHDOM_VERTEX_CONST_HANDLE_H

#include "../graph.h"
#include "vertex_container.h"
#include "vertex_base_handle.h"
#include "vertex_handle.h"
#include "../multiset_graph.h"
#include "multiset_graph_vertex_handle.h"

namespace graphdom {
    /**
     * @brief Every valid instance of this class can be used to identify a specific [vertex](@ref mathematical_vertex_definition) of a [graph](@ref graphdom::graph) and to access its [core](@ref mathematical_vertex_core_definition) by reference or pointer.<br>
     * A valid instance `hndl` of this class cannot create objects that allow modification of the graph to which the vertex identified by `hndl` belongs without a non-const reference to that graph.
     *
     * An instance `hndl` of this class is invalidated as soon as one of the following scenarios occurs:
     * -# `hndl` is constructed using an invalid instance of this class.
     * -# `hndl` is constructed using an invalid instance of [graphdom::graph< VertexType >::vertex_handle](@ref graphdom::graph::vertex_handle).
     * -# `hndl` is constructed using an invalid instance of [graphdom::multiset_vertex_graph< VertexType >::vertex_handle](@ref graphdom::multiset_vertex_graph::vertex_handle).
     * -# `hndl = other_hndl;` is executed where `other_hndl` is an invalid instance of this class.
     *
     * A valid instance `hndl` of this class is invalidated as soon as the vertex it is associated with is erased.
     *
     * An invalid instance `hndl` of this class is validated as soon as `hndl = other_hndl;` is executed where `other_hndl` is a valid instance of this class.
     *
     * If `*this` is invalid then any operation other than `*this = other;` and the destruction of `*this` will cause undefined behavior.
     */
    template <typename VertexType>
    class graph<VertexType>::vertex_const_handle final : public graph<VertexType>::vertex_base_handle< const graph<VertexType>::vertex_container* > {
        public:
            vertex_const_handle() = delete;
            /**
             * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            vertex_const_handle(const vertex_const_handle& other);
            /**
             * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            vertex_const_handle(const graph<VertexType>::vertex_handle& other);
            /**
             * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
             * If @p other is invalid then `*this` will be invalid immediately after its construction.
             *
             * @param other The reference to the object from which to construct `*this`.
             * @par Complexity
             * Constant.
             */
            vertex_const_handle(const typename multiset_graph<VertexType>::vertex_handle& other);

            ~vertex_const_handle() = default;

            vertex_const_handle& operator=(const vertex_const_handle& other);

            [[nodiscard]] graph<VertexType>::const_adj_list adj_list() const;
            [[nodiscard]] graph<VertexType>::const_adj_list adj_list(edge_type edge_type) const;
            [[nodiscard]] graph<VertexType>::const_adj_list const_adj_list() const;
            [[nodiscard]] graph<VertexType>::const_adj_list const_adj_list(edge_type edge_type) const;
    };
}

#include "impl/vertex_const_handle.h"

#endif //GRAPHDOM_VERTEX_CONST_HANDLE_H