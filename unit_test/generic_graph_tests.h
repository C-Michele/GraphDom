#ifndef GENERIC_GRAPH_TESTS_H
#define GENERIC_GRAPH_TESTS_H

#include "gtest/gtest.h"

#define SET_VERTEX_GRAPH_IS_A_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                   \
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