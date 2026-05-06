#ifndef HANDLERS_DECLARATIONS_H
#define HANDLERS_DECLARATIONS_H

#include "graph.h"

/// Every valid instance of this class can be used to identify a specific [vertex](@ref mathematical_vertex_definition) of a [graph](@ref MAIN_LIBRARY_NAMESPACE::graph) and to access its [core](@ref mathematical_vertex_core_definition) by reference or pointer.
/**
 * An instance `hndl` of this class is invalidated as soon as one of the following scenarios occurs:
 * -# `hndl` is constructed using an invalid instance of this class.
 * -# `hndl` is constructed using an invalid instance of [MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph< VertexType >::vertex_handle](@ref MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph::vertex_handle).
 * -# `hndl = other_hndl;` is executed where `other_hndl` is an invalid instance of this class.
 *
 * A valid instance `hndl` of this class is invalidated as soon as the vertex it is associated with is erased.
 *
 * An invalid instance `hndl` of this class is validated as soon as `hndl = other_hndl;` is executed where `other_hndl` is a valid instance of this class.
 *
 * If `*this` is invalid then any operation other than `*this = other;` and the destruction of `*this` will cause undefined behavior.
 */
template <typename VertexType>
class graphdom::graph<VertexType>::vertex_handle final {
    public:
        vertex_handle() = delete;
        vertex_handle(const vertex_handle&) = default;

        /**
         * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
         * If @p other is invalid then `*this` will be invalid immediately after its construction.
         *
         * @param other The reference to the object from which to construct `*this`.
         * @par Complexity
         * Constant.
         */
        vertex_handle(const typename graphdom::multiset_graph<VertexType>::vertex_handle& other);

        /**
         * If `*this` is invalid, invoking this conversion operator via `*this` will cause undefined behavior.<br>
         * If `*this` is valid and identifies a vertex belonging to a set-vertex graph, invoking this conversion operator via `*this` will throw an instance of a class publicly derived, directly or indirectly, from `std::exception`.
         *
         * @par Complexity
         * Constant.
         */
        explicit operator typename graphdom::multiset_graph<VertexType>::vertex_handle() const;

        /**
         * If `*this` is valid then `*(*this)` returns a const reference to the core of the vertex identified by `*this`.<br>
         * If `*this` is invalid then `*(*this)` will cause undefined behavior.
         *
         * @return A const reference to the core of the vertex identified by `*this`.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] const VertexType& operator*() const;

        /**
         * If `*this` is valid then the expression `(*this)->...` is equal to `( &( *(*this) ) )->...`.<br>
         * If `*this` is invalid then the expression `(*this)->...` will cause undefined behavior.
         *
         * @return `&( *(*this) )`
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] const VertexType* operator->() const;

        /**
         * Returns `true` if `*this` and @p other are valid and identify the same vertex of the same graph.<br>
         * Returns `false` if `*this` and @p other are valid, identify different vertices, and the vertices identified by `*this` and @p other belong to the same graph.<br>
         * In other cases, `*this == other` will cause undefined behavior.
         *
         * @param other The object to compare with `*this`.
         * @return The comparison result.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] bool operator==(const graphdom::graph<VertexType>::vertex_const_handle& other) const;

        /**
         * `*this != other` has the same behavior of `!( *this == other)`.
         *
         * @param other The object to compare with `*this`.
         * @return The same result of `!( *this == other)`.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] bool operator!=(const graphdom::graph<VertexType>::vertex_const_handle& other) const;

        vertex_handle& operator=(const vertex_handle&) = default;

        [[nodiscard]] graphdom::graph<VertexType>::ADJ_LIST adj_list() const;
        [[nodiscard]] graphdom::graph<VertexType>::ADJ_LIST adj_list(graphdom::edge_type) const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(graphdom::edge_type) const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>::vertex_const_handle;
        friend class graphdom::graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class graphdom::multiset_graph<VertexType>::vertex_handle;
        friend class graphdom::graph<VertexType>;
        /// \endcond DEV_DOC
    private:
        vertex_handle(
            const graphdom::graph<VertexType>*,
            const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
            graphdom::edge_type non_mixed_graph_type
        );
        vertex_handle(
            const graphdom::graph<VertexType>*,
            const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
        );

        const graphdom::graph<VertexType>* vertex_owner;
        std::variant<
            std::monostate,
            const graphdom::graph<VertexType>::vertex_container*,
            graphdom::graph<VertexType>::vertex_container*
        > vertex_container_ptr;
        graphdom::graph<VertexType>::graph_edges_type edges_type;
};

/**
 * @brief Every valid instance of this class can be used to identify a specific [vertex](@ref mathematical_vertex_definition) of a [graph](@ref MAIN_LIBRARY_NAMESPACE::graph) and to access its [core](@ref mathematical_vertex_core_definition) by reference or pointer.<br>
 * A valid instance `hndl` of this class cannot create objects that allow modification of the graph to which the vertex identified by `hndl` belongs without a non-const reference to that graph.
 *
 * An instance `hndl` of this class is invalidated as soon as one of the following scenarios occurs:
 * -# `hndl` is constructed using an invalid instance of this class.
 * -# `hndl` is constructed using an invalid instance of [MAIN_LIBRARY_NAMESPACE::graph< VertexType >::vertex_handle](@ref MAIN_LIBRARY_NAMESPACE::graph::vertex_handle).
 * -# `hndl` is constructed using an invalid instance of [MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph< VertexType >::vertex_handle](@ref MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph::vertex_handle).
 * -# `hndl = other_hndl;` is executed where `other_hndl` is an invalid instance of this class.
 *
 * A valid instance `hndl` of this class is invalidated as soon as the vertex it is associated with is erased.
 *
 * An invalid instance `hndl` of this class is validated as soon as `hndl = other_hndl;` is executed where `other_hndl` is a valid instance of this class.
 *
 * If `*this` is invalid then any operation other than `*this = other;` and the destruction of `*this` will cause undefined behavior.
 */
template <typename VertexType>
class graphdom::graph<VertexType>::vertex_const_handle final {
    public:
        vertex_const_handle() = delete;
        vertex_const_handle(const vertex_const_handle&) = default;

        /**
         * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
         * If @p other is invalid then `*this` will be invalid immediately after its construction.
         *
         * @param other The reference to the object from which to construct `*this`.
         * @par Complexity
         * Constant.
         */
        vertex_const_handle(const graphdom::graph<VertexType>::vertex_handle& other);

        /**
         * If @p other is valid then immediately after the construction of `*this` we will have `*this == other`.<br>
         * If @p other is invalid then `*this` will be invalid immediately after its construction.
         *
         * @param other The reference to the object from which to construct `*this`.
         * @par Complexity
         * Constant.
         */
        vertex_const_handle(const typename graphdom::multiset_graph<VertexType>::vertex_handle& other);

        /**
         * If `*this` is valid then `*(*this)` returns a const reference to the core of the vertex identified by `*this`.<br>
         * If `*this` is invalid then `*(*this)` will cause undefined behavior.
         *
         * @return A const reference to the core of the vertex identified by `*this`.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] const VertexType& operator*() const;

        /**
         * If `*this` is valid then the expression `(*this)->...` is equal to `( &( *(*this) ) )->...`.<br>
         * If `*this` is invalid then the expression `(*this)->...` will cause undefined behavior.
         *
         * @return `&( *(*this) )`
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] const VertexType* operator->() const;

        /**
         * Returns `true` if `*this` and @p other are valid and identify the same vertex of the same graph.<br>
         * Returns `false` if `*this` and @p other are valid, identify different vertices, and the vertices identified by `*this` and @p other belong to the same graph.<br>
         * In other cases, `*this == other` will cause undefined behavior.
         *
         * @param other The object to compare with `*this`.
         * @return The comparison result.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] bool operator==(const vertex_const_handle& other) const;

        /**
         * `*this != other` has the same behavior of `!( *this == other )`.
         *
         * @param other The object to compare with `*this`.
         * @return The same result of `!( *this == other)`.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] bool operator!=(const vertex_const_handle& other) const;

        vertex_const_handle& operator=(const vertex_const_handle&) = default;

        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_ADJ_LIST adj_list() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(graphdom::edge_type) const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(graphdom::edge_type) const;

        /// \cond DEV_DOC
        friend bool graphdom::graph<VertexType>::vertex_handle::operator==(const vertex_const_handle&) const;
        friend bool graphdom::graph<VertexType>::vertex_handle::operator!=(const vertex_const_handle&) const;
        friend class graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class graphdom::multiset_graph<VertexType>::vertex_handle;
        friend class graphdom::graph<VertexType>;
        friend class graphdom::multiset_graph<VertexType>;
        /// \endcond DEV_DOC
    private:
        vertex_const_handle(
            const graphdom::graph<VertexType>*,
            const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
            graphdom::edge_type non_mixed_graph_type
        );
        vertex_const_handle(
            const graphdom::graph<VertexType>*,
            const graphdom::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
        );
        vertex_const_handle(
            const graphdom::multiset_graph<VertexType>*,
            const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<vertex_container*>&,
            graphdom::edge_type non_mixed_graph_type
        );
        vertex_const_handle(
            const graphdom::multiset_graph<VertexType>*,
            const graphdom::graph<VertexType>::mixed_graph_vertex_container<vertex_container*>&
        );

        const graphdom::graph<VertexType>* vertex_owner;
        const graphdom::graph<VertexType>::vertex_container* graph_vertex_container;
        graphdom::graph<VertexType>::graph_edges_type edges_type;
};

template <typename VertexType>
class graphdom::graph<VertexType>::ADJ_LIST {
    public:
        ADJ_LIST() = delete;
        ADJ_LIST(const ADJ_LIST&) = default;
        ADJ_LIST(const typename graphdom::multiset_graph<VertexType>::ADJ_LIST&);

        [[nodiscard]] graphdom::graph<VertexType>::EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] graphdom::graph<VertexType>::EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>::CONSTANT_ADJ_LIST;
        friend class graphdom::graph<VertexType>::vertex_handle;
        friend class graphdom::multiset_graph<VertexType>::ADJ_LIST;
        /// \endcond DEV_DOC
    private:
        ADJ_LIST(
            const graphdom::graph<VertexType>* vertex_container_graph_owner_ptr,
            const std::variant<
                std::monostate,
                const graphdom::graph<VertexType>::vertex_container*,
                graphdom::graph<VertexType>::vertex_container*
            >& vertex_container_ptr,
            graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type
        );
        ADJ_LIST(
            const graphdom::graph<VertexType>* vertex_container_graph_owner_ptr,
            const std::variant<
                std::monostate,
                const graphdom::graph<VertexType>::vertex_container*,
                graphdom::graph<VertexType>::vertex_container*
            >& vertex_container_ptr,
            graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type,
            graphdom::edge_type edges_type_selected
        );

        const graphdom::graph<VertexType>* vertex_container_graph_owner;
        graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type;

        using set_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;
        using set_vertex_graph_vertex_container_info_type =
            std::pair<
                const graphdom::graph<VertexType>::vertex_container*,
                set_vertex_graph_vertex_container_adj_sets_ptr_array_type
            >;
        using multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;
        using multiset_vertex_graph_vertex_container_info_type =
            std::pair<
                graphdom::graph<VertexType>::vertex_container*,
                multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type
            >;
        std::variant<
            set_vertex_graph_vertex_container_info_type,
            multiset_vertex_graph_vertex_container_info_type
        > graph_type_dependent_vertex_container_info;
};

template <typename VertexType>
class graphdom::graph<VertexType>::CONSTANT_ADJ_LIST {
    public:
        CONSTANT_ADJ_LIST() = delete;
        CONSTANT_ADJ_LIST(const CONSTANT_ADJ_LIST&) = default;
        CONSTANT_ADJ_LIST(const ADJ_LIST&);
        CONSTANT_ADJ_LIST(const typename graphdom::multiset_graph<VertexType>::ADJ_LIST&);

        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>::vertex_handle;
        friend class graphdom::graph<VertexType>::vertex_const_handle;
        friend class graphdom::multiset_graph<VertexType>::vertex_handle;
        /// \endcond DEV_DOC
    private:
        CONSTANT_ADJ_LIST(
            const graphdom::graph<VertexType>* vertex_container_graph_owner_ptr,
            const graphdom::graph<VertexType>::vertex_container* vertex_container_ptr,
            graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type
        );
        CONSTANT_ADJ_LIST(
            const graphdom::graph<VertexType>* vertex_container_graph_owner_ptr,
            const graphdom::graph<VertexType>::vertex_container* vertex_container_ptr,
            graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type,
            graphdom::edge_type edges_type_selected
        );

        const graphdom::graph<VertexType>* vertex_container_graph_owner;
        graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type;
        const graphdom::graph<VertexType>::vertex_container* vertex_container_ptr;

        using set_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                const graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;
        using multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                const graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;

        std::variant<
            set_vertex_graph_vertex_container_adj_sets_ptr_array_type,
            multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type
        > vertex_container_adj_sets_ptr_array;
};

template <typename VertexType>
class graphdom::graph<VertexType>::EDGE_ITERATOR_NAME final {
    public:
        EDGE_ITERATOR_NAME() = delete;
        EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&) = default;
        EDGE_ITERATOR_NAME(const typename graphdom::multiset_graph<VertexType>::EDGE_ITERATOR_NAME&);

        [[nodiscard]] graphdom::graph<VertexType>::vertex_handle operator*() const;
        [[nodiscard]] graphdom::graph<VertexType>::vertex_handle operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_EDGE_ITERATOR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_EDGE_ITERATOR_NAME&) const;

        EDGE_ITERATOR_NAME& operator=(const EDGE_ITERATOR_NAME&) = default;
        EDGE_ITERATOR_NAME& operator++();
        [[nodiscard]] EDGE_ITERATOR_NAME operator++(int);

        [[nodiscard]] graphdom::edge_type edge_type() const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class graphdom::graph<VertexType>::ADJ_LIST;
        friend class graphdom::multiset_graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class graphdom::graph<VertexType>;
        friend class graphdom::set_graph<VertexType>;
        friend class graphdom::multiset_graph<VertexType>;
        /// \endcond DEV_DOC
    private:
        EDGE_ITERATOR_NAME(
            const graphdom::graph<VertexType>* edge_set_vertex_graph_owner_ptr,
            const graphdom::graph<VertexType>::vertex_container* edge_begin_point_ptr,
            graphdom::graph<VertexType>::graph_edges_type edge_set_vertex_graph_owner_edges_type,
            const std::array<
                graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
                2
            >& edge_begin_point_adj_sets_array_ptr,
            graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator
        );
        EDGE_ITERATOR_NAME(
            const graphdom::graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            graphdom::graph<VertexType>::vertex_container* edge_begin_point_ptr,
            graphdom::graph<VertexType>::graph_edges_type edge_multiset_vertex_graph_owner_edges_type,
            const std::array<
                graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
                2
            >& edge_begin_point_adj_sets_array_ptr,
            graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator
        );
        EDGE_ITERATOR_NAME(
            const graphdom::set_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
            const graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                const graphdom::graph<VertexType>::vertex_container*
            >* edge_begin_point_ptr,
            graphdom::edge_type edge_set_vertex_graph_owner_edges_type,
            typename graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr
        );
        EDGE_ITERATOR_NAME(
            const graphdom::set_graph<VertexType>* edge_set_vertex_graph_owner_ptr,
            const graphdom::graph<VertexType>::mixed_graph_vertex_container<
                const graphdom::graph<VertexType>::vertex_container*
            >* edge_begin_point_ptr,
            typename graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr,
            graphdom::edge_type inner_itr_edge_type,
            bool inner_itr_is_limited_by_edge_type = false
        );
        EDGE_ITERATOR_NAME(
            const graphdom::multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            graphdom::graph<VertexType>::non_mixed_graph_vertex_container<
                graphdom::graph<VertexType>::vertex_container*
            >* edge_begin_point_ptr,
            graphdom::edge_type edge_multiset_vertex_graph_owner_edges_type,
            typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr
        );
        EDGE_ITERATOR_NAME(
            const graphdom::multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            graphdom::graph<VertexType>::mixed_graph_vertex_container<
                graphdom::graph<VertexType>::vertex_container*
            >* edge_begin_point_ptr,
            typename graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>::iterator inner_itr,
            graphdom::edge_type inner_itr_edge_type,
            bool inner_itr_is_limited_by_edge_type = false
        );

        const graphdom::graph<VertexType>* edge_owner;
        graphdom::graph<VertexType>::graph_edges_type graph_owner_edges_type;

        using special_begin_end_indicator = std::monostate;

        using real_set_vertex_graph_vertex_container_edge_iterator_type =
            typename graphdom::graph<VertexType>::adj_set<
                const graphdom::graph<VertexType>::vertex_container*
            >::iterator;
        using set_vertex_graph_inner_edge_iterator_type =
            std::variant<
                special_begin_end_indicator,
                real_set_vertex_graph_vertex_container_edge_iterator_type
            >;
        using set_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;
        using set_vertex_graph_edge_info =
            std::tuple<
                const graphdom::graph<VertexType>::vertex_container*,
                set_vertex_graph_inner_edge_iterator_type,
                set_vertex_graph_vertex_container_adj_sets_ptr_array_type
            >;
        using real_multiset_vertex_graph_vertex_container_edge_iterator_type =
            typename graphdom::graph<VertexType>::adj_set<
                graphdom::graph<VertexType>::vertex_container*
            >::iterator;
        using multiset_vertex_graph_inner_edge_iterator_type =
            std::variant<
                special_begin_end_indicator,
                real_multiset_vertex_graph_vertex_container_edge_iterator_type
            >;
        using multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;
        using multiset_vertex_graph_edge_info =
            std::tuple<
                graphdom::graph<VertexType>::vertex_container*,
                multiset_vertex_graph_inner_edge_iterator_type,
                multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type
            >;

        std::variant<
            set_vertex_graph_edge_info,
            multiset_vertex_graph_edge_info
        > type_dependent_edge_info;

        graphdom::edge_type current_edge_type;
};

template <typename VertexType>
class graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME final {
    public:
        CONSTANT_EDGE_ITERATOR_NAME() = delete;
        CONSTANT_EDGE_ITERATOR_NAME(const CONSTANT_EDGE_ITERATOR_NAME&) = default;
        CONSTANT_EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&);
        CONSTANT_EDGE_ITERATOR_NAME(const typename graphdom::multiset_graph<VertexType>::EDGE_ITERATOR_NAME&);

        [[nodiscard]] graphdom::graph<VertexType>::vertex_const_handle operator*() const;
        [[nodiscard]] graphdom::graph<VertexType>::vertex_const_handle operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_EDGE_ITERATOR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_EDGE_ITERATOR_NAME&) const;

        CONSTANT_EDGE_ITERATOR_NAME& operator=(const CONSTANT_EDGE_ITERATOR_NAME&) = default;
        CONSTANT_EDGE_ITERATOR_NAME& operator++();
        [[nodiscard]] CONSTANT_EDGE_ITERATOR_NAME operator++(int);

        [[nodiscard]] graphdom::edge_type edge_type() const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>;
        friend class graphdom::graph<VertexType>::ADJ_LIST;
        friend class graphdom::graph<VertexType>::CONSTANT_ADJ_LIST;
        friend class graphdom::multiset_graph<VertexType>::ADJ_LIST;
        friend bool graphdom::graph<VertexType>::EDGE_ITERATOR_NAME::operator==(const CONSTANT_EDGE_ITERATOR_NAME&) const;
        friend bool graphdom::graph<VertexType>::EDGE_ITERATOR_NAME::operator!=(const CONSTANT_EDGE_ITERATOR_NAME&) const;
        friend class graphdom::set_graph<VertexType>;
        friend class graphdom::multiset_graph<VertexType>;
        /// \endcond DEV_DOC
    private:
        CONSTANT_EDGE_ITERATOR_NAME(
            const graphdom::graph<VertexType>* edge_set_vertex_graph_owner_ptr,
            const graphdom::graph<VertexType>::vertex_container* edge_begin_point_ptr,
            graphdom::graph<VertexType>::graph_edges_type edge_set_vertex_graph_owner_edges_type,
            const std::array<
                const graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
                2
            >& edge_begin_point_adj_sets_array_ptr,
            graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator
        );
        CONSTANT_EDGE_ITERATOR_NAME(
            const graphdom::graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            const graphdom::graph<VertexType>::vertex_container* edge_begin_point_ptr,
            graphdom::graph<VertexType>::graph_edges_type edge_multiset_vertex_graph_owner_edges_type,
            const std::array<
                const graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
                2
            >& edge_begin_point_adj_sets_array_ptr,
            graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator
        );

        bool is_limited_by_edge_type() const;

        const graphdom::graph<VertexType>* edge_graph_owner;
        const graphdom::graph<VertexType>::vertex_container* edge_vertex_container_owner;
        graphdom::graph<VertexType>::graph_edges_type graph_owner_edges_type;

        using special_begin_end_indicator = std::monostate;

        using real_set_vertex_graph_vertex_container_edge_iterator_type =
            typename graphdom::graph<VertexType>::adj_set<
                const graphdom::graph<VertexType>::vertex_container*
            >::const_iterator;
        using set_vertex_graph_inner_edge_iterator_type =
            std::variant<
                special_begin_end_indicator,
                real_set_vertex_graph_vertex_container_edge_iterator_type
            >;
        using set_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                const graphdom::graph<VertexType>::adj_set<const graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;
        using set_vertex_graph_edge_info =
            std::pair<
                set_vertex_graph_inner_edge_iterator_type,
                set_vertex_graph_vertex_container_adj_sets_ptr_array_type
            >;

        using real_multiset_vertex_graph_vertex_container_edge_iterator_type =
            typename graphdom::graph<VertexType>::adj_set<
                graphdom::graph<VertexType>::vertex_container*
            >::const_iterator;
        using multiset_vertex_graph_inner_edge_iterator_type =
            std::variant<
                special_begin_end_indicator,
                real_multiset_vertex_graph_vertex_container_edge_iterator_type
            >;
        using multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                const graphdom::graph<VertexType>::adj_set<graphdom::graph<VertexType>::vertex_container*>*,
                2
            >;
        using multiset_vertex_graph_edge_info =
            std::pair<
                multiset_vertex_graph_inner_edge_iterator_type,
                multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type
            >;

        std::variant<
            set_vertex_graph_edge_info,
            multiset_vertex_graph_edge_info
        > type_dependent_edge_info;

        graphdom::edge_type current_edge_type;
};

/// Every valid instance of this class can be used to identify a specific [vertex](@ref mathematical_vertex_definition) of a [multiset-vertex graph](@ref MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph) and to access its [core](@ref mathematical_vertex_core_definition) by reference or pointer.
/**
 * An instance `hndl` of this class is invalidated as soon as one of the following scenarios occurs:
 * -# `hndl` is constructed using an invalid instance of this class.
 * -# `hndl` is constructed using an invalid instance of [MAIN_LIBRARY_NAMESPACE::graph< VertexType >::vertex_handle](@ref MAIN_LIBRARY_NAMESPACE::graph::vertex_handle).
 * -# `hndl = other_hndl;` is executed where `other_hndl` is an invalid instance of this class.
 *
 * A valid instance `hndl` of this class is invalidated as soon as the vertex it is associated with is erased.
 *
 * An invalid instance `hndl` of this class is validated as soon as `hndl = other_hndl;` is executed where `other_hndl` is a valid instance of this class.
 *
 * If `*this` is invalid then any operation other than `*this = other;` and the destruction of `*this` will cause undefined behavior.
 */
template <typename VertexType>
class graphdom::multiset_graph<VertexType>::vertex_handle final {
    public:
        vertex_handle() = delete;
        vertex_handle(const vertex_handle&) = default;

        /**
         * If @p other is valid and identifies a vertex of a multiset-vertex graph, then immediately after the construction of `*this` we will have `*this == other`.<br>
         * If @p other is valid but identifies a vertex of a set-vertex graph, then this constructor will throw an instance of a class publicly derived, directly or indirectly, from `std::exception`.<br>
         * If @p other is invalid then `*this` will be invalid immediately after its construction.
         *
         * @param other The object to compare with `*this`.
         * @par Complexity
         * Constant.
         */
        explicit vertex_handle(const typename graphdom::graph<VertexType>::vertex_handle& other);

        /**
         * If `*this` is valid then `*(*this)` returns a non-const reference to the core of the vertex identified by `*this`.<br>
         * If `*this` is invalid then `*(*this)` will cause undefined behavior.
         *
         * @return A const reference to the core of the vertex identified by `*this`.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] VertexType& operator*() const;

        /**
         * If `*this` is valid then the expression `(*this)->...` is equal to `( &( *(*this) ) )->...`.<br>
         * If `*this` is invalid then the expression `(*this)->...` will cause undefined behavior.
         *
         * @return `&( *(*this) )`
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] VertexType* operator->() const;

        /**
         * Returns `true` if `*this` and @p other are valid and identify the same vertex of the same multiset-vertex graph.<br>
         * Returns `false` if `*this` and @p other are valid, identify different vertices, and the vertices identified by `*this` and @p other belong to the same multiset-vertex graph.<br>
         * In other cases, `*this == other` will cause undefined behavior.
         *
         * @param other The object to compare with `*this`.
         * @return The comparison result.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] bool operator==(const typename graphdom::graph<VertexType>::vertex_const_handle& other) const;

        /**
         * `*this != other` has the same behavior of `!( *this == other )`.
         *
         * @param other The object to compare with `*this`
         * @return The same result of `!( *this == other)`.
         * @par Complexity
         * Constant.
         */
        [[nodiscard]] bool operator!=(const typename graphdom::graph<VertexType>::vertex_const_handle& other) const;

        vertex_handle& operator=(const vertex_handle&) = default;

        [[nodiscard]] graphdom::multiset_graph<VertexType>::ADJ_LIST adj_list() const;
        [[nodiscard]] graphdom::multiset_graph<VertexType>::ADJ_LIST adj_list(graphdom::edge_type) const;
        [[nodiscard]] typename graphdom::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const;
        [[nodiscard]] typename graphdom::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(graphdom::edge_type) const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>::vertex_const_handle;
        friend class graphdom::multiset_graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class graphdom::graph<VertexType>::vertex_handle;
        friend class graphdom::multiset_graph<VertexType>;
        friend typename graphdom::graph<VertexType>::vertex_handle graphdom::graph<VertexType>::EDGE_ITERATOR_NAME::operator*() const;
        /// \endcond DEV_DOC
    private:
        vertex_handle(
            const graphdom::multiset_graph<VertexType>*,
            typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
            graphdom::edge_type non_mixed_graph_type
        );
        vertex_handle(
            const graphdom::multiset_graph<VertexType>*,
            typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
        );

        const graphdom::multiset_graph<VertexType>* vertex_owner;
        VertexContainerPointerType multiset_graph_vertex_container;
        typename graphdom::graph<VertexType>::graph_edges_type edges_type;
};

template <typename VertexType>
class graphdom::multiset_graph<VertexType>::ADJ_LIST { //TODO: class implementation
    public:
        ADJ_LIST() = delete;
        ADJ_LIST(const ADJ_LIST&) = default;
        explicit ADJ_LIST(const typename graphdom::graph<VertexType>::ADJ_LIST&);

        [[nodiscard]] graphdom::multiset_graph<VertexType>::EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] graphdom::multiset_graph<VertexType>::EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] typename graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] typename graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>::CONSTANT_ADJ_LIST;
        friend class graphdom::multiset_graph<VertexType>::vertex_handle;
        friend class graphdom::graph<VertexType>::ADJ_LIST;
        /// \endcond DEV_DOC
    private:
        ADJ_LIST(
            const graphdom::multiset_graph<VertexType>* vertex_container_graph_owner_ptr,
            VertexContainerPointerType vertex_container_ptr,
            typename graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type
        );
        ADJ_LIST(
            const graphdom::multiset_graph<VertexType>* vertex_container_graph_owner_ptr,
            VertexContainerPointerType vertex_container_ptr,
            typename graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type,
            graphdom::edge_type edges_type_selected
        );

        const graphdom::multiset_graph<VertexType>* vertex_container_graph_owner;
        typename graphdom::graph<VertexType>::graph_edges_type vertex_container_graph_owner_edges_type;
        VertexContainerPointerType vertex_container_ptr;

        using adj_sets_ptr_array_type =
            std::array<
                typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>*,
                2
            >;

        adj_sets_ptr_array_type adj_sets_array;
};

template <typename VertexType>
class graphdom::multiset_graph<VertexType>::EDGE_ITERATOR_NAME final { //TODO: class implementation
    public:
        EDGE_ITERATOR_NAME() = delete;
        EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&) = default;
        EDGE_ITERATOR_NAME(const typename graphdom::graph<VertexType>::EDGE_ITERATOR_NAME&);

        [[nodiscard]] graphdom::multiset_graph<VertexType>::vertex_handle operator*() const;
        [[nodiscard]] graphdom::multiset_graph<VertexType>::vertex_handle operator->() const;
        [[nodiscard]] bool operator==(const typename graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const;
        [[nodiscard]] bool operator!=(const typename graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const;

        EDGE_ITERATOR_NAME& operator=(const typename graphdom::graph<VertexType>::EDGE_ITERATOR_NAME&);
        EDGE_ITERATOR_NAME& operator++();
        [[nodiscard]] EDGE_ITERATOR_NAME operator++(int);

        [[nodiscard]] graphdom::edge_type edge_type() const;

        /// \cond DEV_DOC
        friend class graphdom::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class graphdom::multiset_graph<VertexType>::ADJ_LIST;
        friend class graphdom::graph<VertexType>::EDGE_ITERATOR_NAME;
        /// \endcond DEV_DOC
    private:
        EDGE_ITERATOR_NAME(
            const graphdom::multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            VertexContainerPointerType edge_begin_point_ptr,
            typename graphdom::graph<VertexType>::graph_edges_type edge_multiset_vertex_graph_owner_edges_type,
            const std::array<
                typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>*,
                2
            >& edge_begin_point_adj_sets_array_ptr,
            typename graphdom::graph<VertexType>::begin_or_end begin_or_end_indicator
        );
        EDGE_ITERATOR_NAME(
            const graphdom::multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            typename graphdom::graph<VertexType>::template non_mixed_graph_vertex_container<
                VertexContainerPointerType
            >* edge_begin_point_ptr,
            graphdom::edge_type edge_multiset_vertex_graph_owner_edges_type,
            typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>::iterator inner_itr
        );
        EDGE_ITERATOR_NAME(
            const graphdom::multiset_graph<VertexType>* edge_multiset_vertex_graph_owner_ptr,
            typename graphdom::graph<VertexType>::template mixed_graph_vertex_container<
                VertexContainerPointerType
            >* edge_begin_point_ptr,
            typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>::iterator inner_itr,
            graphdom::edge_type inner_itr_edge_type,
            bool inner_itr_is_limited_by_edge_type = false
        );

        const graphdom::multiset_graph<VertexType>* edge_owner;
        VertexContainerPointerType edge_vertex_container_owner;
        typename graphdom::graph<VertexType>::graph_edges_type graph_owner_edges_type;

        using special_begin_end_indicator = std::monostate;
        using real_multiset_vertex_graph_vertex_container_edge_iterator_type =
            typename graphdom::graph<VertexType>::template adj_set<
                VertexContainerPointerType
            >::iterator;
        using multiset_vertex_graph_inner_edge_iterator_type =
            std::variant<
                special_begin_end_indicator,
                real_multiset_vertex_graph_vertex_container_edge_iterator_type
            >;
        using multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type =
            std::array<
                typename graphdom::graph<VertexType>::template adj_set<VertexContainerPointerType>*,
                2
            >;

        multiset_vertex_graph_inner_edge_iterator_type inner_edge_iterator;
        multiset_vertex_graph_vertex_container_adj_sets_ptr_array_type vertex_container_adj_sets_ptr_array;
        graphdom::edge_type current_edge_type;
};

#endif //HANDLERS_DECLARATIONS_H