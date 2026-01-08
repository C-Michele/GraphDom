#ifndef GENERIC_MULTISET_VERTEX_DIGRAPH_TESTS_H
#define GENERIC_MULTISET_VERTEX_DIGRAPH_TESTS_H

#include <vector>
#include <cstddef>

#include "gtest/gtest.h"
#include "../graph.h"

#define MULTISET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_SPECIFIC_VERTEX_POINTER_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__specific_vertex_ptr__not_constant_adj_list__not_c_methods) {                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 10;                                                                                           \
        const std::size_t number_of_repetitions = 3;                                                                                                        \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<std::size_t>::VERTEX_PTR_NAME > inserted_vertices;                     \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                        \
                inserted_vertices.emplace_back( graph.insert_vertex( i ) );                                                                                 \
            }                                                                                                                                               \
        }                                                                                                                                                   \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                             \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                      \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                                   \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                               \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                              \
                    ASSERT_EQ(k_adj_list_undirected.begin(),k_adj_list_undirected.end());                                                                   \
                                                                                                                                                            \
                    std::set<std::size_t*> expected_vertices_in_k_adj_lists;                                                                                \
                    if( k < first ) {                                                                                                                       \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                         \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                             \
                        }                                                                                                                                   \
                    }                                                                                                                                       \
                    else if( k == first ) {                                                                                                                 \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                          \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                             \
                        }                                                                                                                                   \
                    }                                                                                                                                       \
                                                                                                                                                            \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                      \
                    std::set<std::size_t*> vertices_encountered_in_k_adj_list;                                                                              \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                      \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                        \
                                                                                                                                                            \
                        std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                                   \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                                \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );         \
                    }                                                                                                                                       \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                           \
                                                                                                                                                            \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                  \
                    std::set<std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                                     \
                    for(auto edge_itr = k_adj_list_directed.begin(); edge_itr != k_adj_list_directed.end(); ++edge_itr){                                    \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                        \
                                                                                                                                                            \
                        std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                                   \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                       \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );         \
                    }                                                                                                                                       \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                                  \
                }                                                                                                                                           \
            }                                                                                                                                               \
        }                                                                                                                                                   \
    }                                                                                                                                                       \

#define MULTISET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_SPECIFIC_VERTEX_POINTER_NOT_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__specific_vertex_ptr__not_constant_adj_list__c_methods) {                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 10;                                                                                           \
        const std::size_t number_of_repetitions = 3;                                                                                                        \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<std::size_t>::VERTEX_PTR_NAME > inserted_vertices;                     \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                        \
                inserted_vertices.emplace_back( graph.insert_vertex( i ) );                                                                                 \
            }                                                                                                                                               \
        }                                                                                                                                                   \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                             \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                      \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                                   \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                               \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                              \
                    ASSERT_EQ(k_adj_list_undirected.cbegin(),k_adj_list_undirected.cend());                                                                 \
                                                                                                                                                            \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                                \
                    if( k < first ) {                                                                                                                       \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                         \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                             \
                        }                                                                                                                                   \
                    }                                                                                                                                       \
                    else if( k == first ) {                                                                                                                 \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                          \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                             \
                        }                                                                                                                                   \
                    }                                                                                                                                       \
                                                                                                                                                            \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                      \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                        \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                    \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                        \
                                                                                                                                                            \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                             \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                                \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );         \
                    }                                                                                                                                       \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                           \
                                                                                                                                                            \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                               \
                    for(auto edge_itr = k_adj_list_directed.cbegin(); edge_itr != k_adj_list_directed.cend(); ++edge_itr){                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                        \
                                                                                                                                                            \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                             \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                       \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );         \
                    }                                                                                                                                       \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                                  \
                }                                                                                                                                           \
            }                                                                                                                                               \
        }                                                                                                                                                   \
    }                                                                                                                                                       \

#endif //GENERIC_MULTISET_VERTEX_DIGRAPH_TESTS_H