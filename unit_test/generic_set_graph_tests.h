#ifndef GENERIC_SET_GRAPH_TESTS_H
#define GENERIC_SET_GRAPH_TESTS_H

#include <utility>
#include <forward_list>
#include <vector>
#include <type_traits>
#include <cstddef>
#include <exception>

#include "gtest/gtest.h"
#include "graphdom_tests_utility.h"
#include "graphdom/graph.h"

#define SET_GRAPH_IS_A_SET_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)              \
    TEST(TEST_SUITE_NAME,is_a_set_graph) {                                                              \
        CONCRETE_CLASS_NAME graph;                                                                      \
        EXPECT_NE(dynamic_cast< typename graphdom::set_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);    \
    }                                                                                                   \

#define SET_GRAPH_IS_NOT_A_MULTISET_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)         \
    TEST(TEST_SUITE_NAME,is_not_a_multiset_graph) {                                                         \
        CONCRETE_CLASS_NAME graph;                                                                          \
        EXPECT_EQ(dynamic_cast< typename graphdom::multiset_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);   \
    }                                                                                                       \

#define SET_GRAPH_ORDER_METHOD_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                    \
    TEST(TEST_SUITE_NAME, order_method) {                                                                   \
        CONCRETE_CLASS_NAME graph;                                                                          \
        ASSERT_EQ(graph.order(),0);                                                                         \
        const std::size_t number_of_vertices = 100;                                                         \
        std::forward_list<typename graphdom::graph<std::size_t>::vertex_handle> inserted_vertices_handles;  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                               \
            inserted_vertices_handles.emplace_front( ( graph.insert_vertex(i) ).first );                    \
            ASSERT_EQ(graph.order(),i+1);                                                                   \
            for(std::size_t j = 0; j <= i; ++j) {                                                           \
                const auto insertion_result = graph.insert_vertex(j);                                       \
                ASSERT_EQ(graph.order(),i+1);                                                               \
            }                                                                                               \
        }                                                                                                   \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                               \
            graph.erase_vertex( inserted_vertices_handles.front() );                                        \
            ASSERT_EQ(graph.order(),number_of_vertices-(i+1));                                              \
            inserted_vertices_handles.pop_front();                                                          \
        }                                                                                                   \
    }                                                                                                       \

#define SET_GRAPH_CORRECT_RETURNED_BOOLEAN_AFTER_VERTEX_INSERTION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME) \
    TEST(TEST_SUITE_NAME, correct_returned_boolean_after_vertex_insertion) {                                \
        CONCRETE_CLASS_NAME graph;                                                                          \
        const std::size_t number_of_vertices = 100;                                                         \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                               \
            ASSERT_TRUE( ( graph.insert_vertex(i) ).second );                                               \
            for(std::size_t j = 0; j <= i; ++j) {                                                           \
                ASSERT_FALSE( ( graph.insert_vertex(j) ).second );                                          \
            }                                                                                               \
        }                                                                                                   \
    }                                                                                                       \

#define SET_GRAPH_CORRECT_RETURNED_BOOLEAN_AFTER_VERTEX_MOVE_INSERTION_WITHOUT_LABEL_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)          \
    TEST(TEST_SUITE_NAME, correct_returned_boolean_after_vertex_move_insertion_without_label) {                                         \
        static_assert( std::is_base_of< graphdom::set_graph< graphdom_tests::heap_value< std::size_t > > , CONCRETE_CLASS_NAME >() );   \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                                     \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                           \
            graphdom_tests::heap_value< std::size_t > heap_i(i);                                                                        \
            ASSERT_TRUE( ( graph.insert_vertex( std::move( heap_i ) ) ).second );                                                       \
            for(std::size_t j = 0; j <= i; ++j) {                                                                                       \
                graphdom_tests::heap_value< std::size_t > heap_j(j);                                                                    \
                ASSERT_FALSE( ( graph.insert_vertex( std::move( heap_j ) ) ).second );                                                  \
            }                                                                                                                           \
        }                                                                                                                               \
    }                                                                                                                                   \

#define SET_GRAPH_INVALIDATED_SOURCE_AFTER_SUCCESSFUL_VERTEX_MOVE_INSERTION_WITHOUT_LABEL_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)     \
    TEST(TEST_SUITE_NAME, invalidated_source_after_successful_vertex_move_insertion_without_label) {                                    \
        static_assert( std::is_base_of< graphdom::set_graph< graphdom_tests::heap_value< std::size_t > > , CONCRETE_CLASS_NAME >() );   \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                                     \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                           \
            graphdom_tests::heap_value< std::size_t > heap_i(i);                                                                        \
            const auto* const before_ptr = heap_i.get_as_pointer();                                                                     \
            EXPECT_NE( before_ptr , nullptr );                                                                                          \
            EXPECT_EQ( heap_i.get_as_reference() , i );                                                                                 \
            const auto insertion_i_result = graph.insert_vertex( std::move( heap_i ) );                                                 \
            ASSERT_EQ( heap_i.get_as_pointer() , nullptr );                                                                             \
            ASSERT_EQ( ( *( insertion_i_result.first ) ).get_as_pointer() , before_ptr );                                               \
            ASSERT_EQ( ( *( insertion_i_result.first ) ).get_as_reference() , i );                                                      \
        }                                                                                                                               \
    }                                                                                                                                   \

#define SET_GRAPH_NOT_INVALIDATED_SOURCE_AFTER_UNSUCCESSFUL_VERTEX_MOVE_INSERTION_WITHOUT_LABEL_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)   \
    TEST(TEST_SUITE_NAME, not_invalidated_source_after_unsuccessful_vertex_move_insertion_without_label) {                                  \
        static_assert( std::is_base_of< graphdom::set_graph< graphdom_tests::heap_value< std::size_t > > , CONCRETE_CLASS_NAME >() );       \
        CONCRETE_CLASS_NAME graph;                                                                                                          \
        const std::size_t number_of_vertices = 100;                                                                                         \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                               \
            graphdom_tests::heap_value< std::size_t > heap_i(i);                                                                            \
            graph.insert_vertex( std::move( heap_i ) );                                                                                     \
            for(std::size_t j = 0; j <= i; ++j) {                                                                                           \
                graphdom_tests::heap_value< std::size_t > heap_j(j);                                                                        \
                const auto* const before_ptr = heap_j.get_as_pointer();                                                                     \
                EXPECT_NE( before_ptr , nullptr );                                                                                          \
                EXPECT_EQ( heap_j.get_as_reference() , j );                                                                                 \
                const auto insertion_j_result = graph.insert_vertex( std::move( heap_j ) );                                                 \
                ASSERT_EQ( heap_j.get_as_pointer() , before_ptr );                                                                          \
                ASSERT_EQ( heap_j.get_as_reference() , j );                                                                                 \
            }                                                                                                                               \
        }                                                                                                                                   \
    }                                                                                                                                       \

#define SET_GRAPH_CORRECT_VERTEX_HANDLE_DEREFERENCING_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                         \
    TEST(TEST_SUITE_NAME, correct_vertex_handle_dereferencing) {                                                        \
        CONCRETE_CLASS_NAME graph;                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                     \
        typename std::vector<const std::size_t*> inserted_vertices_raw_pointers;                                        \
        inserted_vertices_raw_pointers.reserve(number_of_vertices);                                                     \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                           \
            inserted_vertices_raw_pointers.emplace_back( &( *( ( graph.insert_vertex(i) ).first ) ) );                  \
            ASSERT_EQ( *( inserted_vertices_raw_pointers.back() ) , i );                                                \
            for(std::size_t j = 0; j <= i; ++j) {                                                                       \
                const std::size_t* const inserted_vertex_j_raw_pointer = &( *( ( graph.insert_vertex(j) ).first ) );    \
                for(std::size_t k = 0; k<inserted_vertices_raw_pointers.size(); ++k) {                                  \
                    ASSERT_EQ( *( inserted_vertices_raw_pointers[k] ) , k );                                            \
                    if(k==j){                                                                                           \
                        ASSERT_EQ( inserted_vertices_raw_pointers[k] , inserted_vertex_j_raw_pointer );                 \
                    }                                                                                                   \
                    else {                                                                                              \
                        ASSERT_NE( inserted_vertices_raw_pointers[k] , inserted_vertex_j_raw_pointer );                 \
                    }                                                                                                   \
                }                                                                                                       \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \

#define SET_GRAPH_CORRECT_VERTEX_HANDLE_DEREFERENCING_AFTER_OTHER_VERTICES_ERASION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME, correct_vertex_handle_dereferencing_after_other_vertices_erasion) {                                   \
        CONCRETE_CLASS_NAME graph;                                                                                              \
        const std::size_t number_of_vertices = 100;                                                                             \
        typename std::vector<                                                                                                   \
            std::pair<                                                                                                          \
                typename graphdom::graph<std::size_t>::vertex_handle,                                                           \
                const std::size_t*                                                                                              \
            >                                                                                                                   \
        > inserted_vertices;                                                                                                    \
        inserted_vertices.reserve(number_of_vertices);                                                                          \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                   \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                       \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                 \
        }                                                                                                                       \
        while( ! inserted_vertices.empty() ) {                                                                                  \
            graph.erase_vertex( ( inserted_vertices.back() ).first );                                                           \
            inserted_vertices.pop_back();                                                                                       \
            for(std::size_t k = 0; k<inserted_vertices.size(); ++k) {                                                           \
                ASSERT_EQ( *( ( inserted_vertices[k] ).first ) , k );                                                           \
                ASSERT_EQ( &( *( ( inserted_vertices[k] ).first ) ) , ( inserted_vertices[k] ).second );                        \
            }                                                                                                                   \
        }                                                                                                                       \
    }                                                                                                                           \

#define SET_GRAPH_CORRECT_VERTEX_CONST_HANDLE_CONVERSION_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                    \
    TEST(TEST_SUITE_NAME, correct_vertex_const_handle_conversion_1) {                                                                   \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                                     \
        typename std::vector<                                                                                                           \
            std::pair<                                                                                                                  \
                typename graphdom::graph<std::size_t>::vertex_handle,                                                                   \
                const std::size_t*                                                                                                      \
            >                                                                                                                           \
        > inserted_vertices;                                                                                                            \
        inserted_vertices.reserve(number_of_vertices);                                                                                  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                           \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                               \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                         \
        }                                                                                                                               \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                           \
            const typename graphdom::graph<std::size_t>::vertex_const_handle vertex_const_handle_i = ( inserted_vertices[i] ).first;    \
            ASSERT_EQ( *( vertex_const_handle_i ) , i );                                                                                \
            for(std::size_t k = 0; k < number_of_vertices; ++k) {                                                                       \
                if(k==i){                                                                                                               \
                    ASSERT_EQ( ( inserted_vertices[k] ).second , &( *( vertex_const_handle_i ) ) );                                     \
                }                                                                                                                       \
                else {                                                                                                                  \
                    ASSERT_NE( ( inserted_vertices[k] ).second , &( *( vertex_const_handle_i ) ) );                                     \
                }                                                                                                                       \
            }                                                                                                                           \
        }                                                                                                                               \
    }                                                                                                                                   \

#define SET_GRAPH_VERTEX_HANDLE_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)             \
    TEST(TEST_SUITE_NAME, vertex_handle_equality_operator) {                                            \
        CONCRETE_CLASS_NAME graph;                                                                      \
        const std::size_t number_of_vertices = 100;                                                     \
        std::vector<typename graphdom::graph<std::size_t>::vertex_handle> inserted_vertices_handles;    \
        inserted_vertices_handles.reserve(number_of_vertices);                                          \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                           \
            inserted_vertices_handles.emplace_back( ( graph.insert_vertex(i) ).first );                 \
            for(std::size_t j = 0; j <= i; ++j) {                                                       \
                const auto insertion_result_j = graph.insert_vertex(j);                                 \
                for(std::size_t k = 0; k<inserted_vertices_handles.size(); ++k) {                       \
                    if(k==j) {                                                                          \
                        ASSERT_TRUE(inserted_vertices_handles[k] == insertion_result_j.first);          \
                        ASSERT_TRUE(insertion_result_j.first == inserted_vertices_handles[k]);          \
                    }                                                                                   \
                    else {                                                                              \
                        ASSERT_FALSE(inserted_vertices_handles[k] == insertion_result_j.first);         \
                        ASSERT_FALSE(insertion_result_j.first == inserted_vertices_handles[k]);         \
                    }                                                                                   \
                }                                                                                       \
            }                                                                                           \
        }                                                                                               \
    }                                                                                                   \

#define SET_GRAPH_VERTEX_HANDLE_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)           \
    TEST(TEST_SUITE_NAME, vertex_handle_inequality_operator) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                      \
        const std::size_t number_of_vertices = 100;                                                     \
        std::vector<typename graphdom::graph<std::size_t>::vertex_handle> inserted_vertices_handles;    \
        inserted_vertices_handles.reserve(number_of_vertices);                                          \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                           \
            inserted_vertices_handles.emplace_back( ( graph.insert_vertex(i) ).first );                 \
            for(std::size_t j = 0; j <= i; ++j) {                                                       \
                const auto insertion_result_j = graph.insert_vertex(j);                                 \
                for(std::size_t k = 0; k<inserted_vertices_handles.size(); ++k) {                       \
                    if(k==j) {                                                                          \
                        ASSERT_FALSE(inserted_vertices_handles[k] != insertion_result_j.first);         \
                        ASSERT_FALSE(insertion_result_j.first != inserted_vertices_handles[k]);         \
                    }                                                                                   \
                    else {                                                                              \
                        ASSERT_TRUE(inserted_vertices_handles[k] != insertion_result_j.first);          \
                        ASSERT_TRUE(insertion_result_j.first != inserted_vertices_handles[k]);          \
                    }                                                                                   \
                }                                                                                       \
            }                                                                                           \
        }                                                                                               \
    }                                                                                                   \

#define SET_GRAPH_VERTEX_CONST_HANDLE_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                   \
    TEST(TEST_SUITE_NAME, vertex_const_handle_equality_operator) {                                                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                                                  \
        const std::size_t number_of_vertices = 100;                                                                                                 \
        std::vector<typename graphdom::graph<std::size_t>::vertex_const_handle> inserted_vertices_handles;                                          \
        inserted_vertices_handles.reserve(number_of_vertices);                                                                                      \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                       \
            inserted_vertices_handles.emplace_back( ( graph.insert_vertex(i) ).first );                                                             \
            for(std::size_t j = 0; j <= i; ++j) {                                                                                                   \
                const graphdom::graph<std::size_t>::vertex_const_handle insertion_const_vertex_j_handle_result = ( graph.insert_vertex(j) ).first;  \
                for(std::size_t k = 0; k<inserted_vertices_handles.size(); ++k) {                                                                   \
                    if(k==j) {                                                                                                                      \
                        ASSERT_TRUE(inserted_vertices_handles[k] == insertion_const_vertex_j_handle_result);                                        \
                        ASSERT_TRUE(insertion_const_vertex_j_handle_result == inserted_vertices_handles[k]);                                        \
                    }                                                                                                                               \
                    else {                                                                                                                          \
                        ASSERT_FALSE(inserted_vertices_handles[k] == insertion_const_vertex_j_handle_result);                                       \
                        ASSERT_FALSE(insertion_const_vertex_j_handle_result == inserted_vertices_handles[k]);                                       \
                    }                                                                                                                               \
                }                                                                                                                                   \
            }                                                                                                                                       \
        }                                                                                                                                           \
    }                                                                                                                                               \

#define SET_GRAPH_VERTEX_CONST_HANDLE_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                 \
    TEST(TEST_SUITE_NAME, vertex_const_handle_inequality_operator) {                                                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                                  \
        const std::size_t number_of_vertices = 100;                                                                                                 \
        std::vector<typename graphdom::graph<std::size_t>::vertex_const_handle> inserted_vertices_handles;                                          \
        inserted_vertices_handles.reserve(number_of_vertices);                                                                                      \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                       \
            inserted_vertices_handles.emplace_back( ( graph.insert_vertex(i) ).first );                                                             \
            for(std::size_t j = 0; j <= i; ++j) {                                                                                                   \
                const graphdom::graph<std::size_t>::vertex_const_handle insertion_const_vertex_j_handle_result = ( graph.insert_vertex(j) ).first;  \
                for(std::size_t k = 0; k<inserted_vertices_handles.size(); ++k) {                                                                   \
                    if(k==j) {                                                                                                                      \
                        ASSERT_FALSE(inserted_vertices_handles[k] != insertion_const_vertex_j_handle_result);                                       \
                        ASSERT_FALSE(insertion_const_vertex_j_handle_result != inserted_vertices_handles[k]);                                       \
                    }                                                                                                                               \
                    else {                                                                                                                          \
                        ASSERT_TRUE(inserted_vertices_handles[k] != insertion_const_vertex_j_handle_result);                                        \
                        ASSERT_TRUE(insertion_const_vertex_j_handle_result != inserted_vertices_handles[k]);                                        \
                    }                                                                                                                               \
                }                                                                                                                                   \
            }                                                                                                                                       \
        }                                                                                                                                           \
    }                                                                                                                                               \

#define SET_GRAPH_CORRECT_RETURNED_VERTEX_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)   \
    TEST(TEST_SUITE_NAME, correct_returned_vertex_handle_reference_after_assignment) {                                  \
        CONCRETE_CLASS_NAME graph;                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                     \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_handle > inserted_vertices_handles;         \
        inserted_vertices_handles.reserve(number_of_vertices);                                                          \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                           \
            inserted_vertices_handles.emplace_back( ( graph.insert_vertex(i) ).first );                                 \
            typename graphdom::graph<std::size_t>::vertex_handle vertex_handle = inserted_vertices_handles.back();      \
            const typename graphdom::graph<std::size_t>::vertex_handle* const vertex_handle_address = &vertex_handle;   \
            for(std::size_t k = 0; k < inserted_vertices_handles.size(); ++k )  {                                       \
                ASSERT_EQ( &( vertex_handle = inserted_vertices_handles[k] ), vertex_handle_address );                  \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \

#define SET_GRAPH_VERTEX_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                         \
    TEST(TEST_SUITE_NAME, vertex_handle_assignment_operator_test_1) {                                                   \
        CONCRETE_CLASS_NAME graph;                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                     \
        typename std::vector<                                                                                           \
            std::pair<                                                                                                  \
                typename graphdom::graph<std::size_t>::vertex_handle,                                                   \
                const std::size_t*                                                                                      \
            >                                                                                                           \
        > inserted_vertices;                                                                                            \
        inserted_vertices.reserve(number_of_vertices);                                                                  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                           \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                               \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                         \
            typename graphdom::graph<std::size_t>::vertex_handle vertex_handle = ( inserted_vertices.back() ).first;    \
            for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                               \
                vertex_handle = ( inserted_vertices[k] ).first;                                                         \
                ASSERT_EQ( vertex_handle , ( inserted_vertices[k] ).first );                                            \
                ASSERT_EQ( &( *vertex_handle ) , ( inserted_vertices[k] ).second );                                     \
                ASSERT_EQ( *vertex_handle , k );                                                                        \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \

#define SET_GRAPH_CORRECT_RETURNED_VERTEX_CONST_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME) \
    TEST(TEST_SUITE_NAME, correct_returned_vertex_const_handle_reference_after_assignment) {                                \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        const std::size_t number_of_vertices = 100;                                                                         \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_const_handle > inserted_vertices_handles;       \
        inserted_vertices_handles.reserve(number_of_vertices);                                                              \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                               \
            inserted_vertices_handles.emplace_back( ( graph.insert_vertex(i) ).first );                                     \
            typename graphdom::graph<std::size_t>::vertex_const_handle vertex_handle = inserted_vertices_handles.back();    \
            const typename graphdom::graph<std::size_t>::vertex_const_handle* const vertex_handle_address = &vertex_handle; \
            for(std::size_t k = 0; k < inserted_vertices_handles.size(); ++k )  {                                           \
                ASSERT_EQ( &( vertex_handle = inserted_vertices_handles[k] ), vertex_handle_address );                      \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \

#define SET_GRAPH_VERTEX_CONST_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                       \
    TEST(TEST_SUITE_NAME, vertex_const_handle_assignment_operator_test_1) {                                                 \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        const std::size_t number_of_vertices = 100;                                                                         \
        typename std::vector<                                                                                               \
            std::pair<                                                                                                      \
                typename graphdom::graph<std::size_t>::vertex_const_handle,                                                 \
                const std::size_t*                                                                                          \
            >                                                                                                               \
        > inserted_vertices;                                                                                                \
        inserted_vertices.reserve(number_of_vertices);                                                                      \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                               \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                   \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                             \
            typename graphdom::graph<std::size_t>::vertex_const_handle vertex_handle = ( inserted_vertices.back() ).first;  \
            for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                   \
                vertex_handle = ( inserted_vertices[k] ).first;                                                             \
                ASSERT_EQ( vertex_handle , ( inserted_vertices[k] ).first );                                                \
                ASSERT_EQ( &( *vertex_handle ) , ( inserted_vertices[k] ).second );                                         \
                ASSERT_EQ( *vertex_handle , k );                                                                            \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \

#define SET_GRAPH_UNABLE_TO_CONVERT_A_VERTEX_HANDLE_TO_MULTISET_VERTEX_HANDLE_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                                                                                                                        \
    TEST(TEST_SUITE_NAME, unable_to_convert_a_vertex_handle_to_multiset_vertex_handle) {                                                                                                                                                                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                                                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                                                                                                                                                                                     \
        typename std::vector<                                                                                                                                                                                                                                                           \
            std::pair<                                                                                                                                                                                                                                                                  \
                typename graphdom::graph<std::size_t>::vertex_handle,                                                                                                                                                                                                     \
                const std::size_t*                                                                                                                                                                                                                                                      \
            >                                                                                                                                                                                                                                                                           \
        > inserted_vertices;                                                                                                                                                                                                                                                            \
        inserted_vertices.reserve(number_of_vertices);                                                                                                                                                                                                                                  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                                                                                                                                                           \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                                                                                                                                                                               \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                                                                                                                                                         \
        }                                                                                                                                                                                                                                                                               \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                                                                                                                                                           \
            ASSERT_THROW(const typename graphdom::multiset_graph<std::size_t>::vertex_handle multiset_vertex_ptr_i = static_cast<graphdom::multiset_graph<std::size_t>::vertex_handle>(( inserted_vertices[i] ).first), std::exception);      \
        }                                                                                                                                                                                                                                                                               \
    }                                                                                                                                                                                                                                                                                   \

#endif //GENERIC_SET_GRAPH_TESTS_H