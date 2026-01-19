#ifndef GENERIC_SET_VERTEX_DIGRAPH_TESTS_H
#define GENERIC_SET_VERTEX_DIGRAPH_TESTS_H

#include <vector>
#include <utility>
#include <cstddef>

#include "gtest/gtest.h"
#include "../graph.h"

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)     \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__not_constant_adj_list__not_c_methods) {                                      \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME > inserted_vertices;                                 \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    ASSERT_EQ(k_adj_list_undirected.begin(),k_adj_list_undirected.end());                                                               \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.begin(); edge_itr != k_adj_list_directed.end(); ++edge_itr){                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)         \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__not_constant_adj_list__c_methods) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME > inserted_vertices;                                 \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    ASSERT_EQ(k_adj_list_undirected.cbegin(),k_adj_list_undirected.cend());                                                             \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.cbegin(); edge_itr != k_adj_list_directed.cend(); ++edge_itr){                              \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)         \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__constant_adj_list__not_c_methods) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME > inserted_vertices;                                 \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    ASSERT_EQ(k_adj_list_undirected.begin(),k_adj_list_undirected.end());                                                               \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.begin(); edge_itr != k_adj_list_directed.end(); ++edge_itr){                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)             \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__constant_adj_list__c_methods) {                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME > inserted_vertices;                                 \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    ASSERT_EQ(k_adj_list_undirected.cbegin(),k_adj_list_undirected.cend());                                                             \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.cbegin(); edge_itr != k_adj_list_directed.cend(); ++edge_itr){                              \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)         \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__not_constant_adj_list__not_c_methods) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME > inserted_vertices;                        \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    ASSERT_EQ(k_adj_list_undirected.begin(),k_adj_list_undirected.end());                                                               \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.begin(); edge_itr != k_adj_list_directed.end(); ++edge_itr){                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)             \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__not_constant_adj_list__c_methods) {                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME > inserted_vertices;                        \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    ASSERT_EQ(k_adj_list_undirected.cbegin(),k_adj_list_undirected.cend());                                                             \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.cbegin(); edge_itr != k_adj_list_directed.cend(); ++edge_itr){                              \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)             \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__constant_adj_list__not_c_methods) {                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME > inserted_vertices;                        \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    ASSERT_EQ(k_adj_list_undirected.begin(),k_adj_list_undirected.end());                                                               \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.begin(); edge_itr != k_adj_list_directed.end(); ++edge_itr){                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                 \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__constant_adj_list__c_methods) {                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME > inserted_vertices;                        \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {                                                                  \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    ASSERT_EQ(k_adj_list_undirected.cbegin(),k_adj_list_undirected.cend());                                                             \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ) {                                                                                                                   \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ) {                                                                                                             \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;                                                           \
                    for(auto edge_itr = k_adj_list_directed.cbegin(); edge_itr != k_adj_list_directed.cend(); ++edge_itr){                              \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::directed);                                                    \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );                   \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_DIGRAPH_CORRECT_EDGES_ERASION_NOT_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                           \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__not_constant_vertex_ptr__not_constant_adj_list__not_c_methods) {                                                                            \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        typename std::vector<                                                                                                                                                               \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME,                                                                                                       \
                typename std::set< const std::size_t* >                                                                                                                                     \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        inserted_vertices_and_incidence_matrix.reserve(number_of_different_vertex_values);                                                                                                  \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            inserted_vertices_and_incidence_matrix.emplace_back( ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() );                                                   \
        }                                                                                                                                                                                   \
        for(std::size_t first = 0; first < inserted_vertices_and_incidence_matrix.size(); ++first) {                                                                                        \
            for(std::size_t second = 0; second < inserted_vertices_and_incidence_matrix.size(); ++second) {                                                                                 \
                graph.insert_edge( ( inserted_vertices_and_incidence_matrix[first] ).first , ( inserted_vertices_and_incidence_matrix[second] ).first );                                    \
                ( ( inserted_vertices_and_incidence_matrix[first] ).second ).emplace( &( *( ( inserted_vertices_and_incidence_matrix[second] ).first ) ) );                                 \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for(std::size_t k = 0; k < inserted_vertices_and_incidence_matrix.size(); ++k ) {                                                                                                   \
            auto k_adj_list = ( ( inserted_vertices_and_incidence_matrix[k] ).first ).adj_list();                                                                                           \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix[k] ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                                                          \
                                                                                                                                                                                            \
                for(std::size_t j = 0; j < inserted_vertices_and_incidence_matrix.size(); ++j ){                                                                                            \
                    auto j_adj_list_undirected = ( ( inserted_vertices_and_incidence_matrix[j] ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                         \
                    ASSERT_EQ( j_adj_list_undirected.begin() , j_adj_list_undirected.end() );                                                                                               \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( inserted_vertices_and_incidence_matrix[j] ).second;                                                       \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( inserted_vertices_and_incidence_matrix[j] ).first ).adj_list();                                                                                   \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                                                                    \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_directed = ( ( inserted_vertices_and_incidence_matrix[j] ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                             \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_directed;                                                                                  \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                                                                    \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_directed.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                        \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_directed.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                    \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#endif //GENERIC_SET_VERTEX_DIGRAPH_TESTS_H