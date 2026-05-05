#ifndef GENERIC_SET_UGRAPH_TESTS_H
#define GENERIC_SET_UGRAPH_TESTS_H

#include <vector>
#include <utility>
#include <cstddef>
#include <map>

#include "gtest/gtest.h"
#include "graphdom/graph.h"

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)      \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__not_constant_adj_list__not_c_methods) {                                      \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle > inserted_vertices;                                   \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    ASSERT_EQ(k_adj_list_directed.begin(),k_adj_list_directed.end());                                                                   \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.begin(); edge_itr != k_adj_list_undirected.end(); ++edge_itr){                            \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)          \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__not_constant_adj_list__c_methods) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle > inserted_vertices;                                 \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    ASSERT_EQ(k_adj_list_directed.cbegin(),k_adj_list_directed.cend());                                                                 \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.cbegin(); edge_itr != k_adj_list_undirected.cend(); ++edge_itr){                          \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)          \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__constant_adj_list__not_c_methods) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle > inserted_vertices;                                 \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    ASSERT_EQ(k_adj_list_directed.begin(),k_adj_list_directed.end());                                                                   \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.begin(); edge_itr != k_adj_list_undirected.end(); ++edge_itr){                            \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_NOT_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)              \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__not_constant_vertex_ptr__constant_adj_list__c_methods) {                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle > inserted_vertices;                                 \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    ASSERT_EQ(k_adj_list_directed.cbegin(),k_adj_list_directed.cend());                                                                 \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.cbegin(); edge_itr != k_adj_list_undirected.cend(); ++edge_itr){                          \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)          \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__not_constant_adj_list__not_c_methods) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle > inserted_vertices;                             \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    ASSERT_EQ(k_adj_list_directed.begin(),k_adj_list_directed.end());                                                                   \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.begin(); edge_itr != k_adj_list_undirected.end(); ++edge_itr){                            \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)              \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__not_constant_adj_list__c_methods) {                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle > inserted_vertices;                             \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                              \
                    ASSERT_EQ(k_adj_list_directed.cbegin(),k_adj_list_directed.cend());                                                                 \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].adj_list();                                                                                  \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                          \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.cbegin(); edge_itr != k_adj_list_undirected.cend(); ++edge_itr){                          \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)              \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__constant_adj_list__not_c_methods) {                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle > inserted_vertices;                             \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    ASSERT_EQ(k_adj_list_directed.begin(),k_adj_list_directed.end());                                                                   \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.begin(); edge_itr != k_adj_list.end(); ++edge_itr){                                                  \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.begin(); edge_itr != k_adj_list_undirected.end(); ++edge_itr){                            \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_INSERTION_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                  \
    TEST(TEST_SUITE_NAME,correct_edges_insertion__constant_vertex_ptr__constant_adj_list__c_methods) {                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 30;                                                                                       \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle > inserted_vertices;                             \
        inserted_vertices.reserve(number_of_different_vertex_values);                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            inserted_vertices.emplace_back( ( graph.insert_vertex( i ) ).first );                                                                       \
        }                                                                                                                                               \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {                                                                         \
            for(std::size_t second = first; second < inserted_vertices.size(); ++second) {                                                              \
                graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );                                                               \
                for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                           \
                    auto k_adj_list_directed = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::directed);                        \
                    ASSERT_EQ(k_adj_list_directed.cbegin(),k_adj_list_directed.cend());                                                                 \
                                                                                                                                                        \
                    std::set<const std::size_t*> expected_vertices_in_k_adj_lists;                                                                      \
                    if( k < first ){                                                                                                                    \
                        for(std::size_t j = 0; j < inserted_vertices.size(); ++j ){                                                                     \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else if( k == first ){                                                                                                              \
                        for(std::size_t j = 0; j <= second; ++j ){                                                                                      \
                            expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                         \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                    else{                                                                                                                               \
                        if( k <= second ){                                                                                                              \
                            for(std::size_t j = 0; j <= first; ++j ){                                                                                   \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                        else{                                                                                                                           \
                            for(std::size_t j = 0; j < first; ++j ){                                                                                    \
                                expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );                                                     \
                            }                                                                                                                           \
                        }                                                                                                                               \
                    }                                                                                                                                   \
                                                                                                                                                        \
                    auto k_adj_list = inserted_vertices[k].const_adj_list();                                                                            \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list;                                                                    \
                    for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr){                                                \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );                            \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());                                       \
                                                                                                                                                        \
                    auto k_adj_list_undirected = inserted_vertices[k].const_adj_list(MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                    \
                    std::set<const std::size_t*> vertices_encountered_in_k_adj_list_undirected;                                                         \
                    for(auto edge_itr = k_adj_list_undirected.cbegin(); edge_itr != k_adj_list_undirected.cend(); ++edge_itr){                          \
                        ASSERT_EQ(edge_itr.edge_type(),MAIN_LIBRARY_NAMESPACE::edge_type::undirected);                                                  \
                                                                                                                                                        \
                        const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));                                                         \
                        EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_undirected.emplace( edge_itr_vertex_raw_pointer ) ).second );                 \
                        ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );     \
                    }                                                                                                                                   \
                    ASSERT_EQ(vertices_encountered_in_k_adj_list_undirected.size(),expected_vertices_in_k_adj_lists.size());                            \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_NOT_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                            \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__not_constant_vertex_ptr__not_constant_adj_list__not_c_methods) {                                                                            \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                                     \
                    ASSERT_EQ( j_adj_list_directed.begin() , j_adj_list_directed.end() );                                                                                                   \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).adj_list();                                                                                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                 \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_NOT_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__not_constant_vertex_ptr__not_constant_adj_list__c_methods) {                                                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                                     \
                    ASSERT_EQ( j_adj_list_directed.cbegin() , j_adj_list_directed.cend() );                                                                                                 \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).adj_list();                                                                                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                 \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_NOT_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__not_constant_vertex_ptr__constant_adj_list__not_c_methods) {                                                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                               \
                    ASSERT_EQ( j_adj_list_directed.begin() , j_adj_list_directed.end() );                                                                                                   \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).const_adj_list();                                                                                                     \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_NOT_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                    \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__not_constant_vertex_ptr__constant_adj_list__c_methods) {                                                                                    \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                       \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                               \
                    ASSERT_EQ( j_adj_list_directed.cbegin() , j_adj_list_directed.cend() );                                                                                                 \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).const_adj_list();                                                                                                     \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__constant_vertex_ptr__not_constant_adj_list__not_c_methods) {                                                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                                     \
                    ASSERT_EQ( j_adj_list_directed.begin() , j_adj_list_directed.end() );                                                                                                   \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).adj_list();                                                                                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                 \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_CONSTANT_VERTEX_PTR_NOT_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                    \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__constant_vertex_ptr__not_constant_adj_list__c_methods) {                                                                                    \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                                     \
                    ASSERT_EQ( j_adj_list_directed.cbegin() , j_adj_list_directed.cend() );                                                                                                 \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).adj_list();                                                                                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                 \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_NOT_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                    \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__constant_vertex_ptr__constant_adj_list__not_c_methods) {                                                                                    \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                               \
                    ASSERT_EQ( j_adj_list_directed.begin() , j_adj_list_directed.end() );                                                                                                   \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).const_adj_list();                                                                                                     \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.begin(); edge_itr != j_adj_list.end(); ++edge_itr ) {                                                                                    \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#define SET_VERTEX_UGRAPH_CORRECT_EDGES_ERASION_CONSTANT_VERTEX_PTR_CONSTANT_ADJ_LIST_C_METHODS(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                        \
    TEST(TEST_SUITE_NAME,correct_edges_erasion__constant_vertex_ptr__constant_adj_list__c_methods) {                                                                                        \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                          \
        const std::size_t number_of_different_vertex_values = 30;                                                                                                                           \
        std::map<                                                                                                                                                                           \
            const std::size_t*,                                                                                                                                                             \
            std::pair<                                                                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                std::set< const std::size_t* >                                                                                                                                              \
            >                                                                                                                                                                               \
        > inserted_vertices_and_incidence_matrix;                                                                                                                                           \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                \
            typename std::pair<                                                                                                                                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                                                                   \
                typename std::set< const std::size_t* >                                                                                                                                     \
            > pair_to_insert{ ( graph.insert_vertex( i ) ).first , std::set< const std::size_t* >() };                                                                                      \
            inserted_vertices_and_incidence_matrix.emplace( &( *( pair_to_insert.first ) ) , std::move( pair_to_insert ) );                                                                 \
        }                                                                                                                                                                                   \
        for( auto first_itr = inserted_vertices_and_incidence_matrix.begin(); first_itr != inserted_vertices_and_incidence_matrix.end(); ++first_itr ){                                     \
            for( auto second_itr = first_itr; second_itr != inserted_vertices_and_incidence_matrix.end(); ++second_itr ){                                                                   \
                graph.insert_edge( ( ( *first_itr ).second ).first , ( ( *second_itr ).second ).first );                                                                                    \
                ( ( ( *first_itr ).second ).second ).emplace( ( *second_itr ).first );                                                                                                      \
                ( ( ( *second_itr ).second ).second ).emplace( ( *first_itr ).first );                                                                                                      \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
        for( auto itr_k = inserted_vertices_and_incidence_matrix.begin(); itr_k != inserted_vertices_and_incidence_matrix.end(); ++itr_k ) {                                                \
            auto k_adj_list = ( ( ( *itr_k ).second ).first ).adj_list();                                                                                                                   \
            auto const itr_k_vertex_raw_pointer = ( *itr_k ).first;                                                                                                                         \
            for(auto k_adj_list_edge_itr = k_adj_list.begin(); k_adj_list_edge_itr != k_adj_list.end(); ){                                                                                  \
                auto k_adj_list_next_edge_itr = k_adj_list_edge_itr;                                                                                                                        \
                ++k_adj_list_next_edge_itr;                                                                                                                                                 \
                                                                                                                                                                                            \
                const std::size_t* const k_adj_list_edge_itr_vertex_endpoint_raw_pointer = &( *( *k_adj_list_edge_itr ) );                                                                  \
                                                                                                                                                                                            \
                k_adj_list_edge_itr = graph.erase_edge( k_adj_list_edge_itr );                                                                                                              \
                EXPECT_EQ( k_adj_list_edge_itr , k_adj_list_next_edge_itr );                                                                                                                \
                ( ( inserted_vertices_and_incidence_matrix.at( itr_k_vertex_raw_pointer ) ).second ).erase( k_adj_list_edge_itr_vertex_endpoint_raw_pointer );                              \
                ( ( inserted_vertices_and_incidence_matrix.at( k_adj_list_edge_itr_vertex_endpoint_raw_pointer ) ).second ).erase( itr_k_vertex_raw_pointer );                              \
                                                                                                                                                                                            \
                for( auto itr_j = inserted_vertices_and_incidence_matrix.begin(); itr_j != inserted_vertices_and_incidence_matrix.end(); ++itr_j ){                                         \
                    auto j_adj_list_directed = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::directed );                                               \
                    ASSERT_EQ( j_adj_list_directed.cbegin() , j_adj_list_directed.cend() );                                                                                                 \
                                                                                                                                                                                            \
                    const auto& expected_vertices_raw_pointers_in_j_adj_lists = ( ( *itr_j ).second ).second;                                                                               \
                                                                                                                                                                                            \
                    auto j_adj_list = ( ( ( *itr_j ).second ).first ).const_adj_list();                                                                                                     \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list;                                                                                           \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                                 \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                             \
                                                                                                                                                                                            \
                    auto j_adj_list_undirected = ( ( ( *itr_j ).second ).first ).const_adj_list( MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                           \
                    std::set<const std::size_t*> vertices_raw_pointers_encountered_in_j_adj_list_undirected;                                                                                \
                    for(auto edge_itr = j_adj_list.cbegin(); edge_itr != j_adj_list.cend(); ++edge_itr ) {                                                                                  \
                        ASSERT_EQ( edge_itr.edge_type() , MAIN_LIBRARY_NAMESPACE::edge_type::undirected );                                                                                  \
                                                                                                                                                                                            \
                        const std::size_t* const edge_itr_endpoint_raw_pointer = &( *( *( edge_itr ) ) );                                                                                   \
                        EXPECT_TRUE( ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.emplace( edge_itr_endpoint_raw_pointer ) ).second );                                      \
                        ASSERT_NE( expected_vertices_raw_pointers_in_j_adj_lists.find( edge_itr_endpoint_raw_pointer ) , expected_vertices_raw_pointers_in_j_adj_lists.end() );             \
                    }                                                                                                                                                                       \
                    ASSERT_EQ( vertices_raw_pointers_encountered_in_j_adj_list_undirected.size() , expected_vertices_raw_pointers_in_j_adj_lists.size() );                                  \
                }                                                                                                                                                                           \
            }                                                                                                                                                                               \
        }                                                                                                                                                                                   \
    }                                                                                                                                                                                       \

#endif //GENERIC_SET_UGRAPH_TESTS_H