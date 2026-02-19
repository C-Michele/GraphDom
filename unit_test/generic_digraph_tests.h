#ifndef GENERIC_DIGRAPH_TESTS_H
#define GENERIC_DIGRAPH_TESTS_H

#include <utility>

#include "gtest/gtest.h"
#include "../non_mixed_graph.h"
#include "../mixed_graph.h"

#define DIGRAPH_IS_A_NON_MIXED_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                              \
    TEST(TEST_SUITE_NAME,is_a_non_mixed_graph) {                                                                            \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        EXPECT_NE(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::non_mixed_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);    \
    }                                                                                                                       \

#define DIGRAPH_IS_NOT_A_MIXED_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                              \
    TEST(TEST_SUITE_NAME,is_not_a_mixed_graph) {                                                                            \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        EXPECT_EQ(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::mixed_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);        \
    }                                                                                                                       \

#endif //GENERIC_DIGRAPH_TESTS_H