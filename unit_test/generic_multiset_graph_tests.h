#ifndef GENERIC_MULTISET_GRAPH_TESTS_H
#define GENERIC_MULTISET_GRAPH_TESTS_H

#include <utility>
#include <list>
#include <set>
#include <cstddef>

#include "gtest/gtest.h"
#include "graphlab/graph.h"

#define MULTISET_VERTEX_GRAPH_IS_A_MULTISET_VERTEX_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)              \
    TEST(TEST_SUITE_NAME,is_a_multiset_vertex_graph) {                                                                          \
        CONCRETE_CLASS_NAME graph;                                                                                              \
        EXPECT_NE(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::multiset_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);  \
    }                                                                                                                           \

#define MULTISET_VERTEX_GRAPH_IS_NOT_A_SET_VERTEX_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)           \
    TEST(TEST_SUITE_NAME,is_not_a_set_vertex_graph) {                                                                       \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        EXPECT_EQ(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::set_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);   \
    }                                                                                                                       \

#define MULTISET_VERTEX_GRAPH_ORDER_METHOD_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                            \
    TEST(TEST_SUITE_NAME, order_method) {                                                                                                       \
        CONCRETE_CLASS_NAME graph;                                                                                                              \
        ASSERT_EQ(graph.order(),0);                                                                                                             \
        const std::size_t number_of_different_vertex_values = 100;                                                                              \
        const std::size_t number_of_repetitions = 10;                                                                                           \
        std::list<typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle> inserted_vertices_pointers;               \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                            \
                inserted_vertices_pointers.emplace_front( graph.insert_vertex(i) );                                                             \
                ASSERT_EQ(graph.order(),inserted_vertices_pointers.size());                                                                     \
            }                                                                                                                                   \
        }                                                                                                                                       \
        for(std::size_t i = 0; i < number_of_different_vertex_values * number_of_repetitions; ++i) {                                            \
            graph.erase_vertex( inserted_vertices_pointers.front() );                                                                           \
            ASSERT_EQ(graph.order(),(number_of_different_vertex_values*number_of_repetitions)-(i+1));                                           \
            inserted_vertices_pointers.pop_front();                                                                                             \
        }                                                                                                                                       \
    }                                                                                                                                           \

#define MULTISET_VERTEX_GRAPH_CORRECT_SPECIFIC_VERTEX_POINTER_DEREFERENCING_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)       \
    TEST(TEST_SUITE_NAME, correct_specific_vertex_pointer_dereferencing) {                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                          \
        const std::size_t number_of_repetitions = 10;                                                                       \
        typename std::set<std::size_t*> inserted_vertices_raw_pointers;                                                     \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                        \
                const auto insertion_result = inserted_vertices_raw_pointers.emplace( &( *( graph.insert_vertex(i) ) ) );   \
                ASSERT_TRUE( insertion_result.second );                                                                     \
                ASSERT_EQ( *( *( insertion_result.first ) ) , i );                                                          \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \

#define MULTISET_VERTEX_GRAPH_CORRECT_SPECIFIC_VERTEX_POINTER_DEREFERENCING_AFTER_OTHER_VERTICES_ERASION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)  \
    TEST(TEST_SUITE_NAME, correct_specific_vertex_pointer_dereferencing_after_other_vertices_erasion) {                                             \
        CONCRETE_CLASS_NAME graph;                                                                                                                  \
        const std::size_t number_of_different_vertex_values = 100;                                                                                  \
        const std::size_t number_of_repetitions = 10;                                                                                               \
        typename std::vector<                                                                                                                       \
            std::pair<                                                                                                                              \
                typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle,                                                 \
                std::size_t*                                                                                                                        \
            >                                                                                                                                       \
        > inserted_vertices;                                                                                                                        \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                     \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                        \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                                 \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                 \
            }                                                                                                                                       \
        }                                                                                                                                           \
        while( ! inserted_vertices.empty() ) {                                                                                                      \
            graph.erase_vertex( ( inserted_vertices.back() ).first );                                                                               \
            inserted_vertices.pop_back();                                                                                                           \
            for(std::size_t k = 0; k<inserted_vertices.size(); ++k) {                                                                               \
                ASSERT_EQ( *( ( inserted_vertices[k] ).first ) , k/number_of_repetitions );                                                         \
                ASSERT_EQ( &( *( ( inserted_vertices[k] ).first ) ) , ( inserted_vertices[k] ).second );                                            \
            }                                                                                                                                       \
        }                                                                                                                                           \
    }                                                                                                                                               \

#define MULTISET_VERTEX_GRAPH_CORRECT_CONVERSION_FROM_SPECIFIC_VERTEX_POINTER_TO_CONST_VERTEX_POINTER_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)       \
    TEST(TEST_SUITE_NAME, correct_conversion_from_specific_vertex_pointer_to_constant_vertex_pointer_1) {                                               \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                                   \
        typename std::vector<                                                                                                                           \
            std::pair<                                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle,                                                     \
                std::size_t*                                                                                                                            \
            >                                                                                                                                           \
        > inserted_vertices;                                                                                                                            \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                    \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                                     \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                     \
            }                                                                                                                                           \
        }                                                                                                                                               \
        for(std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                                    \
            const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle const_vertex_ptr_k = ( inserted_vertices[k] ).first;         \
            ASSERT_EQ( *const_vertex_ptr_k , k/number_of_repetitions );                                                                                 \
            for(std::size_t j = 0; j < inserted_vertices.size(); ++j ) {                                                                                \
                if(j==k) {                                                                                                                              \
                    ASSERT_EQ( ( inserted_vertices[j] ).second , &( *( const_vertex_ptr_k ) ) );                                                        \
                }                                                                                                                                       \
                else {                                                                                                                                  \
                    ASSERT_NE( ( inserted_vertices[j] ).second , &( *( const_vertex_ptr_k ) ) );                                                        \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_CORRECT_CONVERSION_FROM_SPECIFIC_VERTEX_POINTER_TO_GENERIC_VERTEX_POINTER_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)     \
    TEST(TEST_SUITE_NAME, correct_conversion_from_specific_vertex_pointer_to_generic_vertex_pointer_1) {                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                                   \
        typename std::vector<                                                                                                                           \
            std::pair<                                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle,                                                     \
                std::size_t*                                                                                                                            \
            >                                                                                                                                           \
        > inserted_vertices;                                                                                                                            \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                    \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                                     \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                     \
            }                                                                                                                                           \
        }                                                                                                                                               \
        for(std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                                    \
            const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle vertex_ptr_k = ( inserted_vertices[k] ).first;                     \
            ASSERT_EQ( *vertex_ptr_k , k/number_of_repetitions );                                                                                       \
            for(std::size_t j = 0; j < inserted_vertices.size(); ++j ) {                                                                                \
                if(j==k) {                                                                                                                              \
                    ASSERT_EQ( ( inserted_vertices[j] ).second , &( *( vertex_ptr_k ) ) );                                                              \
                }                                                                                                                                       \
                else {                                                                                                                                  \
                    ASSERT_NE( ( inserted_vertices[j] ).second , &( *( vertex_ptr_k ) ) );                                                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_CORRECT_CONVERSION_FROM_GENERIC_VERTEX_POINTER_TO_SPECIFIC_VERTEX_POINTER_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)     \
    TEST(TEST_SUITE_NAME, correct_conversion_from_generic_vertex_pointer_to_specific_vertex_pointer_1) {                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                                   \
        typename std::vector<                                                                                                                           \
            std::pair<                                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                     \
                const std::size_t*                                                                                                                      \
            >                                                                                                                                           \
        > inserted_vertices;                                                                                                                            \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                    \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                                     \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                     \
            }                                                                                                                                           \
        }                                                                                                                                               \
        for(std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                                    \
            const typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle vertex_ptr_k( ( inserted_vertices[k] ).first );    \
            ASSERT_EQ( *vertex_ptr_k , k/number_of_repetitions );                                                                                       \
            for(std::size_t j = 0; j < inserted_vertices.size(); ++j ) {                                                                                \
                if(j==k) {                                                                                                                              \
                    ASSERT_EQ( ( inserted_vertices[j] ).second , &( *( vertex_ptr_k ) ) );                                                              \
                }                                                                                                                                       \
                else {                                                                                                                                  \
                    ASSERT_NE( ( inserted_vertices[j] ).second , &( *( vertex_ptr_k ) ) );                                                              \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_SPECIFIC_VERTEX_POINTER_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                       \
    TEST(TEST_SUITE_NAME, specific_vertex_pointer_equality_operator) {                                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                   \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle> inserted_vertices;    \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                           \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                                   \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                               \
                const auto last_inserted_vertex = inserted_vertices.back();                                                             \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                             \
                    if( k == inserted_vertices.size()-1 ){                                                                              \
                        ASSERT_TRUE(inserted_vertices[k] == last_inserted_vertex);                                                      \
                        ASSERT_TRUE(last_inserted_vertex == inserted_vertices[k]);                                                      \
                    }                                                                                                                   \
                    else {                                                                                                              \
                        ASSERT_FALSE(inserted_vertices[k] == last_inserted_vertex);                                                     \
                        ASSERT_FALSE(last_inserted_vertex == inserted_vertices[k]);                                                     \
                    }                                                                                                                   \
                }                                                                                                                       \
            }                                                                                                                           \
        }                                                                                                                               \
    }                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_SPECIFIC_VERTEX_POINTER_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                     \
    TEST(TEST_SUITE_NAME, specific_vertex_pointer_inequality_operator) {                                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                   \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle> inserted_vertices;    \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                           \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                                   \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                               \
                const auto last_inserted_vertex = inserted_vertices.back();                                                             \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                             \
                    if( k == inserted_vertices.size()-1 ){                                                                              \
                        ASSERT_FALSE(inserted_vertices[k] != last_inserted_vertex);                                                     \
                        ASSERT_FALSE(last_inserted_vertex != inserted_vertices[k]);                                                     \
                    }                                                                                                                   \
                    else {                                                                                                              \
                        ASSERT_TRUE(inserted_vertices[k] != last_inserted_vertex);                                                      \
                        ASSERT_TRUE(last_inserted_vertex != inserted_vertices[k]);                                                      \
                    }                                                                                                                   \
                }                                                                                                                       \
            }                                                                                                                           \
        }                                                                                                                               \
    }                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_VERTEX_POINTER_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                \
    TEST(TEST_SUITE_NAME, vertex_pointer_equality_operator) {                                                                                           \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                                   \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle> inserted_vertices;                                    \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                                           \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                                                   \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                                               \
                const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle last_inserted_vertex = inserted_vertices.back();               \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                                             \
                    if( k == inserted_vertices.size()-1 ){                                                                                              \
                        ASSERT_TRUE(inserted_vertices[k] == last_inserted_vertex);                                                                      \
                        ASSERT_TRUE(last_inserted_vertex == inserted_vertices[k]);                                                                      \
                    }                                                                                                                                   \
                    else {                                                                                                                              \
                        ASSERT_FALSE(inserted_vertices[k] == last_inserted_vertex);                                                                     \
                        ASSERT_FALSE(last_inserted_vertex == inserted_vertices[k]);                                                                     \
                    }                                                                                                                                   \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_VERTEX_POINTER_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                              \
    TEST(TEST_SUITE_NAME, vertex_pointer_inequality_operator) {                                                                                         \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                                   \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle> inserted_vertices;                                    \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                                           \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                                                   \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                                               \
                const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle last_inserted_vertex = inserted_vertices.back();               \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                                             \
                    if( k == inserted_vertices.size()-1 ){                                                                                              \
                        ASSERT_FALSE(inserted_vertices[k] != last_inserted_vertex);                                                                     \
                        ASSERT_FALSE(last_inserted_vertex != inserted_vertices[k]);                                                                     \
                    }                                                                                                                                   \
                    else {                                                                                                                              \
                        ASSERT_TRUE(inserted_vertices[k] != last_inserted_vertex);                                                                      \
                        ASSERT_TRUE(last_inserted_vertex != inserted_vertices[k]);                                                                      \
                    }                                                                                                                                   \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_CONSTANT_VERTEX_POINTER_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                               \
    TEST(TEST_SUITE_NAME, constant_vertex_pointer_equality_operator) {                                                                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                                                                              \
        const std::size_t number_of_repetitions = 10;                                                                                                           \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle> inserted_vertices;                                      \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                                 \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                                                   \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                                                           \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                                                       \
                const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle last_inserted_vertex = inserted_vertices.back();                 \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                                                     \
                    if( k == inserted_vertices.size()-1 ){                                                                                                      \
                        ASSERT_TRUE(inserted_vertices[k] == last_inserted_vertex);                                                                              \
                        ASSERT_TRUE(last_inserted_vertex == inserted_vertices[k]);                                                                              \
                    }                                                                                                                                           \
                    else {                                                                                                                                      \
                        ASSERT_FALSE(inserted_vertices[k] == last_inserted_vertex);                                                                             \
                        ASSERT_FALSE(last_inserted_vertex == inserted_vertices[k]);                                                                             \
                    }                                                                                                                                           \
                }                                                                                                                                               \
            }                                                                                                                                                   \
        }                                                                                                                                                       \
    }                                                                                                                                                           \

#define MULTISET_VERTEX_GRAPH_CONSTANT_VERTEX_POINTER_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                             \
    TEST(TEST_SUITE_NAME, constant_vertex_pointer_inequality_operator) {                                                                                        \
        CONCRETE_CLASS_NAME graph;                                                                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                                                                              \
        const std::size_t number_of_repetitions = 10;                                                                                                           \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle> inserted_vertices;                                      \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                                 \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                                                   \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                                                           \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                                                       \
                const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle last_inserted_vertex = inserted_vertices.back();                 \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                                                     \
                    if( k == inserted_vertices.size()-1 ){                                                                                                      \
                        ASSERT_FALSE(inserted_vertices[k] != last_inserted_vertex);                                                                             \
                        ASSERT_FALSE(last_inserted_vertex != inserted_vertices[k]);                                                                             \
                    }                                                                                                                                           \
                    else {                                                                                                                                      \
                        ASSERT_TRUE(inserted_vertices[k] != last_inserted_vertex);                                                                              \
                        ASSERT_TRUE(last_inserted_vertex != inserted_vertices[k]);                                                                              \
                    }                                                                                                                                           \
                }                                                                                                                                               \
            }                                                                                                                                                   \
        }                                                                                                                                                       \
    }                                                                                                                                                           \

#define MULTISET_VERTEX_GRAPH_CORRECT_RETURNED_SPECIFIC_VERTEX_POINTER_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)             \
    TEST(TEST_SUITE_NAME, correct_returned_specific_vertex_pointer_reference_after_assignment) {                                                        \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                                   \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle > inserted_vertices_pointers;          \
        inserted_vertices_pointers.reserve( number_of_different_vertex_values * number_of_repetitions );                                                \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                    \
                inserted_vertices_pointers.emplace_back( graph.insert_vertex(i) );                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle vertex_ptr = inserted_vertices_pointers.back();      \
                const typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle* const vertex_ptr_address = &vertex_ptr;       \
                for(std::size_t k = 0; k < inserted_vertices_pointers.size(); ++k )  {                                                                  \
                    ASSERT_EQ( &( vertex_ptr = inserted_vertices_pointers[k] ), vertex_ptr_address );                                                   \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_SPECIFIC_VERTEX_POINTER_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                   \
    TEST(TEST_SUITE_NAME, specific_vertex_pointer_assignment_operator_test_1) {                                                                         \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                                   \
        typename std::vector<                                                                                                                           \
            std::pair<                                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle,                                                     \
                std::size_t*                                                                                                                            \
            >                                                                                                                                           \
        > inserted_vertices;                                                                                                                            \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                            \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                    \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                                     \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                     \
                typename MAIN_LIBRARY_NAMESPACE::multiset_graph<std::size_t>::vertex_handle vertex_ptr = ( inserted_vertices.back() ).first;     \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                                           \
                    vertex_ptr = ( inserted_vertices[k] ).first;                                                                                        \
                    ASSERT_EQ( vertex_ptr , ( inserted_vertices[k] ).first );                                                                           \
                    ASSERT_EQ( &( *vertex_ptr ) , ( inserted_vertices[k] ).second );                                                                    \
                    ASSERT_EQ( *vertex_ptr , k/number_of_repetitions );                                                                                 \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_CORRECT_RETURNED_VERTEX_POINTER_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)      \
    TEST(TEST_SUITE_NAME, correct_returned_vertex_pointer_reference_after_assignment) {                                                 \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                   \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle > inserted_vertices_pointers;          \
        inserted_vertices_pointers.reserve( number_of_different_vertex_values * number_of_repetitions );                                \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                            \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                    \
                inserted_vertices_pointers.emplace_back( graph.insert_vertex(i) );                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle vertex_ptr = inserted_vertices_pointers.back();      \
                const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle* const vertex_ptr_address = &vertex_ptr;       \
                for(std::size_t k = 0; k < inserted_vertices_pointers.size(); ++k )  {                                                  \
                    ASSERT_EQ( &( vertex_ptr = inserted_vertices_pointers[k] ), vertex_ptr_address );                                   \
                }                                                                                                                       \
            }                                                                                                                           \
        }                                                                                                                               \
    }                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_VERTEX_POINTER_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                            \
    TEST(TEST_SUITE_NAME, vertex_pointer_assignment_operator_test_1) {                                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_different_vertex_values = 100;                                                                      \
        const std::size_t number_of_repetitions = 10;                                                                                   \
        typename std::vector<                                                                                                           \
            std::pair<                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                     \
                const std::size_t*                                                                                                      \
            >                                                                                                                           \
        > inserted_vertices;                                                                                                            \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                         \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                            \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                    \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                     \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                     \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle vertex_ptr = ( inserted_vertices.back() ).first;     \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                           \
                    vertex_ptr = ( inserted_vertices[k] ).first;                                                                        \
                    ASSERT_EQ( vertex_ptr , ( inserted_vertices[k] ).first );                                                           \
                    ASSERT_EQ( &( *vertex_ptr ) , ( inserted_vertices[k] ).second );                                                    \
                    ASSERT_EQ( *vertex_ptr , k/number_of_repetitions );                                                                 \
                }                                                                                                                       \
            }                                                                                                                           \
        }                                                                                                                               \
    }                                                                                                                                   \

#define MULTISET_VERTEX_GRAPH_CORRECT_RETURNED_CONSTANT_VERTEX_POINTER_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)     \
    TEST(TEST_SUITE_NAME, correct_returned_constant_vertex_pointer_reference_after_assignment) {                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                                                              \
        const std::size_t number_of_repetitions = 10;                                                                                           \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle > inserted_vertices_pointers;            \
        inserted_vertices_pointers.reserve( number_of_different_vertex_values * number_of_repetitions );                                        \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                            \
                inserted_vertices_pointers.emplace_back( graph.insert_vertex(i) );                                                              \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle vertex_ptr = inserted_vertices_pointers.back();        \
                const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle* const vertex_ptr_address = &vertex_ptr;         \
                for(std::size_t k = 0; k < inserted_vertices_pointers.size(); ++k )  {                                                          \
                    ASSERT_EQ( &( vertex_ptr = inserted_vertices_pointers[k] ), vertex_ptr_address );                                           \
                }                                                                                                                               \
            }                                                                                                                                   \
        }                                                                                                                                       \
    }                                                                                                                                           \

#define MULTISET_VERTEX_GRAPH_CONSTANT_VERTEX_POINTER_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                           \
    TEST(TEST_SUITE_NAME, constant_vertex_pointer_assignment_operator_test_1) {                                                                 \
        CONCRETE_CLASS_NAME graph;                                                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                                                              \
        const std::size_t number_of_repetitions = 10;                                                                                           \
        typename std::vector<                                                                                                                   \
            std::pair<                                                                                                                          \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle,                                                       \
                const std::size_t*                                                                                                              \
            >                                                                                                                                   \
        > inserted_vertices;                                                                                                                    \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                 \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                            \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                             \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                             \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_const_handle vertex_ptr = ( inserted_vertices.back() ).first;       \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                                   \
                    vertex_ptr = ( inserted_vertices[k] ).first;                                                                                \
                    ASSERT_EQ( vertex_ptr , ( inserted_vertices[k] ).first );                                                                   \
                    ASSERT_EQ( &( *vertex_ptr ) , ( inserted_vertices[k] ).second );                                                            \
                    ASSERT_EQ( *vertex_ptr , k/number_of_repetitions );                                                                         \
                }                                                                                                                               \
            }                                                                                                                                   \
        }                                                                                                                                       \
    }                                                                                                                                           \

#endif //GENERIC_MULTISET_GRAPH_TESTS_H