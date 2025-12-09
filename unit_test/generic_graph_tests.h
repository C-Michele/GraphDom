#ifndef GENERIC_GRAPH_TESTS_H
#define GENERIC_GRAPH_TESTS_H

#include <utility>

#include "gtest/gtest.h"
#include "../graph.h"

template <typename VertexType>
[[nodiscard]] std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME,bool> graph_vertex_insertion(MAIN_LIBRARY_NAMESPACE::graph<VertexType>& graph, const VertexType& vertex_to_insert) {
    if(dynamic_cast<MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>*>(&graph) != nullptr) {
        auto& set_vertex_graph = dynamic_cast<MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>&>(graph);
        return set_vertex_graph.insert_vertex(vertex_to_insert);
    }
    auto& multiset_vertex_graph = dynamic_cast<MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>&>(graph);
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME,bool>(multiset_vertex_graph.insert_vertex(vertex_to_insert),true);
}

template <typename VertexType>
[[nodiscard]] std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME,bool> graph_vertex_insertion(MAIN_LIBRARY_NAMESPACE::graph<VertexType>& graph, VertexType&& vertex_to_insert) {
    if(dynamic_cast<MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>*>(&graph) != nullptr) {
        auto& set_vertex_graph = dynamic_cast<MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>&>(graph);
        return set_vertex_graph.insert_vertex(vertex_to_insert);
    }
    auto& multiset_vertex_graph = dynamic_cast<MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VertexType>&>(graph);
    return std::pair<typename MAIN_LIBRARY_NAMESPACE::graph<VertexType>::VERTEX_PTR_NAME,bool>(multiset_vertex_graph.insert_vertex(vertex_to_insert),true);
}

#define IS_A_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                                    \
    TEST(TEST_SUITE_NAME,is_a_graph) {                                                                          \
        CONCRETE_CLASS_NAME graph;                                                                              \
        EXPECT_NE(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::graph<VERTEX_TYPENAME>* >( &graph ),nullptr);  \
    }                                                                                                           \

#define NO_VERTICES_AFTER_DEFAULT_CONSTRUCTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME, no_vertices_after_default_construction) {                         \
        CONCRETE_CLASS_NAME graph;                                                          \
        EXPECT_EQ(graph.order(),0);                                                         \
    }                                                                                       \

#endif //GENERIC_GRAPH_TESTS_H