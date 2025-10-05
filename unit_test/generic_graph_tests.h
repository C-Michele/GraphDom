#ifndef GENERIC_GRAPH_TESTS_H
#define GENERIC_GRAPH_TESTS_H

#include "gtest/gtest.h"

#define NO_VERTICES_AFTER_DEFAULT_CONSTRUCTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME, no_vertices_after_default_construction) {                         \
        CONCRETE_CLASS_NAME graph;                                                          \
        EXPECT_EQ(graph.order(),0);                                                         \
    }                                                                                       \

#define NO_EDGES_AFTER_DEFAULT_CONSTRUCTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)       \
    TEST(TEST_SUITE_NAME, no_edges_after_default_construction) {                            \
        CONCRETE_CLASS_NAME graph;                                                          \
        EXPECT_EQ(graph.size(),0);                                                          \
    }                                                                                       \

#endif //GENERIC_GRAPH_TESTS_H