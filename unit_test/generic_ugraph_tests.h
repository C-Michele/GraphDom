#ifndef GENERIC_UGRAPH_TESTS_H
#define GENERIC_UGRAPH_TESTS_H

#include <utility>

#include "gtest/gtest.h"
#include "graphdom/non_mixed_graph.h"
#include "graphdom/mixed_graph.h"

#define UGRAPH_IS_A_NON_MIXED_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)               \
    TEST(TEST_SUITE_NAME,is_a_non_mixed_graph) {                                                            \
        CONCRETE_CLASS_NAME graph;                                                                          \
        EXPECT_NE(dynamic_cast< typename graphdom::non_mixed_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);  \
    }                                                                                                       \

#define UGRAPH_IS_NOT_A_MIXED_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)           \
    TEST(TEST_SUITE_NAME,is_not_a_mixed_graph) {                                                        \
        CONCRETE_CLASS_NAME graph;                                                                      \
        EXPECT_EQ(dynamic_cast< typename graphdom::mixed_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);  \
    }                                                                                                   \

#endif //GENERIC_UGRAPH_TESTS_H