#ifndef FULL_LABELED_SET_VERTEX_DIGRAPH_H
#define FULL_LABELED_SET_VERTEX_DIGRAPH_H

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
    class full_labeled_set_vertex_digraph final :
    virtual public labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>,
    virtual public labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2> {
        public:
            full_labeled_set_vertex_digraph() = default;
            full_labeled_set_vertex_digraph(const Compare& v_comp, const T1& v_lab, const T2& e_lab);
            full_labeled_set_vertex_digraph(const Compare& v_comp, const T1& v_lab, T2&& e_lab = T2());
            full_labeled_set_vertex_digraph(const Compare& v_comp, T1&& v_lab, const T2& e_lab);
            explicit full_labeled_set_vertex_digraph(const Compare& v_comp, T1&& v_lab = T1(), T2&& e_lab = T2());
            full_labeled_set_vertex_digraph(Compare&& v_comp, const T1& v_lab, const T2& e_lab);
            full_labeled_set_vertex_digraph(Compare&& v_comp, const T1& v_lab, T2&& e_lab = T2());
            full_labeled_set_vertex_digraph(Compare&& v_comp, T1&& v_lab, const T2& e_lab);
            explicit full_labeled_set_vertex_digraph(Compare&& v_comp, T1&& v_lab = T1(), T2&& e_lab = T2());

            ~full_labeled_set_vertex_digraph() override; //TODO: look out to memory leaks in ADJs

            [[nodiscard]] std::size_t order() const override;
            [[nodiscard]] const VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) const override;
            [[nodiscard]] const EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) const override;

            void erase_vertex(const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) override; //TODO: look out to memory leaks in ADJ
            [[nodiscard]] typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME erase_edge(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override; //TODO: look out to memory leaks in ADJ
            [[nodiscard]] VertexLabelType& get_vertex_label(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) override;
            using MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::insert_vertex;
            [[nodiscard]] std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(const VertexType&, const VertexLabelType&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(const VertexType&, VertexLabelType&&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(VertexType&&, const VertexLabelType&) override;
            [[nodiscard]] std::pair<typename graph<VertexType>::VERTEX_PTR_NAME,bool> insert_vertex(VertexType&&, VertexLabelType&&) override;
            [[nodiscard]] EdgeLabelType& get_edge_label(const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) override;
            void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const EdgeLabelType&) override;
            void insert_edge(const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&, EdgeLabelType&&) override;
        private:
            class custom_set_less {
                public:
                    custom_set_less() = default;
                    explicit custom_set_less(const Compare& comp) : external_vertex_less_functor(comp){}
                    explicit custom_set_less(Compare&& comp) : external_vertex_less_functor(std::move(comp)){}

                    bool operator()(
                        const typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<EdgeLabelType>& left,
                        const typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<EdgeLabelType>& right ) const {
                        return external_vertex_less_functor(left.vertex,right.vertex);
                    }
                private:
                    Compare external_vertex_less_functor;
            };

            std::set<
                typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::template non_mixed_graph_labeled_vertex_container<EdgeLabelType>,
                custom_set_less
            > vertices;
    };
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(const Compare& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(const Compare& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(const Compare& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(const Compare& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(v_comp) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(Compare&& v_comp, const T1& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(Compare&& v_comp, const T1& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(v_lab),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(Compare&& v_comp, T1&& v_lab, const T2& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(e_lab),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::
full_labeled_set_vertex_digraph(Compare&& v_comp, T1&& v_lab, T2&& e_lab) :
labeled_vertex_set_vertex_graph<VertexType,VertexLabelType,T1>(std::move(v_lab)),
labeled_edge_non_mixed_graph<VertexType,EdgeLabelType,T2>(std::move(e_lab)),
vertices( custom_set_less(std::move(v_comp)) ) {}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::~full_labeled_set_vertex_digraph() {
    //TODO: real implementation, look out to memory leaks in ADJs
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::size_t MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::order() const {
    return vertices.size();
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const VertexLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& const_vertex_ptr) const {
    //TODO: real implementation, look out to memory leaks in ADJs
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
const EdgeLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME &) const {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_vertex(
    const typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::CONSTANT_VERTEX_PTR_NAME& const_vertex_ptr) {
    if ( MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_ptr_owner(const_vertex_ptr) == this ) {
        const auto vertex_container_to_erase_ptr = MAIN_LIBRARY_NAMESPACE::graph<VertexType>::get_vertex_container(const_vertex_ptr);
        if ( vertex_container_to_erase_ptr != nullptr ) {
            auto vertex_container_to_erase_found_vertices_itr = vertices.end();
            for (auto digraph_vertices_itr = vertices.begin(); digraph_vertices_itr != vertices.end(); ++digraph_vertices_itr) {
                auto& digraph_vertices_itr_vertex_container = *digraph_vertices_itr;
                if ( &digraph_vertices_itr_vertex_container == vertex_container_to_erase_ptr ) {
                    vertex_container_to_erase_found_vertices_itr = digraph_vertices_itr;
                }
                auto& digraph_vertices_itr_vertex_container_adj = digraph_vertices_itr_vertex_container.adj;
                typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template edge_endpoint<typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::VertexContainerPointerType>
                edge_endpoint_bait(vertex_container_to_erase_ptr);
                auto itr_vertex_container_adj_found_result_itr = digraph_vertices_itr_vertex_container_adj.find(&edge_endpoint_bait);
                if (itr_vertex_container_adj_found_result_itr != digraph_vertices_itr_vertex_container_adj.end()) {
                    auto edge_endpoint_to_erase_ptr =
                        static_cast<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_directed_edge_endpoint<typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::VertexContainerPointerType,EdgeLabelType>* const>(
                            *itr_vertex_container_adj_found_result_itr
                        );
                    delete edge_endpoint_to_erase_ptr; // This is to avoid memory leaks
                    digraph_vertices_itr_vertex_container_adj.erase(itr_vertex_container_adj_found_result_itr);
                }
            }
            if ( vertex_container_to_erase_found_vertices_itr != vertices.end() ) {
                auto& vertex_container_to_erase = *vertex_container_to_erase_found_vertices_itr;
                auto& vertex_container_to_erase_adj = vertex_container_to_erase.adj;
                for(auto vertex_container_to_erase_adj_itr = vertex_container_to_erase_adj.begin();
                    vertex_container_to_erase_adj_itr != vertex_container_to_erase_adj.end();) {
                    auto edge_endpoint_to_erase_ptr =
                        static_cast<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::template labeled_directed_edge_endpoint<typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>::VertexContainerPointerType,EdgeLabelType>* const>(
                            *vertex_container_to_erase_adj_itr
                        );
                    delete edge_endpoint_to_erase_ptr; // This is to avoid memory leaks
                    vertex_container_to_erase_adj_itr = vertex_container_to_erase_adj.erase(vertex_container_to_erase_adj_itr);
                }
                vertices.erase(vertex_container_to_erase_found_vertices_itr);
            }
            //TODO:: Evaluate a possible exception throw HERE
        }
        //TODO:: Evaluate a possible exception throw HERE
    }
    //TODO:: Evaluate a possible exception throw HERE
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::EDGE_ITERATOR_NAME
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::erase_edge(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
VertexLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_vertex_label(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME, bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
    const VertexType& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        vertex_to_insert,
        vertex_label_to_insert
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::directed
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME, bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
const VertexType& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        vertex_to_insert,
        std::move(vertex_label_to_insert)
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::directed
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME,bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, const VertexLabelType& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        std::move(vertex_to_insert),
        vertex_label_to_insert
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::directed
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME, bool>
MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_vertex(
VertexType&& vertex_to_insert, VertexLabelType&& vertex_label_to_insert) {
    auto inner_insertion_result = vertices.emplace(
        std::move(vertex_to_insert),
        std::move(vertex_label_to_insert)
    );
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME, bool>(
        MAIN_LIBRARY_NAMESPACE::graph<VertexType>::vertex_ptr_factory(
            this,
            *(inner_insertion_result.first),
            MAIN_LIBRARY_NAMESPACE::edge_type::directed
        ),
        inner_insertion_result.second
    );
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
EdgeLabelType& MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::get_edge_label(
    const typename graph<VertexType>::CONSTANT_EDGE_ITERATOR_NAME&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&,
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&,
    const EdgeLabelType&) {
    //TODO: real implementation
}

template<typename VertexType, typename VertexLabelType, typename EdgeLabelType, typename Compare, typename T1, typename T2>
void MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<VertexType,VertexLabelType,EdgeLabelType,Compare,T1,T2>::insert_edge(
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&,
    const typename graph<VertexType>::CONSTANT_VERTEX_PTR_NAME&,
    EdgeLabelType&&) {
    //TODO: real implementation
}

//TODO: continue class implementation

#endif //FULL_LABELED_SET_VERTEX_DIGRAPH_H