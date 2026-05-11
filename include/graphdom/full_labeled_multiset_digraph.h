#ifndef FULL_LABELED_MULTISET_DIGRAPH_H
#define FULL_LABELED_MULTISET_DIGRAPH_H

#include <forward_list>

#include "graph.h"
#include "labeled_vertex_graph.h"
#include "labeled_vertex_multiset_graph.h"
#include "labeled_edge_graph.h"
#include "labeled_edge_non_mixed_graph.h"

namespace graphdom {
    template<
        typename VertexType,
        typename VertexLabelType,
        typename EdgeLabelType,
        typename T1 = default_vertex_labeller<VertexType,VertexLabelType>, //TODO:: find a better name for T1
        typename T2 = default_edge_labeller<VertexType,EdgeLabelType> // TODO: find a better name for T2
    >
    class full_labeled_multiset_digraph final :
        virtual public labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>,
        virtual public labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2> {
            public:
                full_labeled_multiset_digraph();
                full_labeled_multiset_digraph(const T1& v_lab, const T2& e_lab);
                explicit full_labeled_multiset_digraph(const T1& v_lab, T2&& e_lab = T2());
                full_labeled_multiset_digraph(T1&& v_lab, const T2& e_lab);
                explicit full_labeled_multiset_digraph(T1&& v_lab, T2&& e_lab = T2());

                ~full_labeled_multiset_digraph() override;

                [[nodiscard]] std::size_t order() const override;
                [[nodiscard]] const VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) const override;
                [[nodiscard]] const EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const override;

                void erase_vertex(const typename graphdom::graph<VertexType>::vertex_const_handle&) override; //TODO: look out to memory leaks in ADJ
                [[nodiscard]] typename graphdom::graph<VertexType>::EDGE_ITERATOR_NAME erase_edge(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override; //TODO: look out to memory leaks in ADJ
                [[nodiscard]] VertexLabelType& get_vertex_label(const typename graph<VertexType>::vertex_const_handle&) override;
                using graphdom::multiset_graph<VertexType>::insert_vertex;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(const VertexType&, const VertexLabelType&) override;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(const VertexType&, VertexLabelType&&) override;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(VertexType&&, const VertexLabelType&) override;
                [[nodiscard]] typename multiset_graph<VertexType>::vertex_handle insert_vertex(VertexType&&, VertexLabelType&&) override;
                [[nodiscard]] EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override;
                using graphdom::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>::insert_edge;
                void insert_edge(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, const EdgeLabelType&) override;
                void insert_edge(const typename graph<VertexType>::vertex_const_handle&, const typename graph<VertexType>::vertex_const_handle&, EdgeLabelType&&) override;
            private:
                using VertexContainerPointerType = typename graphdom::multiset_graph<VertexType>::VertexContainerPointerType;
                using edge_endpoint = typename graphdom::multiset_graph<VertexType>::template labeled_directed_edge_endpoint<VertexLabelType>;
                using vertex_container = typename graphdom::multiset_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<EdgeLabelType>;

                static void safe_edge_endpoint_deallocation(typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>*);

                std::forward_list<vertex_container> vertices;
                std::size_t number_of_vertices_inserted;
    };
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>//TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_digraph() :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>//TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_digraph(const T1& v_lab, const T2& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_digraph(const T1& v_lab, T2&& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_digraph(T1&& v_lab, const T2& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
full_labeled_multiset_digraph(T1&& v_lab, T2&& e_lab) :
labeled_vertex_multiset_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
number_of_vertices_inserted(0) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::~full_labeled_multiset_digraph() {
    while ( ! vertices.empty() ) {
        auto& vertex_to_erase = vertices.front();
        auto& vertex_to_erase_adj = vertex_to_erase.adj;
        for (auto edge_endpoint_to_deallocate = vertex_to_erase_adj.begin();
            edge_endpoint_to_deallocate != vertex_to_erase_adj.end();
            ++edge_endpoint_to_deallocate) {
            safe_edge_endpoint_deallocation(*edge_endpoint_to_deallocate); // This is to avoid memory leaks
        }
        vertices.pop_front();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
std::size_t graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::order() const {
    return number_of_vertices_inserted;
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
const VertexLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle&) const {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
const EdgeLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_edge_label(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::erase_vertex(
    const typename graphdom::graph<VertexType>::vertex_const_handle& const_vertex_ptr_to_erase_reference) {
    if( graphdom::graph<VertexType>::get_owner_graph(const_vertex_ptr_to_erase_reference) == this ) {
        const auto vertex_container_to_erase_ptr = graphdom::graph<VertexType>::get_vertex_container(const_vertex_ptr_to_erase_reference);
        if ( vertex_container_to_erase_ptr != nullptr ) {
            auto before_vertex_container_to_erase_found_vertices_itr = vertices.end();
            for(auto vertices_itr = vertices.before_begin(); vertices_itr != vertices.end(); ++vertices_itr) {
                auto vertices_itr_next = std::next(vertices_itr);
                if( vertices_itr_next != vertices.end() ){
                    if( (&(*vertices_itr_next)) == vertex_container_to_erase_ptr ){
                        before_vertex_container_to_erase_found_vertices_itr = vertices_itr;
                    }
                    auto& vertices_itr_next_vertex_container = *vertices_itr_next;
                    auto& vertices_itr_next_vertex_container_adj = vertices_itr_next_vertex_container.adj;
                    auto vertices_itr_next_vertex_container_adj_found_result_itr = vertices_itr_next_vertex_container_adj.find(vertex_container_to_erase_ptr);
                    if ( vertices_itr_next_vertex_container_adj_found_result_itr != vertices_itr_next_vertex_container_adj.end() ) {
                        safe_edge_endpoint_deallocation(*vertices_itr_next_vertex_container_adj_found_result_itr); // This is to avoid memory leaks
                        vertices_itr_next_vertex_container_adj.erase(vertices_itr_next_vertex_container_adj_found_result_itr);
                    }
                }
            }
            if ( before_vertex_container_to_erase_found_vertices_itr != vertices.end() ) {
                const auto& vertex_container_to_erase_forward_list_iterator = std::next( before_vertex_container_to_erase_found_vertices_itr );
                auto& adj_to_erase = (*vertex_container_to_erase_forward_list_iterator).adj;
                for (auto adj_to_erase_itr = adj_to_erase.begin(); adj_to_erase_itr != adj_to_erase.end(); ++adj_to_erase_itr) {
                    safe_edge_endpoint_deallocation(*adj_to_erase_itr); // This is to avoid memory leaks
                }
                vertices.erase_after(before_vertex_container_to_erase_found_vertices_itr);
                --number_of_vertices_inserted;
            }
            //TODO:: Evaluate a possible exception throw HERE
        }
        //TODO:: Evaluate a possible exception throw HERE
    }
    //TODO:: Evaluate a possible exception throw HERE
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
typename graphdom::graph<VertexType>::EDGE_ITERATOR_NAME
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType, EdgeLabelType, T1, T2>::erase_edge(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& edge_itr) {
    if ( graphdom::graph<VertexType>::get_owner_graph(edge_itr) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const edge_itr_begin_point = const_cast<vertex_container*>( static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_begin_point(edge_itr) ) );
    auto edge_itr_inner_iterator = graphdom::multiset_graph<VertexType>::get_inner_iterator( edge_itr );
    auto const edge_itr_endpoint = *edge_itr_inner_iterator;
    safe_edge_endpoint_deallocation(edge_itr_endpoint);
    return graphdom::multiset_graph<VertexType>::edge_iterator_factory(
        this,
        edge_itr_begin_point,
        directed,
        ( edge_itr_begin_point->adj ).erase( edge_itr_inner_iterator )
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
VertexLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::vertex_const_handle&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
    const VertexType& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    vertices.emplace_front(
        vertex_to_insert,
        vertex_label_to_insert
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_ptr_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
const VertexType& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    vertices.emplace_front(
        vertex_to_insert,
        std::move(vertex_label_to_insert)
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_ptr_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    vertices.emplace_front(
        std::move(vertex_to_insert),
        vertex_label_to_insert
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_ptr_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2> //TODO:: find a better name for T1 and T2
typename graphdom::multiset_graph<VertexType>::vertex_handle
graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    vertices.emplace_front(
        std::move(vertex_to_insert),
        std::move(vertex_label_to_insert)
    );
    ++number_of_vertices_inserted;
    return graphdom::multiset_graph<VertexType>::vertex_ptr_factory(
        this,
        vertices.front(),
        graphdom::edge_type::directed
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
EdgeLabelType& graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::get_edge_label(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& begin_point_vertex_ptr,
    const typename graph<VertexType>::vertex_const_handle& end_point_vertex_ptr,
    const EdgeLabelType& edge_label_to_insert) {
    if (
        graphdom::graph<VertexType>::get_owner_graph( begin_point_vertex_ptr ) != this ||
        graphdom::graph<VertexType>::get_owner_graph( end_point_vertex_ptr ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( begin_point_vertex_ptr ) );
    auto const end_point_vertex_container = const_cast< typename graphdom::graph<VertexType>::vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( end_point_vertex_ptr ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert( new edge_endpoint( end_point_vertex_container , edge_label_to_insert ) );
    const auto inner_insertion_result = ( ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert.get() ) ).second;
    if ( inner_insertion_result ) {
        edge_endpoint_to_insert.release();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::insert_edge(
    const typename graph<VertexType>::vertex_const_handle& begin_point_vertex_ptr,
    const typename graph<VertexType>::vertex_const_handle& end_point_vertex_ptr,
    EdgeLabelType&& edge_label_to_insert) {
        if (
            graphdom::graph<VertexType>::get_owner_graph( begin_point_vertex_ptr ) != this ||
            graphdom::graph<VertexType>::get_owner_graph( end_point_vertex_ptr ) != this
        ) {
            throw std::runtime_error("Error"); //TODO: write a better message
        }
        auto const begin_point_vertex_container = static_cast< const vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( begin_point_vertex_ptr ) );
        auto const end_point_vertex_container = const_cast< typename graphdom::graph<VertexType>::vertex_container* >( graphdom::graph<VertexType>::get_vertex_container( end_point_vertex_ptr ) );
        if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
            throw std::runtime_error("Error"); //TODO: write a better message
        }
        const auto lower_bound = ( begin_point_vertex_container->adj ).lower_bound( end_point_vertex_container );
        if ( lower_bound == ( begin_point_vertex_container->adj ).cend()  ) {
            ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
        }
        else {
            if ( ( ( begin_point_vertex_container->adj ).key_comp() )( end_point_vertex_container, *lower_bound ) ) {
                ( begin_point_vertex_container->adj ).emplace_hint( lower_bound, new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
            }
        }
        /*
        std::unique_ptr< edge_endpoint > edge_endpoint_to_insert( new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
        const auto inner_insertion_result = ( ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert.get() ) ).second;
        if ( inner_insertion_result ) {
            edge_endpoint_to_insert.release();
        }
        */
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename T1, typename T2>
void graphdom::full_labeled_multiset_digraph<VertexType,VertexLabelType,EdgeLabelType,T1,T2>::
safe_edge_endpoint_deallocation(
    typename graphdom::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>* ee_ptr) {
    delete static_cast< edge_endpoint* >( ee_ptr );
}

#endif //FULL_LABELED_MULTISET_DIGRAPH_H