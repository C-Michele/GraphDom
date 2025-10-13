#ifndef GENERIC_SET_VERTEX_GRAPH_TESTS_H
#define GENERIC_SET_VERTEX_GRAPH_TESTS_H

#include <utility>
#include <string>
#include <forward_list>
#include <vector>
#include <cstddef>

#include "gtest/gtest.h"
#include "../graph.h"

#define SET_VERTEX_GRAPH_CORRECT_BEHAVIOR_OF_ORDER_METHOD_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                         \
    TEST(TEST_SUITE_NAME, correct_behavior_of_order_method) {                                                               \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        ASSERT_EQ(graph.order(),0);                                                                                         \
        const std::size_t number_of_vertices = 100;                                                                         \
        std::forward_list<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME> inserted_vertices_pointers; \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                               \
            inserted_vertices_pointers.emplace_front( ( graph.insert_vertex(i) ).first );                                   \
            ASSERT_EQ(graph.order(),i+1);                                                                                   \
            for(std::size_t j = 0; j <= i; ++j) {                                                                           \
                const auto insertion_result = graph.insert_vertex(j);                                                       \
                ASSERT_EQ(graph.order(),i+1);                                                                               \
            }                                                                                                               \
        }                                                                                                                   \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                               \
            graph.erase_vertex( inserted_vertices_pointers.front() );                                                       \
            ASSERT_EQ(graph.order(),number_of_vertices-(i+1));                                                              \
            inserted_vertices_pointers.pop_front();                                                                         \
        }                                                                                                                   \
    }                                                                                                                       \

#define SET_VERTEX_GRAPH_CORRECT_RETURNED_BOOLEAN_AFTER_VERTEX_INSERTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)  \
    TEST(TEST_SUITE_NAME, correct_returned_boolean_after_vertex_insertion) {                                        \
        CONCRETE_CLASS_NAME graph;                                                                                  \
        const std::size_t number_of_vertices = 100;                                                                 \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                       \
            ASSERT_TRUE( ( graph.insert_vertex(i) ).second );                                                       \
            for(std::size_t j = 0; j <= i; ++j) {                                                                   \
                ASSERT_FALSE( ( graph.insert_vertex(j) ).second );                                                  \
            }                                                                                                       \
        }                                                                                                           \
    }                                                                                                               \

#define SET_VERTEX_GRAPH_CORRECT_RETURNED_POINTER_AFTER_VERTEX_INSERTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)      \
    TEST(TEST_SUITE_NAME, correct_returned_pointer_after_vertex_insertion) {                                            \
        CONCRETE_CLASS_NAME graph;                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                     \
        std::vector<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME> inserted_vertices_pointers;   \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                         \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                           \
            inserted_vertices_pointers.emplace_back( ( graph.insert_vertex(i) ).first );                                \
            for(std::size_t j = 0; j <= i; ++j) {                                                                       \
                const auto insertion_result_j = graph.insert_vertex(j);                                                 \
                for(std::size_t k = 0; k<inserted_vertices_pointers.size(); ++k) {                                      \
                    if(k==j) {                                                                                          \
                        ASSERT_TRUE(inserted_vertices_pointers[k] == insertion_result_j.first);                         \
                        ASSERT_FALSE(inserted_vertices_pointers[k] != insertion_result_j.first);                        \
                    }                                                                                                   \
                    else {                                                                                              \
                        ASSERT_FALSE(inserted_vertices_pointers[k] == insertion_result_j.first);                        \
                        ASSERT_TRUE(inserted_vertices_pointers[k] != insertion_result_j.first);                         \
                    }                                                                                                   \
                }                                                                                                       \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \

#define SET_VERTEX_GRAPH_CORRECT_VERTEX_POINTER_DEREFERENCING_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                 \
    TEST(TEST_SUITE_NAME, correct_vertex_pointer_dereferencing) {                                                       \
        CONCRETE_CLASS_NAME graph;                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                     \
        std::vector<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME> inserted_vertices_pointers;   \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                         \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                           \
            const auto insertion_result_i = graph.insert_vertex(i);                                                     \
            ASSERT_EQ( *( insertion_result_i.first ) , i );                                                             \
            inserted_vertices_pointers.emplace_back( insertion_result_i.first );                                        \
            for(std::size_t j = 0; j <= i; ++j) {                                                                       \
                const auto insertion_result_j = graph.insert_vertex(j);                                                 \
                ASSERT_EQ( *( insertion_result_j.first ) , j );                                                         \
                for(std::size_t k = 0; k<inserted_vertices_pointers.size(); ++k) {                                      \
                    if(k==j){                                                                                           \
                        ASSERT_EQ( &( inserted_vertices_pointers[k] ) , &( *( insertion_result_j.first ) ) );           \
                    }                                                                                                   \
                    else {                                                                                              \
                        ASSERT_NE( &( inserted_vertices_pointers[k] ) , &( *( insertion_result_j.first ) ) );           \
                    }                                                                                                   \
                }                                                                                                       \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \

#endif //GENERIC_SET_VERTEX_GRAPH_TESTS_H