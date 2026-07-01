#ifndef GRAPHDOM_GENERIC_GRAPH_TESTS_H
#define GRAPHDOM_GENERIC_GRAPH_TESTS_H

#include <utility>

#include "gtest/gtest.h"
#include "graphdom/graphdom.h"

#define IS_A_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                        \
    TEST(TEST_SUITE_NAME,is_a_graph) {                                                              \
        CONCRETE_CLASS_NAME graph;                                                                  \
        EXPECT_NE(dynamic_cast< typename graphdom::graph<VERTEX_TYPENAME>* >( &graph ),nullptr);    \
    }                                                                                               \

#define NO_VERTICES_AFTER_DEFAULT_CONSTRUCTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME, no_vertices_after_default_construction) {                         \
        CONCRETE_CLASS_NAME graph;                                                          \
        EXPECT_EQ(graph.order(),0);                                                         \
    }                                                                                       \

#endif //GENERIC_GRAPH_TESTS_H