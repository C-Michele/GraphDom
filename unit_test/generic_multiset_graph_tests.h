#ifndef GENERIC_MULTISET_GRAPH_TESTS_H
#define GENERIC_MULTISET_GRAPH_TESTS_H

#include <utility>
#include <list>
#include <set>
#include <cstddef>

#include "gtest/gtest.h"
#include "graphdom/graph.h"

#define MULTISET_GRAPH_IS_A_MULTISET_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)        \
    TEST(TEST_SUITE_NAME,is_a_multiset_graph) {                                                             \
        CONCRETE_CLASS_NAME graph;                                                                          \
        EXPECT_NE(dynamic_cast< typename graphdom::multiset_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);   \
    }                                                                                                       \

#define MULTISET_GRAPH_IS_NOT_A_SET_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)     \
    TEST(TEST_SUITE_NAME,is_not_a_set_graph) {                                                          \
        CONCRETE_CLASS_NAME graph;                                                                      \
        EXPECT_EQ(dynamic_cast< typename graphdom::set_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);    \
    }                                                                                                   \

#define MULTISET_GRAPH_ORDER_METHOD_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                   \
    TEST(TEST_SUITE_NAME, order_method) {                                                                       \
        CONCRETE_CLASS_NAME graph;                                                                              \
        ASSERT_EQ(graph.order(),0);                                                                             \
        const std::size_t number_of_different_vertex_values = 100;                                              \
        const std::size_t number_of_repetitions = 10;                                                           \
        std::list<typename graphdom::multiset_graph<std::size_t>::vertex_handle> inserted_vertices_handlers;    \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                            \
                inserted_vertices_handlers.emplace_front( graph.insert_vertex(i) );                             \
                ASSERT_EQ(graph.order(),inserted_vertices_handlers.size());                                     \
            }                                                                                                   \
        }                                                                                                       \
        for(std::size_t i = 0; i < number_of_different_vertex_values * number_of_repetitions; ++i) {            \
            graph.erase_vertex( inserted_vertices_handlers.front() );                                           \
            ASSERT_EQ(graph.order(),(number_of_different_vertex_values*number_of_repetitions)-(i+1));           \
            inserted_vertices_handlers.pop_front();                                                             \
        }                                                                                                       \
    }                                                                                                           \

#define MULTISET_GRAPH_ORDER_METHOD_WITH_MOVE_INSERTION_WITHOUT_LABEL_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                             \
    TEST(TEST_SUITE_NAME, order_method_with_move_insertion_without_label) {                                                                 \
        static_assert( std::is_base_of< graphdom::multiset_graph< graphdom_tests::heap_value< std::size_t > > , CONCRETE_CLASS_NAME >() );  \
        CONCRETE_CLASS_NAME graph;                                                                                                          \
        ASSERT_EQ(graph.order(),0);                                                                                                         \
        const std::size_t number_of_different_vertex_values = 100;                                                                          \
        const std::size_t number_of_repetitions = 10;                                                                                       \
        std::list<typename graphdom::multiset_graph< graphdom_tests::heap_value< std::size_t > >::vertex_handle> inserted_vertices_handlers;\
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                        \
                graphdom_tests::heap_value< std::size_t > heap_j( j );                                                                      \
                inserted_vertices_handlers.emplace_front( graph.insert_vertex( std::move( j ) ) );                                          \
                ASSERT_EQ(graph.order(),inserted_vertices_handlers.size());                                                                 \
            }                                                                                                                               \
        }                                                                                                                                   \
        for(std::size_t i = 0; i < number_of_different_vertex_values * number_of_repetitions; ++i) {                                        \
            graph.erase_vertex( inserted_vertices_handlers.front() );                                                                       \
            ASSERT_EQ(graph.order(),(number_of_different_vertex_values*number_of_repetitions)-(i+1));                                       \
            inserted_vertices_handlers.pop_front();                                                                                         \
        }                                                                                                                                   \
    }                                                                                                                                       \

#define MULTISET_GRAPH_CORRECT_VERTEX_SPECIFIC_HANDLE_DEREFERENCING_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)               \
    TEST(TEST_SUITE_NAME, correct_vertex_specific_handle_dereferencing) {                                                   \
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

#define MULTISET_GRAPH_CORRECT_VERTEX_SPECIFIC_HANDLE_DEREFERENCING_AFTER_OTHER_VERTICES_ERASION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)  \
    TEST(TEST_SUITE_NAME, correct_vertex_specific_handle_dereferencing_after_other_vertices_erasion) {                                      \
        CONCRETE_CLASS_NAME graph;                                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                                          \
        const std::size_t number_of_repetitions = 10;                                                                                       \
        typename std::vector<                                                                                                               \
            std::pair<                                                                                                                      \
                typename graphdom::multiset_graph<std::size_t>::vertex_handle,                                                              \
                std::size_t*                                                                                                                \
            >                                                                                                                               \
        > inserted_vertices;                                                                                                                \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                        \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                         \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                         \
            }                                                                                                                               \
        }                                                                                                                                   \
        while( ! inserted_vertices.empty() ) {                                                                                              \
            graph.erase_vertex( ( inserted_vertices.back() ).first );                                                                       \
            inserted_vertices.pop_back();                                                                                                   \
            for(std::size_t k = 0; k<inserted_vertices.size(); ++k) {                                                                       \
                ASSERT_EQ( *( ( inserted_vertices[k] ).first ) , k/number_of_repetitions );                                                 \
                ASSERT_EQ( &( *( ( inserted_vertices[k] ).first ) ) , ( inserted_vertices[k] ).second );                                    \
            }                                                                                                                               \
        }                                                                                                                                   \
    }                                                                                                                                       \

#define MULTISET_GRAPH_CORRECT_CONVERSION_FROM_VERTEX_SPECIFIC_HANDLE_TO_VERTEX_CONST_HANDLE_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME, correct_conversion_from_vertex_specific_handle_to_vertex_const_handle_1) {                                        \
        CONCRETE_CLASS_NAME graph;                                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                                          \
        const std::size_t number_of_repetitions = 10;                                                                                       \
        typename std::vector<                                                                                                               \
            std::pair<                                                                                                                      \
                typename graphdom::multiset_graph<std::size_t>::vertex_handle,                                                              \
                std::size_t*                                                                                                                \
            >                                                                                                                               \
        > inserted_vertices;                                                                                                                \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                        \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                         \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                         \
            }                                                                                                                               \
        }                                                                                                                                   \
        for(std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                        \
            const typename graphdom::graph<std::size_t>::vertex_const_handle vertex_const_handle_k = ( inserted_vertices[k] ).first;        \
            ASSERT_EQ( *vertex_const_handle_k , k/number_of_repetitions );                                                                  \
            for(std::size_t j = 0; j < inserted_vertices.size(); ++j ) {                                                                    \
                if(j==k) {                                                                                                                  \
                    ASSERT_EQ( ( inserted_vertices[j] ).second , &( *( vertex_const_handle_k ) ) );                                         \
                }                                                                                                                           \
                else {                                                                                                                      \
                    ASSERT_NE( ( inserted_vertices[j] ).second , &( *( vertex_const_handle_k ) ) );                                         \
                }                                                                                                                           \
            }                                                                                                                               \
        }                                                                                                                                   \
    }                                                                                                                                       \

#define MULTISET_GRAPH_CORRECT_CONVERSION_FROM_VERTEX_SPECIFIC_HANDLE_TO_VERTEX_GENERIC_HANDLE_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)      \
    TEST(TEST_SUITE_NAME, correct_conversion_from_vertex_specific_handle_to_vertex_generic_handle_1) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                                                              \
        const std::size_t number_of_repetitions = 10;                                                                                           \
        typename std::vector<                                                                                                                   \
            std::pair<                                                                                                                          \
                typename graphdom::multiset_graph<std::size_t>::vertex_handle,                                                                  \
                std::size_t*                                                                                                                    \
            >                                                                                                                                   \
        > inserted_vertices;                                                                                                                    \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                                 \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                            \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                             \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                             \
            }                                                                                                                                   \
        }                                                                                                                                       \
        for(std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                            \
            const typename graphdom::graph<std::size_t>::vertex_handle vertex_handle_k = ( inserted_vertices[k] ).first;                        \
            ASSERT_EQ( *vertex_handle_k , k/number_of_repetitions );                                                                            \
            for(std::size_t j = 0; j < inserted_vertices.size(); ++j ) {                                                                        \
                if(j==k) {                                                                                                                      \
                    ASSERT_EQ( ( inserted_vertices[j] ).second , &( *( vertex_handle_k ) ) );                                                   \
                }                                                                                                                               \
                else {                                                                                                                          \
                    ASSERT_NE( ( inserted_vertices[j] ).second , &( *( vertex_handle_k ) ) );                                                   \
                }                                                                                                                               \
            }                                                                                                                                   \
        }                                                                                                                                       \
    }                                                                                                                                           \

#define MULTISET_GRAPH_CORRECT_CONVERSION_FROM_VERTEX_GENERIC_HANDLE_TO_VERTEX_SPECIFIC_HANDLE_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)  \
    TEST(TEST_SUITE_NAME, correct_conversion_from_vertex_generic_handle_to_vertex_specific_handle_1) {                                      \
        CONCRETE_CLASS_NAME graph;                                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                                          \
        const std::size_t number_of_repetitions = 10;                                                                                       \
        typename std::vector<                                                                                                               \
            std::pair<                                                                                                                      \
                typename graphdom::graph<std::size_t>::vertex_handle,                                                                       \
                const std::size_t*                                                                                                          \
            >                                                                                                                               \
        > inserted_vertices;                                                                                                                \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                        \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                         \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                         \
            }                                                                                                                               \
        }                                                                                                                                   \
        for(std::size_t k = 0; k < inserted_vertices.size(); ++k ) {                                                                        \
            const typename graphdom::multiset_graph<std::size_t>::vertex_handle vertex_handle_k( ( inserted_vertices[k] ).first );          \
            ASSERT_EQ( *vertex_handle_k , k/number_of_repetitions );                                                                        \
            for(std::size_t j = 0; j < inserted_vertices.size(); ++j ) {                                                                    \
                if(j==k) {                                                                                                                  \
                    ASSERT_EQ( ( inserted_vertices[j] ).second , &( *( vertex_handle_k ) ) );                                               \
                }                                                                                                                           \
                else {                                                                                                                      \
                    ASSERT_NE( ( inserted_vertices[j] ).second , &( *( vertex_handle_k ) ) );                                               \
                }                                                                                                                           \
            }                                                                                                                               \
        }                                                                                                                                   \
    }                                                                                                                                       \

#define MULTISET_GRAPH_VERTEX_SPECIFIC_HANDLE_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)       \
    TEST(TEST_SUITE_NAME, vertex_specific_handle_equality_operator) {                                           \
        CONCRETE_CLASS_NAME graph;                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                              \
        const std::size_t number_of_repetitions = 10;                                                           \
        typename std::vector< typename graphdom::multiset_graph<std::size_t>::vertex_handle> inserted_vertices; \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                 \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                   \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                           \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                       \
                const auto last_inserted_vertex = inserted_vertices.back();                                     \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                     \
                    if( k == inserted_vertices.size()-1 ){                                                      \
                        ASSERT_TRUE(inserted_vertices[k] == last_inserted_vertex);                              \
                        ASSERT_TRUE(last_inserted_vertex == inserted_vertices[k]);                              \
                    }                                                                                           \
                    else {                                                                                      \
                        ASSERT_FALSE(inserted_vertices[k] == last_inserted_vertex);                             \
                        ASSERT_FALSE(last_inserted_vertex == inserted_vertices[k]);                             \
                    }                                                                                           \
                }                                                                                               \
            }                                                                                                   \
        }                                                                                                       \
    }                                                                                                           \

#define MULTISET_GRAPH_VERTEX_SPECIFIC_HANDLE_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)     \
    TEST(TEST_SUITE_NAME, vertex_specific_handle_inequality_operator) {                                         \
        CONCRETE_CLASS_NAME graph;                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                              \
        const std::size_t number_of_repetitions = 10;                                                           \
        typename std::vector< typename graphdom::multiset_graph<std::size_t>::vertex_handle> inserted_vertices; \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                 \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                   \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                           \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                       \
                const auto last_inserted_vertex = inserted_vertices.back();                                     \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                     \
                    if( k == inserted_vertices.size()-1 ){                                                      \
                        ASSERT_FALSE(inserted_vertices[k] != last_inserted_vertex);                             \
                        ASSERT_FALSE(last_inserted_vertex != inserted_vertices[k]);                             \
                    }                                                                                           \
                    else {                                                                                      \
                        ASSERT_TRUE(inserted_vertices[k] != last_inserted_vertex);                              \
                        ASSERT_TRUE(last_inserted_vertex != inserted_vertices[k]);                              \
                    }                                                                                           \
                }                                                                                               \
            }                                                                                                   \
        }                                                                                                       \
    }                                                                                                           \

#define MULTISET_GRAPH_VERTEX_HANDLE_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                            \
    TEST(TEST_SUITE_NAME, vertex_handle_equality_operator) {                                                                \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                          \
        const std::size_t number_of_repetitions = 10;                                                                       \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_handle> inserted_vertices;                      \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                               \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                       \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                   \
                const typename graphdom::graph<std::size_t>::vertex_handle last_inserted_vertex = inserted_vertices.back(); \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                 \
                    if( k == inserted_vertices.size()-1 ){                                                                  \
                        ASSERT_TRUE(inserted_vertices[k] == last_inserted_vertex);                                          \
                        ASSERT_TRUE(last_inserted_vertex == inserted_vertices[k]);                                          \
                    }                                                                                                       \
                    else {                                                                                                  \
                        ASSERT_FALSE(inserted_vertices[k] == last_inserted_vertex);                                         \
                        ASSERT_FALSE(last_inserted_vertex == inserted_vertices[k]);                                         \
                    }                                                                                                       \
                }                                                                                                           \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \

#define MULTISET_GRAPH_VERTEX_HANDLE_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                          \
    TEST(TEST_SUITE_NAME, vertex_handle_inequality_operator) {                                                              \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                          \
        const std::size_t number_of_repetitions = 10;                                                                       \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_handle> inserted_vertices;                      \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                               \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                       \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                   \
                const typename graphdom::graph<std::size_t>::vertex_handle last_inserted_vertex = inserted_vertices.back(); \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                 \
                    if( k == inserted_vertices.size()-1 ){                                                                  \
                        ASSERT_FALSE(inserted_vertices[k] != last_inserted_vertex);                                         \
                        ASSERT_FALSE(last_inserted_vertex != inserted_vertices[k]);                                         \
                    }                                                                                                       \
                    else {                                                                                                  \
                        ASSERT_TRUE(inserted_vertices[k] != last_inserted_vertex);                                          \
                        ASSERT_TRUE(last_inserted_vertex != inserted_vertices[k]);                                          \
                    }                                                                                                       \
                }                                                                                                           \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \

#define MULTISET_GRAPH_VERTEX_CONST_HANDLE_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                              \
    TEST(TEST_SUITE_NAME, vertex_const_handle_equality_operator) {                                                                  \
        CONCRETE_CLASS_NAME graph;                                                                                                  \
        const std::size_t number_of_different_vertex_values = 100;                                                                  \
        const std::size_t number_of_repetitions = 10;                                                                               \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_const_handle> inserted_vertices;                        \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                     \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                       \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                               \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                           \
                const typename graphdom::graph<std::size_t>::vertex_const_handle last_inserted_vertex = inserted_vertices.back();   \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                         \
                    if( k == inserted_vertices.size()-1 ){                                                                          \
                        ASSERT_TRUE(inserted_vertices[k] == last_inserted_vertex);                                                  \
                        ASSERT_TRUE(last_inserted_vertex == inserted_vertices[k]);                                                  \
                    }                                                                                                               \
                    else {                                                                                                          \
                        ASSERT_FALSE(inserted_vertices[k] == last_inserted_vertex);                                                 \
                        ASSERT_FALSE(last_inserted_vertex == inserted_vertices[k]);                                                 \
                    }                                                                                                               \
                }                                                                                                                   \
            }                                                                                                                       \
        }                                                                                                                           \
    }                                                                                                                               \

#define MULTISET_GRAPH_VERTEX_CONST_HANDLE_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                            \
    TEST(TEST_SUITE_NAME, vertex_const_handle_inequality_operator) {                                                                \
        CONCRETE_CLASS_NAME graph;                                                                                                  \
        const std::size_t number_of_different_vertex_values = 100;                                                                  \
        const std::size_t number_of_repetitions = 10;                                                                               \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_const_handle> inserted_vertices;                        \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                     \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i ) {                                                       \
            for(std::size_t j = 0; j < number_of_repetitions; ++j ) {                                                               \
                inserted_vertices.emplace_back( graph.insert_vertex(i) );                                                           \
                const typename graphdom::graph<std::size_t>::vertex_const_handle last_inserted_vertex = inserted_vertices.back();   \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k ){                                                         \
                    if( k == inserted_vertices.size()-1 ){                                                                          \
                        ASSERT_FALSE(inserted_vertices[k] != last_inserted_vertex);                                                 \
                        ASSERT_FALSE(last_inserted_vertex != inserted_vertices[k]);                                                 \
                    }                                                                                                               \
                    else {                                                                                                          \
                        ASSERT_TRUE(inserted_vertices[k] != last_inserted_vertex);                                                  \
                        ASSERT_TRUE(last_inserted_vertex != inserted_vertices[k]);                                                  \
                    }                                                                                                               \
                }                                                                                                                   \
            }                                                                                                                       \
        }                                                                                                                           \
    }                                                                                                                               \

#define MULTISET_GRAPH_CORRECT_RETURNED_VERTEX_SPECIFIC_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME) \
    TEST(TEST_SUITE_NAME, correct_returned_vertex_specific_handle_reference_after_assignment) {                                     \
        CONCRETE_CLASS_NAME graph;                                                                                                  \
        const std::size_t number_of_different_vertex_values = 100;                                                                  \
        const std::size_t number_of_repetitions = 10;                                                                               \
        typename std::vector< typename graphdom::multiset_graph<std::size_t>::vertex_handle > inserted_vertices_handles;            \
        inserted_vertices_handles.reserve( number_of_different_vertex_values * number_of_repetitions );                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                        \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                \
                inserted_vertices_handles.emplace_back( graph.insert_vertex(i) );                                                   \
                typename graphdom::multiset_graph<std::size_t>::vertex_handle vertex_handle = inserted_vertices_handles.back();     \
                const typename graphdom::multiset_graph<std::size_t>::vertex_handle* const vertex_handle_address = &vertex_handle;  \
                for(std::size_t k = 0; k < inserted_vertices_handles.size(); ++k )  {                                               \
                    ASSERT_EQ( &( vertex_handle = inserted_vertices_handles[k] ), vertex_handle_address );                          \
                }                                                                                                                   \
            }                                                                                                                       \
        }                                                                                                                           \
    }                                                                                                                               \

#define MULTISET_GRAPH_VERTEX_SPECIFIC_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                       \
    TEST(TEST_SUITE_NAME, specific_vertex_handle_assignment_operator_test_1) {                                                      \
        CONCRETE_CLASS_NAME graph;                                                                                                  \
        const std::size_t number_of_different_vertex_values = 100;                                                                  \
        const std::size_t number_of_repetitions = 10;                                                                               \
        typename std::vector<                                                                                                       \
            std::pair<                                                                                                              \
                typename graphdom::multiset_graph<std::size_t>::vertex_handle,                                                      \
                std::size_t*                                                                                                        \
            >                                                                                                                       \
        > inserted_vertices;                                                                                                        \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                     \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                        \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                                 \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                 \
                typename graphdom::multiset_graph<std::size_t>::vertex_handle vertex_handle = ( inserted_vertices.back() ).first;   \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                       \
                    vertex_handle = ( inserted_vertices[k] ).first;                                                                 \
                    ASSERT_EQ( vertex_handle , ( inserted_vertices[k] ).first );                                                    \
                    ASSERT_EQ( &( *vertex_handle ) , ( inserted_vertices[k] ).second );                                             \
                    ASSERT_EQ( *vertex_handle , k/number_of_repetitions );                                                          \
                }                                                                                                                   \
            }                                                                                                                       \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define MULTISET_GRAPH_CORRECT_RETURNED_VERTEX_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)  \
    TEST(TEST_SUITE_NAME, correct_returned_vertex_handle_reference_after_assignment) {                                      \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                          \
        const std::size_t number_of_repetitions = 10;                                                                       \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_handle > inserted_vertices_handles;             \
        inserted_vertices_handles.reserve( number_of_different_vertex_values * number_of_repetitions );                     \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                        \
                inserted_vertices_handles.emplace_back( graph.insert_vertex(i) );                                           \
                typename graphdom::graph<std::size_t>::vertex_handle vertex_handle = inserted_vertices_handles.back();      \
                const typename graphdom::graph<std::size_t>::vertex_handle* const vertex_handle_address = &vertex_handle;   \
                for(std::size_t k = 0; k < inserted_vertices_handles.size(); ++k )  {                                       \
                    ASSERT_EQ( &( vertex_handle = inserted_vertices_handles[k] ), vertex_handle_address );                  \
                }                                                                                                           \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \

#define MULTISET_GRAPH_VERTEX_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                        \
    TEST(TEST_SUITE_NAME, vertex_handle_assignment_operator_test_1) {                                                       \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        const std::size_t number_of_different_vertex_values = 100;                                                          \
        const std::size_t number_of_repetitions = 10;                                                                       \
        typename std::vector<                                                                                               \
            std::pair<                                                                                                      \
                typename graphdom::graph<std::size_t>::vertex_handle,                                                       \
                const std::size_t*                                                                                          \
            >                                                                                                               \
        > inserted_vertices;                                                                                                \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                        \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                         \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                         \
                typename graphdom::graph<std::size_t>::vertex_handle vertex_handle = ( inserted_vertices.back() ).first;    \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                               \
                    vertex_handle = ( inserted_vertices[k] ).first;                                                         \
                    ASSERT_EQ( vertex_handle , ( inserted_vertices[k] ).first );                                            \
                    ASSERT_EQ( &( *vertex_handle ) , ( inserted_vertices[k] ).second );                                     \
                    ASSERT_EQ( *vertex_handle , k/number_of_repetitions );                                                  \
                }                                                                                                           \
            }                                                                                                               \
        }                                                                                                                   \
    }                                                                                                                       \

#define MULTISET_GRAPH_CORRECT_RETURNED_VERTEX_CONST_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME, correct_returned_vertex_const_handle_reference_after_assignment) {                                        \
        CONCRETE_CLASS_NAME graph;                                                                                                  \
        const std::size_t number_of_different_vertex_values = 100;                                                                  \
        const std::size_t number_of_repetitions = 10;                                                                               \
        typename std::vector< typename graphdom::graph<std::size_t>::vertex_const_handle > inserted_vertices_handles;               \
        inserted_vertices_handles.reserve( number_of_different_vertex_values * number_of_repetitions );                             \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                        \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                \
                inserted_vertices_handles.emplace_back( graph.insert_vertex(i) );                                                   \
                typename graphdom::graph<std::size_t>::vertex_const_handle vertex_handle = inserted_vertices_handles.back();        \
                const typename graphdom::graph<std::size_t>::vertex_const_handle* const vertex_handle_address = &vertex_handle;     \
                for(std::size_t k = 0; k < inserted_vertices_handles.size(); ++k )  {                                               \
                    ASSERT_EQ( &( vertex_handle = inserted_vertices_handles[k] ), vertex_handle_address );                          \
                }                                                                                                                   \
            }                                                                                                                       \
        }                                                                                                                           \
    }                                                                                                                               \

#define MULTISET_GRAPH_VERTEX_CONST_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                      \
    TEST(TEST_SUITE_NAME, vertex_const_handle_assignment_operator_test_1) {                                                     \
        CONCRETE_CLASS_NAME graph;                                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                                              \
        const std::size_t number_of_repetitions = 10;                                                                           \
        typename std::vector<                                                                                                   \
            std::pair<                                                                                                          \
                typename graphdom::graph<std::size_t>::vertex_const_handle,                                                     \
                const std::size_t*                                                                                              \
            >                                                                                                                   \
        > inserted_vertices;                                                                                                    \
        inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );                                 \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                            \
                inserted_vertices.emplace_back( graph.insert_vertex(i) , nullptr );                                             \
                ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                             \
                typename graphdom::graph<std::size_t>::vertex_const_handle vertex_handle = ( inserted_vertices.back() ).first;  \
                for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                   \
                    vertex_handle = ( inserted_vertices[k] ).first;                                                             \
                    ASSERT_EQ( vertex_handle , ( inserted_vertices[k] ).first );                                                \
                    ASSERT_EQ( &( *vertex_handle ) , ( inserted_vertices[k] ).second );                                         \
                    ASSERT_EQ( *vertex_handle , k/number_of_repetitions );                                                      \
                }                                                                                                               \
            }                                                                                                                   \
        }                                                                                                                       \
    }                                                                                                                           \

#endif //GENERIC_MULTISET_GRAPH_TESTS_H