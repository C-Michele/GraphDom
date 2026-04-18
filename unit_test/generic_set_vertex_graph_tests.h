#ifndef GENERIC_SET_VERTEX_GRAPH_TESTS_H
#define GENERIC_SET_VERTEX_GRAPH_TESTS_H

#include <utility>
#include <forward_list>
#include <vector>
#include <cstddef>
#include <exception>

#include "gtest/gtest.h"
#include "graphlab/graph.h"

#define SET_VERTEX_GRAPH_IS_A_SET_VERTEX_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                    \
    TEST(TEST_SUITE_NAME,is_a_set_vertex_graph) {                                                                           \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        EXPECT_NE(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);   \
    }                                                                                                                       \

#define SET_VERTEX_GRAPH_IS_NOT_A_MULTISET_VERTEX_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)               \
    TEST(TEST_SUITE_NAME,is_not_a_multiset_vertex_graph) {                                                                      \
        CONCRETE_CLASS_NAME graph;                                                                                              \
        EXPECT_EQ(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);  \
    }                                                                                                                           \

#define SET_VERTEX_GRAPH_ORDER_METHOD_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                             \
    TEST(TEST_SUITE_NAME, order_method) {                                                                                   \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        ASSERT_EQ(graph.order(),0);                                                                                         \
        const std::size_t number_of_vertices = 100;                                                                         \
        std::forward_list<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle> inserted_vertices_pointers;   \
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

#define SET_VERTEX_GRAPH_CORRECT_VERTEX_POINTER_DEREFERENCING_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                 \
    TEST(TEST_SUITE_NAME, correct_vertex_pointer_dereferencing) {                                                       \
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

#define SET_VERTEX_GRAPH_CORRECT_VERTEX_POINTER_DEREFERENCING_AFTER_OTHER_VERTICES_ERASION_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)    \
    TEST(TEST_SUITE_NAME, correct_vertex_pointer_dereferencing_after_other_vertices_erasion) {                                          \
        CONCRETE_CLASS_NAME graph;                                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                                     \
        typename std::vector<                                                                                                           \
            std::pair<                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                     \
                const std::size_t*                                                                                                      \
            >                                                                                                                           \
        > inserted_vertices;                                                                                                            \
        inserted_vertices.reserve(number_of_vertices);                                                                                  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                           \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                               \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                         \
        }                                                                                                                               \
        while( ! inserted_vertices.empty() ) {                                                                                          \
            graph.erase_vertex( ( inserted_vertices.back() ).first );                                                                   \
            inserted_vertices.pop_back();                                                                                               \
            for(std::size_t k = 0; k<inserted_vertices.size(); ++k) {                                                                   \
                ASSERT_EQ( *( ( inserted_vertices[k] ).first ) , k );                                                                   \
                ASSERT_EQ( &( *( ( inserted_vertices[k] ).first ) ) , ( inserted_vertices[k] ).second );                                \
            }                                                                                                                           \
        }                                                                                                                               \
    }                                                                                                                                   \

#define SET_VERTEX_GRAPH_CORRECT_CONSTANT_VERTEX_POINTER_CONVERSION_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                         \
    TEST(TEST_SUITE_NAME, correct_constant_vertex_pointer_conversion_1) {                                                                               \
        CONCRETE_CLASS_NAME graph;                                                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                                                     \
        typename std::vector<                                                                                                                           \
            std::pair<                                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                     \
                const std::size_t*                                                                                                                      \
            >                                                                                                                                           \
        > inserted_vertices;                                                                                                                            \
        inserted_vertices.reserve(number_of_vertices);                                                                                                  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                           \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                                               \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                         \
        }                                                                                                                                               \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                           \
            const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME const_vertex_ptr_i = ( inserted_vertices[i] ).first;    \
            ASSERT_EQ( *( const_vertex_ptr_i ) , i );                                                                                                   \
            for(std::size_t k = 0; k < number_of_vertices; ++k) {                                                                                       \
                if(k==i){                                                                                                                               \
                    ASSERT_EQ( ( inserted_vertices[k] ).second , &( *( const_vertex_ptr_i ) ) );                                                        \
                }                                                                                                                                       \
                else {                                                                                                                                  \
                    ASSERT_NE( ( inserted_vertices[k] ).second , &( *( const_vertex_ptr_i ) ) );                                                        \
                }                                                                                                                                       \
            }                                                                                                                                           \
        }                                                                                                                                               \
    }                                                                                                                                                   \

#define SET_VERTEX_GRAPH_VERTEX_POINTER_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                     \
    TEST(TEST_SUITE_NAME, vertex_pointer_equality_operator) {                                                           \
        CONCRETE_CLASS_NAME graph;                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                     \
        std::vector<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle> inserted_vertices_pointers;     \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                         \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                           \
            inserted_vertices_pointers.emplace_back( ( graph.insert_vertex(i) ).first );                                \
            for(std::size_t j = 0; j <= i; ++j) {                                                                       \
                const auto insertion_result_j = graph.insert_vertex(j);                                                 \
                for(std::size_t k = 0; k<inserted_vertices_pointers.size(); ++k) {                                      \
                    if(k==j) {                                                                                          \
                        ASSERT_TRUE(inserted_vertices_pointers[k] == insertion_result_j.first);                         \
                        ASSERT_TRUE(insertion_result_j.first == inserted_vertices_pointers[k]);                         \
                    }                                                                                                   \
                    else {                                                                                              \
                        ASSERT_FALSE(inserted_vertices_pointers[k] == insertion_result_j.first);                        \
                        ASSERT_FALSE(insertion_result_j.first == inserted_vertices_pointers[k]);                        \
                    }                                                                                                   \
                }                                                                                                       \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \

#define SET_VERTEX_GRAPH_VERTEX_POINTER_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                   \
    TEST(TEST_SUITE_NAME, vertex_pointer_inequality_operator) {                                                         \
        CONCRETE_CLASS_NAME graph;                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                     \
        std::vector<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle> inserted_vertices_pointers;     \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                         \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                           \
            inserted_vertices_pointers.emplace_back( ( graph.insert_vertex(i) ).first );                                \
            for(std::size_t j = 0; j <= i; ++j) {                                                                       \
                const auto insertion_result_j = graph.insert_vertex(j);                                                 \
                for(std::size_t k = 0; k<inserted_vertices_pointers.size(); ++k) {                                      \
                    if(k==j) {                                                                                          \
                        ASSERT_FALSE(inserted_vertices_pointers[k] != insertion_result_j.first);                        \
                        ASSERT_FALSE(insertion_result_j.first != inserted_vertices_pointers[k]);                        \
                    }                                                                                                   \
                    else {                                                                                              \
                        ASSERT_TRUE(inserted_vertices_pointers[k] != insertion_result_j.first);                         \
                        ASSERT_TRUE(insertion_result_j.first != inserted_vertices_pointers[k]);                         \
                    }                                                                                                   \
                }                                                                                                       \
            }                                                                                                           \
        }                                                                                                               \
    }                                                                                                                   \

#define SET_VERTEX_GRAPH_CONSTANT_VERTEX_POINTER_EQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                        \
    TEST(TEST_SUITE_NAME, constant_vertex_pointer_equality_operator) {                                                                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                                  \
        const std::size_t number_of_vertices = 100;                                                                                                                 \
        std::vector<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME> inserted_vertices_pointers;                                      \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                                                                     \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                                       \
            inserted_vertices_pointers.emplace_back( ( graph.insert_vertex(i) ).first );                                                                            \
            for(std::size_t j = 0; j <= i; ++j) {                                                                                                                   \
                const MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME insertion_const_vertex_j_ptr_result = ( graph.insert_vertex(j) ).first;  \
                for(std::size_t k = 0; k<inserted_vertices_pointers.size(); ++k) {                                                                                  \
                    if(k==j) {                                                                                                                                      \
                        ASSERT_TRUE(inserted_vertices_pointers[k] == insertion_const_vertex_j_ptr_result);                                                          \
                        ASSERT_TRUE(insertion_const_vertex_j_ptr_result == inserted_vertices_pointers[k]);                                                          \
                    }                                                                                                                                               \
                    else {                                                                                                                                          \
                        ASSERT_FALSE(inserted_vertices_pointers[k] == insertion_const_vertex_j_ptr_result);                                                         \
                        ASSERT_FALSE(insertion_const_vertex_j_ptr_result == inserted_vertices_pointers[k]);                                                         \
                    }                                                                                                                                               \
                }                                                                                                                                                   \
            }                                                                                                                                                       \
        }                                                                                                                                                           \
    }                                                                                                                                                               \

#define SET_VERTEX_GRAPH_CONSTANT_VERTEX_POINTER_INEQUALITY_OPERATOR_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                      \
    TEST(TEST_SUITE_NAME, constant_vertex_pointer_inequality_operator) {                                                                                            \
        CONCRETE_CLASS_NAME graph;                                                                                                                                  \
        const std::size_t number_of_vertices = 100;                                                                                                                 \
        std::vector<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME> inserted_vertices_pointers;                                      \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                                                                     \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                                       \
            inserted_vertices_pointers.emplace_back( ( graph.insert_vertex(i) ).first );                                                                            \
            for(std::size_t j = 0; j <= i; ++j) {                                                                                                                   \
                const MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME insertion_const_vertex_j_ptr_result = ( graph.insert_vertex(j) ).first;  \
                for(std::size_t k = 0; k<inserted_vertices_pointers.size(); ++k) {                                                                                  \
                    if(k==j) {                                                                                                                                      \
                        ASSERT_FALSE(inserted_vertices_pointers[k] != insertion_const_vertex_j_ptr_result);                                                         \
                        ASSERT_FALSE(insertion_const_vertex_j_ptr_result != inserted_vertices_pointers[k]);                                                         \
                    }                                                                                                                                               \
                    else {                                                                                                                                          \
                        ASSERT_TRUE(inserted_vertices_pointers[k] != insertion_const_vertex_j_ptr_result);                                                          \
                        ASSERT_TRUE(insertion_const_vertex_j_ptr_result != inserted_vertices_pointers[k]);                                                          \
                    }                                                                                                                                               \
                }                                                                                                                                                   \
            }                                                                                                                                                       \
        }                                                                                                                                                           \
    }                                                                                                                                                               \

#define SET_VERTEX_GRAPH_CORRECT_RETURNED_VERTEX_POINTER_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)       \
    TEST(TEST_SUITE_NAME, correct_returned_vertex_pointer_reference_after_assignment) {                                             \
        CONCRETE_CLASS_NAME graph;                                                                                                  \
        const std::size_t number_of_vertices = 100;                                                                                 \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle > inserted_vertices_pointers;      \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                                     \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                       \
            inserted_vertices_pointers.emplace_back( ( graph.insert_vertex(i) ).first );                                            \
            typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle vertex_ptr = inserted_vertices_pointers.back();      \
            const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle* const vertex_ptr_address = &vertex_ptr;       \
            for(std::size_t k = 0; k < inserted_vertices_pointers.size(); ++k )  {                                                  \
                ASSERT_EQ( &( vertex_ptr = inserted_vertices_pointers[k] ), vertex_ptr_address );                                   \
            }                                                                                                                       \
        }                                                                                                                           \
    }                                                                                                                               \

#define SET_VERTEX_GRAPH_VERTEX_POINTER_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                             \
    TEST(TEST_SUITE_NAME, vertex_pointer_assignment_operator_test_1) {                                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                  \
        const std::size_t number_of_vertices = 100;                                                                                 \
        typename std::vector<                                                                                                       \
            std::pair<                                                                                                              \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                 \
                const std::size_t*                                                                                                  \
            >                                                                                                                       \
        > inserted_vertices;                                                                                                        \
        inserted_vertices.reserve(number_of_vertices);                                                                              \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                       \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                           \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                     \
            typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle vertex_ptr = ( inserted_vertices.back() ).first;     \
            for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                           \
                vertex_ptr = ( inserted_vertices[k] ).first;                                                                        \
                ASSERT_EQ( vertex_ptr , ( inserted_vertices[k] ).first );                                                           \
                ASSERT_EQ( &( *vertex_ptr ) , ( inserted_vertices[k] ).second );                                                    \
                ASSERT_EQ( *vertex_ptr , k );                                                                                       \
            }                                                                                                                       \
        }                                                                                                                           \
    }                                                                                                                               \

#define SET_VERTEX_GRAPH_CORRECT_RETURNED_CONSTANT_VERTEX_POINTER_REFERENCE_AFTER_ASSIGNMENT_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)      \
    TEST(TEST_SUITE_NAME, correct_returned_constant_vertex_pointer_reference_after_assignment) {                                            \
        CONCRETE_CLASS_NAME graph;                                                                                                          \
        const std::size_t number_of_vertices = 100;                                                                                         \
        typename std::vector< typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME > inserted_vertices_pointers;   \
        inserted_vertices_pointers.reserve(number_of_vertices);                                                                             \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                               \
            inserted_vertices_pointers.emplace_back( ( graph.insert_vertex(i) ).first );                                                    \
            typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME vertex_ptr = inserted_vertices_pointers.back();   \
            const typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME* const vertex_ptr_address = &vertex_ptr;    \
            for(std::size_t k = 0; k < inserted_vertices_pointers.size(); ++k )  {                                                          \
                ASSERT_EQ( &( vertex_ptr = inserted_vertices_pointers[k] ), vertex_ptr_address );                                           \
            }                                                                                                                               \
        }                                                                                                                                   \
    }                                                                                                                                       \

#define SET_VERTEX_GRAPH_CONSTANT_VERTEX_POINTER_ASSIGNMENT_OPERATOR_TEST_1(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                            \
    TEST(TEST_SUITE_NAME, constant_vertex_pointer_assignment_operator_test_1) {                                                             \
        CONCRETE_CLASS_NAME graph;                                                                                                          \
        const std::size_t number_of_vertices = 100;                                                                                         \
        typename std::vector<                                                                                                               \
            std::pair<                                                                                                                      \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME,                                              \
                const std::size_t*                                                                                                          \
            >                                                                                                                               \
        > inserted_vertices;                                                                                                                \
        inserted_vertices.reserve(number_of_vertices);                                                                                      \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                               \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                                   \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                             \
            typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::CONSTANT_VERTEX_PTR_NAME vertex_ptr = ( inserted_vertices.back() ).first;  \
            for(std::size_t k = 0; k < inserted_vertices.size(); ++k )  {                                                                   \
                vertex_ptr = ( inserted_vertices[k] ).first;                                                                                \
                ASSERT_EQ( vertex_ptr , ( inserted_vertices[k] ).first );                                                                   \
                ASSERT_EQ( &( *vertex_ptr ) , ( inserted_vertices[k] ).second );                                                            \
                ASSERT_EQ( *vertex_ptr , k );                                                                                               \
            }                                                                                                                               \
        }                                                                                                                                   \
    }                                                                                                                                       \

#define SET_VERTEX_GRAPH_UNABLE_TO_CONVERT_A_VERTEX_POINTER_TO_MULTISET_VERTEX_POINTER_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                                                                                                                        \
    TEST(TEST_SUITE_NAME, unable_to_convert_a_vertex_pointer_to_multiset_vertex_pointer) {                                                                                                                                                                                              \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                                                                                                                      \
        const std::size_t number_of_vertices = 100;                                                                                                                                                                                                                                     \
        typename std::vector<                                                                                                                                                                                                                                                           \
            std::pair<                                                                                                                                                                                                                                                                  \
                typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::vertex_handle,                                                                                                                                                                                                     \
                const std::size_t*                                                                                                                                                                                                                                                      \
            >                                                                                                                                                                                                                                                                           \
        > inserted_vertices;                                                                                                                                                                                                                                                            \
        inserted_vertices.reserve(number_of_vertices);                                                                                                                                                                                                                                  \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                                                                                                                                                           \
            inserted_vertices.emplace_back( ( graph.insert_vertex(i) ).first , nullptr );                                                                                                                                                                                               \
            ( inserted_vertices.back() ).second = &( *( ( inserted_vertices.back() ).first ) );                                                                                                                                                                                         \
        }                                                                                                                                                                                                                                                                               \
        for(std::size_t i = 0; i < number_of_vertices; ++i) {                                                                                                                                                                                                                           \
            ASSERT_THROW(const typename MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<std::size_t>::vertex_handle multiset_vertex_ptr_i = static_cast<MAIN_LIBRARY_NAMESPACE::multiset_vertex_graph<std::size_t>::vertex_handle>(( inserted_vertices[i] ).first), std::exception);      \
        }                                                                                                                                                                                                                                                                               \
    }                                                                                                                                                                                                                                                                                   \

#endif //GENERIC_SET_VERTEX_GRAPH_TESTS_H