#ifndef GRAPHLAB_GENERIC_MULTISET_VERTEX_GRAPH_TESTS_H
#define GRAPHLAB_GENERIC_MULTISET_VERTEX_GRAPH_TESTS_H

#include <utility>
#include <forward_list>
#include <vector>
#include <cstddef>

#include "gtest/gtest.h"
#include "../graph.h"
#include "../multiset_vertex_graph.h"

#define MULTISET_VERTEX_GRAPH_IS_A_MULTISET_VERTEX_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)              \
    TEST(TEST_SUITE_NAME,is_a_multiset_vertex_graph) {                                                                          \
        CONCRETE_CLASS_NAME graph;                                                                                              \
        EXPECT_NE(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);  \
    }                                                                                                                           \

#define MULTISET_VERTEX_GRAPH_ORDER_METHOD_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                            \
    TEST(TEST_SUITE_NAME, order_method) {                                                                                       \
        CONCRETE_CLASS_NAME graph;                                                                                              \
        ASSERT_EQ(graph.order(),0);                                                                                             \
        const std::size_t number_of_different_vertex_values = 100;                                                              \
        const std::size_t number_of_repetitions = 10;                                                                           \
        std::forward_list<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME> inserted_vertices_pointers;     \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                            \
                inserted_vertices_pointers.emplace_front( graph.insert_vertex(i) );                                             \
                ASSERT_EQ(graph.order(),(i+1)*(j+1));                                                                           \
            }                                                                                                                   \
        }                                                                                                                       \
        for(std::size_t i = 0; i < number_of_different_vertex_values * number_of_repetitions; ++i) {                            \
            graph.erase_vertex( inserted_vertices_pointers.front() );                                                           \
            ASSERT_EQ(graph.order(),(number_of_different_vertex_values*number_of_repetitions)-(i+1));                           \
            inserted_vertices_pointers.pop_front();                                                                             \
        }                                                                                                                       \
    }                                                                                                                           \

#endif //GRAPHLAB_GENERIC_MULTISET_VERTEX_GRAPH_TESTS_H