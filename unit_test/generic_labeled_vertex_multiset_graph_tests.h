#ifndef GENERIC_LABELED_VERTEX_MULTISET_GRAPH_TESTS_H
#define GENERIC_LABELED_VERTEX_MULTISET_GRAPH_TESTS_H

#include "gtest/gtest.h"
#include "graphdom/labeled_vertex_set_graph.h"
#include "graphdom/labeled_vertex_multiset_graph.h"

#define LABELED_VERTEX_MULTISET_GRAPH_IS_A_LABELED_VERTEX_MULTISET_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME,VERTEX_LABEL_TYPENAME)    \
    TEST(TEST_SUITE_NAME,is_a_labeled_vertex_set_graph) {                                                                                                   \
        CONCRETE_CLASS_NAME graph;                                                                                                                          \
        using graph_class_alias = graphdom::labeled_vertex_multiset_graph<VERTEX_TYPENAME,VERTEX_LABEL_TYPENAME>;                                           \
        EXPECT_NE(dynamic_cast< graph_class_alias* >( &graph ),nullptr);                                                                                    \
    }                                                                                                                                                       \

#define LABELED_VERTEX_MULTISET_GRAPH_IS_NOT_A_LABELED_VERTEX_SET_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME,VERTEX_LABEL_TYPENAME) \
    TEST(TEST_SUITE_NAME,is_not_a_labeled_vertex_multiset_graph) {                                                                                      \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        using graph_class_alias = graphdom::labeled_vertex_set_graph<VERTEX_TYPENAME,VERTEX_LABEL_TYPENAME>;                                            \
        EXPECT_EQ(dynamic_cast< graph_class_alias* >( &graph ),nullptr);                                                                                \
    }                                                                                                                                                   \

#endif //GENERIC_LABELED_VERTEX_MULTISET_GRAPH_TESTS_H