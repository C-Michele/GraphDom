#ifndef FULL_LABELED_SET_VERTEX_UGRAPH_H
#define FULL_LABELED_SET_VERTEX_UGRAPH_H

#include <set>

#include "graph.h"
#include "labeled_vertex_graph.h"
#include "labeled_vertex_set_vertex_graph.h"
#include "labeled_edge_graph.h"
#include "labeled_edge_non_mixed_graph.h"

namespace MAIN_LIBRARY_NAMESPACE {
    template<
        typename VertexType,
        typename VertexLabelType,
        typename EdgeLabelType,
        typename Compare = std::less<VertexType>,
        typename T1 = DefaultVertexLabellerType<VertexType,VertexLabelType>, //TODO:: find a better name for T1
        typename T2 = DefaultEdgeLabellerType<VertexType,EdgeLabelType> // TODO: find a better name for T2
    >
    class full_labeled_set_vertex_ugraph final :
    virtual public labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>,
    virtual public labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2> {
        public:
            full_labeled_set_vertex_ugraph() = default;
            full_labeled_set_vertex_ugraph(const Compare& v_comp, const T1& v_lab, const T2& e_lab);
            full_labeled_set_vertex_ugraph(const Compare& v_comp, const T1& v_lab, T2&& e_lab = T2());
            full_labeled_set_vertex_ugraph(const Compare& v_comp, T1&& v_lab, const T2& e_lab);
            explicit full_labeled_set_vertex_ugraph(const Compare& v_comp, T1&& v_lab = T1(), T2&& e_lab = T2());
            full_labeled_set_vertex_ugraph(Compare&& v_comp, const T1& v_lab, const T2& e_lab);
            full_labeled_set_vertex_ugraph(Compare&& v_comp, const T1& v_lab, T2&& e_lab = T2());
            full_labeled_set_vertex_ugraph(Compare&& v_comp, T1&& v_lab, const T2& e_lab);
            explicit full_labeled_set_vertex_ugraph(Compare&& v_comp, T1&& v_lab = T1(), T2&& e_lab = T2());

            ~full_labeled_set_vertex_ugraph() override;

            [[nodiscard]] std::size_t order() const override;
            [[nodiscard]] const VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const override;
            [[nodiscard]] const EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const override;

            void erase_vertex(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) override; //TODO: look out to memory leaks in ADJ
            [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME erase_edge(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override; //TODO: look out to memory leaks in ADJ
            [[nodiscard]] VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) override;
            using MAIN_LIBRARY_NAMESPACE::labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>::insert_vertex;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&, const VertexLabelType&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(const VertexType&, VertexLabelType&&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&, const VertexLabelType&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::vertex_handle,bool> insert_vertex(VertexType&&, VertexLabelType&&) override;
            [[nodiscard]] EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override;
            using MAIN_LIBRARY_NAMESPACE::labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>::insert_edge;
            void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const EdgeLabelType&) override;
            void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, EdgeLabelType&&) override;
        private:
            using VertexContainerPointerType = typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::VertexContainerPointerType;
            using edge_endpoint = typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::template labeled_undirected_edge_endpoint<VertexLabelType>;
            using adj_set = typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::adj_set;
            using vertex_container = typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<EdgeLabelType>;

            static void safe_edge_endpoint_deallocation(typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>*);

            class custom_set_less {
                public:
                    custom_set_less() = default;
                    explicit custom_set_less(const Compare& comp) : external_vertex_less_functor(comp){}
                    explicit custom_set_less(Compare&& comp) : external_vertex_less_functor(std::move(comp)){}

                    bool operator()(
                        const vertex_container& left,
                        const vertex_container& right ) const {
                        return external_vertex_less_functor(left.vertex,right.vertex);
                    }

                    using is_transparent = void;

                    bool operator()(
                        const vertex_container& left,
                        const VertexType& right ) const {
                        return external_vertex_less_functor(left.vertex,right);
                    }

                    bool operator()(
                        const VertexType& left,
                        const vertex_container& right ) const {
                        return external_vertex_less_functor(left,right);
                    }
                private:
                    Compare external_vertex_less_functor;
            };

            std::set<
                vertex_container,
                custom_set_less
            > vertices;
    };
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(const Compare& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(const Compare& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(const Compare& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(const Compare& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(Compare&& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(Compare&& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(Compare&& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_ugraph(Compare&& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
~full_labeled_set_vertex_ugraph() {
    for (auto ugraph_vertices_itr = vertices.begin(); ugraph_vertices_itr != vertices.end(); ++ugraph_vertices_itr) {
        auto& ugv_itr_vertex_container = *ugraph_vertices_itr;
        auto& ugv_itr_vc_adj = ugv_itr_vertex_container.adj;
        for (auto edge_endpoint_to_deallocate = ugv_itr_vc_adj.begin(); edge_endpoint_to_deallocate != ugv_itr_vc_adj.end(); ++edge_endpoint_to_deallocate) {
            safe_edge_endpoint_deallocation(*edge_endpoint_to_deallocate); // This is to avoid memory leaks
        }
        ugv_itr_vc_adj.clear();
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::size_t MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::order() const {
    return vertices.size();
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const VertexLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const EdgeLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_vertex(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& const_vertex_ptr) {
    if ( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph(const_vertex_ptr) == this ) {
        const auto* const vertex_container_to_erase_ptr =
            static_cast< const vertex_container* >( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container(const_vertex_ptr) );
        if ( vertex_container_to_erase_ptr != nullptr ) {
            const auto vertex_container_to_erase_found_vertices_itr = vertices.find( *vertex_container_to_erase_ptr );
            auto& vertex_container_to_erase_adj = ( *vertex_container_to_erase_found_vertices_itr ).adj;
            for (auto vertex_container_to_erase_adj_itr = vertex_container_to_erase_adj.begin();
                vertex_container_to_erase_adj_itr != vertex_container_to_erase_adj.end();
                ++vertex_container_to_erase_adj_itr) {
                const auto& edge_endpoint_vertex_container =
                    *(
                        static_cast< const vertex_container* >(
                            (
                                *(
                                    *(
                                        vertex_container_to_erase_adj_itr
                                    )
                                )
                            ).vertex_container_ptr
                        )
                    );
                if ( ( &edge_endpoint_vertex_container ) != vertex_container_to_erase_ptr ) { //The edge could be a loop
                    auto& edge_endpoint_vertex_container_adj = edge_endpoint_vertex_container.adj;
                    const auto vertex_container_to_erase_founded_in_edge_endpoint_vertex_container_adj =
                        edge_endpoint_vertex_container_adj.find( vertex_container_to_erase_ptr );
                    safe_edge_endpoint_deallocation( *vertex_container_to_erase_founded_in_edge_endpoint_vertex_container_adj );
                    edge_endpoint_vertex_container_adj.erase( vertex_container_to_erase_founded_in_edge_endpoint_vertex_container_adj );
                }
                safe_edge_endpoint_deallocation( *vertex_container_to_erase_adj_itr );
            }
            vertices.erase(vertex_container_to_erase_found_vertices_itr);
        }
        //TODO:: Evaluate a possible exception throw HERE
    }
    //TODO:: Evaluate a possible exception throw HERE
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_edge(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME& edge_itr) {
    if ( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph(edge_itr) != this ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const edge_itr_begin_point = static_cast< const vertex_container* >( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_begin_point( edge_itr ) );
    auto inner_iterator_of_begin_point_adj = MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::get_inner_iterator( edge_itr );
    auto const edge_itr_endpoint = static_cast< const vertex_container* >( ( *( *inner_iterator_of_begin_point_adj ) ).vertex_container_ptr );
    if ( edge_itr_begin_point != edge_itr_endpoint ) { //The edge could be a loop
        auto inner_iterator_of_end_point_adj = ( (*edge_itr_endpoint).adj ).find( edge_itr_begin_point );
        safe_edge_endpoint_deallocation(*inner_iterator_of_end_point_adj);
        ( (*edge_itr_endpoint).adj ).erase( inner_iterator_of_end_point_adj );
    }
    safe_edge_endpoint_deallocation(*inner_iterator_of_begin_point_adj);
    return MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::edge_iterator_factory(
        this,
        edge_itr_begin_point,
        undirected,
        ( (*edge_itr_begin_point).adj ).erase( inner_iterator_of_begin_point_adj )
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
VertexLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle,bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
    const VertexType& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        vertex_to_insert,
        vertex_label_to_insert
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::undirected
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle,bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
    const VertexType& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        vertex_to_insert,
        std::move(vertex_label_to_insert)
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::undirected
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle,bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
    VertexType&& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        std::move(vertex_to_insert),
        vertex_label_to_insert
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::undirected
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle,bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
    VertexType&& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        std::move(vertex_to_insert),
        std::move(vertex_label_to_insert)
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_handle, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::undirected
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
EdgeLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& begin_point_vertex_ptr,
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& end_point_vertex_ptr,
    const EdgeLabelType& edge_label_to_insert) {
    if (
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph( begin_point_vertex_ptr ) != this ||
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph( end_point_vertex_ptr ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = static_cast< const vertex_container* >( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container( begin_point_vertex_ptr ) );
    auto const end_point_vertex_container = static_cast< const vertex_container* >( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container( end_point_vertex_ptr ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_begin_point_adj( new edge_endpoint( end_point_vertex_container , edge_label_to_insert ) );
    const auto inner_insertion_result_in_begin_point_adj = ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_begin_point_adj.get() );
    if ( inner_insertion_result_in_begin_point_adj.second ) {
        edge_endpoint_to_insert_in_begin_point_adj.release();
        if ( begin_point_vertex_container != end_point_vertex_container ) { //The edge could be a loop
            std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_end_point_adj(
                new edge_endpoint(
                    begin_point_vertex_container ,
                    ( static_cast< edge_endpoint* >( *( inner_insertion_result_in_begin_point_adj.first ) ) )->edge_label_ptr
                )
            );
            const auto inner_insertion_result_in_end_point_adj = ( ( end_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_end_point_adj.get() ) ).second;
            if ( inner_insertion_result_in_end_point_adj ) {
                edge_endpoint_to_insert_in_end_point_adj.release();
            }
            else {
                safe_edge_endpoint_deallocation( *( inner_insertion_result_in_begin_point_adj.first ) );
                ( begin_point_vertex_container->adj ).erase( inner_insertion_result_in_begin_point_adj.first );
            }
        }
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& begin_point_vertex_ptr,
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& end_point_vertex_ptr,
    EdgeLabelType&& edge_label_to_insert) {
    if (
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph( begin_point_vertex_ptr ) != this ||
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_owner_graph( end_point_vertex_ptr ) != this
    ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    auto const begin_point_vertex_container = static_cast< const vertex_container* >( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container( begin_point_vertex_ptr ) );
    auto const end_point_vertex_container = static_cast< const vertex_container* >( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container( end_point_vertex_ptr ) );
    if ( begin_point_vertex_container == nullptr || end_point_vertex_container == nullptr ) {
        throw std::runtime_error("Error"); //TODO: write a better message
    }
    std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_begin_point_adj( new edge_endpoint( end_point_vertex_container , std::move(edge_label_to_insert) ) );
    const auto inner_insertion_result_in_begin_point_adj = ( begin_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_begin_point_adj.get() );
    if ( inner_insertion_result_in_begin_point_adj.second ) {
        edge_endpoint_to_insert_in_begin_point_adj.release();
        if ( begin_point_vertex_container != end_point_vertex_container ) { //The edge could be a loop
            std::unique_ptr< edge_endpoint > edge_endpoint_to_insert_in_end_point_adj(
                new edge_endpoint(
                    begin_point_vertex_container ,
                    ( static_cast< edge_endpoint* >( *( inner_insertion_result_in_begin_point_adj.first ) ) )->edge_label_ptr
                )
            );
            const auto inner_insertion_result_in_end_point_adj = ( ( end_point_vertex_container->adj ).insert( edge_endpoint_to_insert_in_end_point_adj.get() ) ).second;
            if ( inner_insertion_result_in_end_point_adj ) {
                edge_endpoint_to_insert_in_end_point_adj.release();
            }
            else {
                safe_edge_endpoint_deallocation( *( inner_insertion_result_in_begin_point_adj.first ) );
                ( begin_point_vertex_container->adj ).erase( inner_insertion_result_in_begin_point_adj.first );
            }
        }
    }
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_ugraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
safe_edge_endpoint_deallocation(
    typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template edge_endpoint<VertexContainerPointerType>* ee_ptr) {
    delete static_cast<edge_endpoint*>(ee_ptr);
}

//TODO: continue class implementation

#endif //FULL_LABELED_SET_VERTEX_UGRAPH_H
