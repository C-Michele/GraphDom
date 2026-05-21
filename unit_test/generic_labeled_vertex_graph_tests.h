#ifndef GRAPHDOM_GENERIC_LABELED_VERTEX_GRAPH_TESTS_H
#define GRAPHDOM_GENERIC_LABELED_VERTEX_GRAPH_TESTS_H

#include "gtest/gtest.h"
#include "graphdom/labeled_vertex_graph.h"

#define IS_A_LABELED_VERTEX_GRAPH(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME,VERTEX_LABEL_TYPENAME)                            \
    TEST(TEST_SUITE_NAME,is_a_labeled_vertex_graph) {                                                                                   \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        EXPECT_NE(dynamic_cast< typename graphdom::labeled_vertex_graph<VERTEX_TYPENAME,VERTEX_LABEL_TYPENAME>* >( &graph ),nullptr);   \
    }                                                                                                                                   \

#endif //GRAPHDOM_GENERIC_LABELED_VERTEX_GRAPH_TESTS_H