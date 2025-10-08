#ifndef GENERIC_SET_VERTEX_GRAPH_TESTS_H
#define GENERIC_SET_VERTEX_GRAPH_TESTS_H

#include <utility>
#include <string>
#include <forward_list>
#include <vector>
#include <cstddef>

#include "gtest/gtest.h"
#include "../graph.h"

#define SET_VERTEX_GRAPH_CORRECT_BEHAVIOR_OF_ORDER_METHOD_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                 \
    TEST(TEST_SUITE_NAME, correct_behavior_of_order_method) {                                                       \
        CONCRETE_CLASS_NAME graph;                                                                                  \
        const std::size_t number_of_vertices = 10;                                                                  \
        std::forward_list<MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME> inserted_vertices_pointers;  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                       \
            for(std::size_t j = 0; j <= i; ++j) {                                                                   \
                const auto insertion_result = graph.insert_vertex(j);                                               \
                if(j<i) {                                                                                           \
                    ASSERT_EQ(graph.order(),i);                                                                     \
                }                                                                                                   \
                else {                                                                                              \
                    ASSERT_EQ(graph.order(),i+1);                                                                   \
                    inserted_vertices_pointers.emplace_front( insertion_result.first );                             \
                }                                                                                                   \
            }                                                                                                       \
        }                                                                                                           \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                       \
            graph.erase_vertex( inserted_vertices_pointers.front() );                                               \
            ASSERT_EQ(graph.order(),number_of_vertices-(i+1));                                                      \
            inserted_vertices_pointers.pop_front();                                                                 \
        }                                                                                                           \
    }                                                                                                               \

#define SET_VERTEX_GRAPH_CORRECT_RETURNED_BOOLEAN_AFTER_VERTEX_INSERTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)  \
    TEST(TEST_SUITE_NAME, correct_returned_boolean_after_vertex_insertion) {                                        \
        CONCRETE_CLASS_NAME graph;                                                                                  \
        const std::size_t number_of_vertices = 10;                                                                  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                       \
            for(std::size_t j = 0; j <= i; ++j) {                                                                   \
                const auto insertion_result = graph.insert_vertex(j);                                               \
                if(j<i) {                                                                                           \
                    ASSERT_FALSE(insertion_result.second);                                                          \
                }                                                                                                   \
                else {                                                                                              \
                    ASSERT_TRUE(insertion_result.second);                                                           \
                }                                                                                                   \
            }                                                                                                       \
        }                                                                                                           \
    }                                                                                                               \

#define SET_VERTEX_GRAPH_CORRECT_RETURNED_POINTER_AFTER_VERTEX_INSERTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)  \
    TEST(TEST_SUITE_NAME, correct_returned_pointer_after_vertex_insertion) {                                        \
        CONCRETE_CLASS_NAME graph;                                                                                  \
        const std::size_t number_of_vertices = 10;                                                                  \
        std::vector<MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME> inserted_vertices_pointers;        \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                     \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                       \
            for(std::size_t j = 0; j <= i; ++j) {                                                                   \
                const auto insertion_result = graph.insert_vertex(j);                                               \
                if(j<i) {                                                                                           \
                    for(std::size_t k = 0; k<inserted_vertices_pointers.size(); ++k) {                              \
                        if(k==j) {                                                                                  \
                            ASSERT_TRUE(inserted_vertices_pointers[k] == insertion_result.first);                   \
                            ASSERT_FALSE(inserted_vertices_pointers[k] != insertion_result.first);                  \
                        }                                                                                           \
                        else {                                                                                      \
                            ASSERT_FALSE(inserted_vertices_pointers[k] == insertion_result.first);                  \
                            ASSERT_TRUE(inserted_vertices_pointers[k] != insertion_result.first);                   \
                        }                                                                                           \
                    }                                                                                               \
                }                                                                                                   \
                else {                                                                                              \
                    inserted_vertices_pointers.emplace_back(insertion_result.first);                                \
                }                                                                                                   \
            }                                                                                                       \
        }                                                                                                           \
    }                                                                                                               \

#endif //GENERIC_SET_VERTEX_GRAPH_TESTS_H