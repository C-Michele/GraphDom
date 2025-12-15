#ifndef HANDLERS_DECLARATIONS_H
#define HANDLERS_DECLARATIONS_H

#include "graph.h"

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME final {
    public:
        VERTEX_PTR_NAME() = delete;
        VERTEX_PTR_NAME(const VERTEX_PTR_NAME&) = default;
        VERTEX_PTR_NAME(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME&);

        explicit operator typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME() const;
        [[nodiscard]] const VertexType& operator*() const;
        [[nodiscard]] const VertexType* operator->() const;
        [[nodiscard]] bool operator==(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;
        [[nodiscard]] bool operator!=(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;

        VERTEX_PTR_NAME& operator=(const VERTEX_PTR_NAME&) = default;

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list() const; //TODO: implementation
        //template <typename Compare>
        // [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list(Compare comp) const; //TODO: implementation
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const; //TODO: implementation
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(Compare comp) const; //TODO: implementation
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const; //TODO: implementation

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>;
    private:
        VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
            MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
        );
        VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* vertex_owner;
        std::variant<
            std::monostate,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
        > vertex_container_ptr;
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type edges_type;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME final {
    public:
        CONSTANT_VERTEX_PTR_NAME() = delete;
        CONSTANT_VERTEX_PTR_NAME(const CONSTANT_VERTEX_PTR_NAME&) = default;
        CONSTANT_VERTEX_PTR_NAME(const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME&);
        CONSTANT_VERTEX_PTR_NAME(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME&);

        [[nodiscard]] const VertexType& operator*() const;
        [[nodiscard]] const VertexType* operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_VERTEX_PTR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_VERTEX_PTR_NAME&) const;

        CONSTANT_VERTEX_PTR_NAME& operator=(const CONSTANT_VERTEX_PTR_NAME&) = default;

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list() const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(Compare comp) const; //TODO: implementation
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const; //TODO: implementation
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(Compare comp) const; //TODO: implementation
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const; //TODO: implementation

        friend bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator==(const CONSTANT_VERTEX_PTR_NAME&) const;
        friend bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME::operator!=(const CONSTANT_VERTEX_PTR_NAME&) const;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>;
    private:
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<const vertex_container*>&,
            MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
        );
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<const vertex_container*>&
        );
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::non_mixed_graph_vertex_container<vertex_container*>&,
            MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
        );
        CONSTANT_VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::mixed_graph_vertex_container<vertex_container*>&
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* vertex_owner;
        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* graph_vertex_container;
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type edges_type;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST { //TODO: class implementation
    public:
        ADJ_LIST() = delete;
        ADJ_LIST(const ADJ_LIST&) = default;
        ADJ_LIST(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST;
    private:
        ADJ_LIST(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const std::variant<
                std::monostate,
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*
            >&,
            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* vertex_owner;

        std::variant<
            std::pair<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >,
            std::pair<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >
        > vertex_info;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST { //TODO: class implementation
    public:
        CONSTANT_ADJ_LIST() = delete;
        CONSTANT_ADJ_LIST(const CONSTANT_ADJ_LIST&) = default;
        CONSTANT_ADJ_LIST(const ADJ_LIST&);
        CONSTANT_ADJ_LIST(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME;
    private:
        CONSTANT_ADJ_LIST(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* vertex_owner;
        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* vertex_container;

        std::variant<
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >,
            std::array<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >
        > vertex_info;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME final { //TODO: class implementation
    public:
        EDGE_ITERATOR_NAME() = delete;
        EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&) = default;
        EDGE_ITERATOR_NAME(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME operator*() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_EDGE_ITERATOR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_EDGE_ITERATOR_NAME&) const;

        EDGE_ITERATOR_NAME& operator=(const EDGE_ITERATOR_NAME&) = default;
        EDGE_ITERATOR_NAME& operator++();
        [[nodiscard]] EDGE_ITERATOR_NAME operator++(int);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::edge_type edge_type() const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME;
    private:
        EDGE_ITERATOR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator,
            const std::array<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >&,
            MAIN_LIBRARY_NAMESPACE::edge_type
        );
        EDGE_ITERATOR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator,
            const std::array<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >&,
            MAIN_LIBRARY_NAMESPACE::edge_type
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* edge_owner;

        using set_vertex_graph_edge_info =
            std::tuple<
                const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >;

        using multiset_vertex_graph_edge_info =
            std::tuple<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::iterator,
                std::array<
                    MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >;

        std::variant<
            set_vertex_graph_edge_info,
            multiset_vertex_graph_edge_info
        > type_dependent_edge_info;

        MAIN_LIBRARY_NAMESPACE::edge_type current_edge_type;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME final { //TODO: class implementation
    public:
        CONSTANT_EDGE_ITERATOR_NAME() = delete;
        CONSTANT_EDGE_ITERATOR_NAME(const CONSTANT_EDGE_ITERATOR_NAME&) = default;
        CONSTANT_EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&);
        CONSTANT_EDGE_ITERATOR_NAME(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME operator*() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME operator->() const;
        [[nodiscard]] bool operator==(const CONSTANT_EDGE_ITERATOR_NAME&) const;
        [[nodiscard]] bool operator!=(const CONSTANT_EDGE_ITERATOR_NAME&) const;

        CONSTANT_EDGE_ITERATOR_NAME& operator=(const CONSTANT_EDGE_ITERATOR_NAME&) = default;
        CONSTANT_EDGE_ITERATOR_NAME& operator++();
        [[nodiscard]] CONSTANT_EDGE_ITERATOR_NAME operator++(int);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::edge_type edge_type() const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST;
        friend bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME::operator==(const EDGE_ITERATOR_NAME&) const;
        friend bool MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME::operator!=(const EDGE_ITERATOR_NAME&) const;
    private:
        CONSTANT_EDGE_ITERATOR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::const_iterator,
            const std::array<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >&,
            MAIN_LIBRARY_NAMESPACE::edge_type
        );
        CONSTANT_EDGE_ITERATOR_NAME(
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>*,
            const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::const_iterator,
            const std::array<
                MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                2
            >&,
            MAIN_LIBRARY_NAMESPACE::edge_type
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* edge_graph_owner;
        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* edge_vertex_container_owner;

        using set_vertex_graph_edge_info =
            std::pair<
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::const_iterator,
                std::array<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >;

        using multiset_vertex_graph_edge_info =
            std::pair<
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>::const_iterator,
                std::array<
                    const MAIN_LIBRARY_NAMESPACE::graph<VertexType>::adj_set<MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container*>*,
                    2
                >
            >;

        std::variant<
            set_vertex_graph_edge_info,
            multiset_vertex_graph_edge_info
        > type_dependent_edge_info;

        MAIN_LIBRARY_NAMESPACE::edge_type current_edge_type;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME final {
    public:
        VERTEX_PTR_NAME() = delete;
        VERTEX_PTR_NAME(const VERTEX_PTR_NAME&) = default;
        explicit VERTEX_PTR_NAME(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME&);

        [[nodiscard]] VertexType& operator*() const;
        [[nodiscard]] VertexType* operator->() const;
        [[nodiscard]] bool operator==(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;
        [[nodiscard]] bool operator!=(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const;

        VERTEX_PTR_NAME& operator=(const VERTEX_PTR_NAME&) = default;

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list() const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list(Compare comp) const; //TODO: implementation
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const; //TODO: implementation
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list() const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(Compare comp) const; //TODO: implementation
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type) const; //TODO: implementation
        //template <typename Compare>
        //[[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type, Compare comp) const; //TODO: implementation

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>;
    private:
        VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template non_mixed_graph_vertex_container<VertexContainerPointerType>&,
            MAIN_LIBRARY_NAMESPACE::edge_type non_mixed_graph_type
        );
        VERTEX_PTR_NAME(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template mixed_graph_vertex_container<VertexContainerPointerType>&
        );

        const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>* vertex_owner;
        VertexContainerPointerType multiset_graph_vertex_container;
        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type edges_type;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST { //TODO: class implementation
    public:
        ADJ_LIST() = delete;
        ADJ_LIST(const ADJ_LIST&) = default;
        explicit ADJ_LIST(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME begin() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME end() const;
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cbegin() const;
        [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME cend() const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_ADJ_LIST;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::ADJ_LIST;
    private:
        ADJ_LIST(
            const MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>*,
            VertexContainerPointerType,
            typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::graph_edges_type
        );

        const MAIN_LIBRARY_NAMESPACE::graph<VertexType>* vertex_owner;
        typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_container* multiset_graph_vertex_container;
        std::array<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template adj_set<VertexContainerPointerType>*,2> adj_sets_array;
};

template <typename VertexType>
class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::EDGE_ITERATOR_NAME final { //TODO: class implementation
    public:
        EDGE_ITERATOR_NAME() = delete;
        EDGE_ITERATOR_NAME(const EDGE_ITERATOR_NAME&);
        explicit EDGE_ITERATOR_NAME(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME&);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME operator*() const;
        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::VERTEX_PTR_NAME operator->() const;
        [[nodiscard]] bool operator==(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const;
        [[nodiscard]] bool operator!=(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const;

        EDGE_ITERATOR_NAME& operator=(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME&);
        EDGE_ITERATOR_NAME& operator++();
        [[nodiscard]] EDGE_ITERATOR_NAME operator++(int);

        [[nodiscard]] MAIN_LIBRARY_NAMESPACE::edge_type edge_type() const;

        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME;
        friend class MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>::ADJ_LIST;
        friend class MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME;
};

#endif //HANDLERS_DECLARATIONS_H