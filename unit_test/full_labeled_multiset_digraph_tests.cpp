#include <string>

#include "gtest/gtest.h"
#include "graphdom_tests_utility.h"
#include "generic_graph_tests.h"
#include "generic_digraph_tests.h"
#include "generic_multiset_graph_tests.h"
#include "generic_multiset_digraph_tests.h"
#include "generic_labeled_vertex_graph_tests.h"
#include "generic_labeled_vertex_multiset_graph_tests.h"
#include "generic_labeled_edge_digraph_tests.h"
#include "generic_labeled_edge_multiset_digraph_tests.h"
#include "graphdom/graphdom.h"
#include "graphdom/full_labeled_multiset_digraph.h"

using tested_graph = graphdom::full_labeled_multiset_digraph<std::size_t,std::string,std::string>;
using tested_graph_2 = graphdom::full_labeled_multiset_digraph<graphdom_tests::heap_value<std::size_t>,std::string,std::string>;
using tested_graph_3 = graphdom::full_labeled_multiset_digraph<graphdom_tests::heap_value<std::size_t>,graphdom_tests::heap_value<std::string>,std::string>;
using tested_graph_4 = graphdom::full_labeled_multiset_digraph<std::size_t,std::string, graphdom_tests::heap_value< std::pair< const std::size_t* , const std::size_t* > > >;
using tested_graph_5 = graphdom::full_labeled_multiset_digraph<std::size_t,std::string, graphdom_tests::heap_value< std::pair< std::size_t* , std::size_t* > > >;

IS_A_GRAPH_TEST(full_labeled_multiset_digraph,tested_graph,std::size_t);

DIGRAPH_IS_A_NON_MIXED_GRAPH_TEST(full_labeled_multiset_digraph,tested_graph,std::size_t);

DIGRAPH_IS_NOT_A_MIXED_GRAPH_TEST(full_labeled_multiset_digraph,tested_graph,std::size_t);

NO_VERTICES_AFTER_DEFAULT_CONSTRUCTION_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_IS_A_MULTISET_GRAPH_TEST(full_labeled_multiset_digraph,tested_graph,std::size_t);

MULTISET_GRAPH_IS_NOT_A_SET_GRAPH_TEST(full_labeled_multiset_digraph,tested_graph,std::size_t);

MULTISET_GRAPH_ORDER_METHOD_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_ORDER_METHOD_WITH_MOVE_INSERTION_WITHOUT_LABEL_TEST(full_labeled_multiset_digraph,tested_graph_2);

MULTISET_GRAPH_CORRECT_VERTEX_SPECIFIC_HANDLE_DEREFERENCING_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_CORRECT_VERTEX_SPECIFIC_HANDLE_DEREFERENCING_AFTER_OTHER_VERTICES_ERASION_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_CORRECT_CONVERSION_FROM_VERTEX_SPECIFIC_HANDLE_TO_VERTEX_CONST_HANDLE_TEST_1(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_CORRECT_CONVERSION_FROM_VERTEX_SPECIFIC_HANDLE_TO_VERTEX_GENERIC_HANDLE_TEST_1(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_CORRECT_CONVERSION_FROM_VERTEX_GENERIC_HANDLE_TO_VERTEX_SPECIFIC_HANDLE_TEST_1(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_SPECIFIC_HANDLE_EQUALITY_OPERATOR_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_SPECIFIC_HANDLE_INEQUALITY_OPERATOR_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_HANDLE_EQUALITY_OPERATOR_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_HANDLE_INEQUALITY_OPERATOR_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_CONST_HANDLE_EQUALITY_OPERATOR_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_CONST_HANDLE_INEQUALITY_OPERATOR_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_CORRECT_RETURNED_VERTEX_SPECIFIC_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_SPECIFIC_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_CORRECT_RETURNED_VERTEX_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_CORRECT_RETURNED_VERTEX_CONST_HANDLE_REFERENCE_AFTER_ASSIGNMENT_TEST(full_labeled_multiset_digraph,tested_graph);

MULTISET_GRAPH_VERTEX_CONST_HANDLE_ASSIGNMENT_OPERATOR_TEST_1(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_SPECIFIC_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

TEST(full_labeled_multiset_digraph,correct_edges_insertion__without_label__specific_vertex_handle__adj_list__c_methods) {
    tested_graph graph;
    const std::size_t number_of_different_vertex_values = 10;
    const std::size_t number_of_repetitions = 3;
    typename std::vector< typename graphdom::multiset_graph<std::size_t>::vertex_handle > inserted_vertices;
    inserted_vertices.reserve( number_of_different_vertex_values * number_of_repetitions );
    for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {
        for(std::size_t j = 0; j < number_of_repetitions; ++j) {
            inserted_vertices.emplace_back( graph.insert_vertex( i ) );
        }
    }
    for(std::size_t first = 0; first < inserted_vertices.size(); ++first) {
        for(std::size_t second = 0; second < inserted_vertices.size(); ++second) {
            graph.insert_edge( inserted_vertices[first], inserted_vertices[second] );
            for( std::size_t k = 0; k < inserted_vertices.size(); ++k ) {
                auto k_adj_list_undirected = inserted_vertices[k].adj_list(graphdom::edge_type::undirected);
                ASSERT_EQ(k_adj_list_undirected.cbegin(),k_adj_list_undirected.cend());
                std::set<const std::size_t*> expected_vertices_in_k_adj_lists;
                if( k < first ) {
                    for(std::size_t j = 0; j < inserted_vertices.size(); ++j ) {
                        expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );
                    }
                }
                else if( k == first ) {
                    for(std::size_t j = 0; j <= second; ++j ) {
                        expected_vertices_in_k_adj_lists.emplace( &*inserted_vertices[j] );
                    }
                }
                auto k_adj_list = inserted_vertices[k].adj_list();
                std::set<const std::size_t*> vertices_encountered_in_k_adj_list;
                for(auto edge_itr = k_adj_list.cbegin(); edge_itr != k_adj_list.cend(); ++edge_itr) {
                    ASSERT_EQ(edge_itr.edge_type(),graphdom::edge_type::directed);
                    const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));
                    EXPECT_TRUE( ( vertices_encountered_in_k_adj_list.emplace( edge_itr_vertex_raw_pointer ) ).second );
                    ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );
                }
                ASSERT_EQ(vertices_encountered_in_k_adj_list.size(),expected_vertices_in_k_adj_lists.size());
                auto k_adj_list_directed = inserted_vertices[k].adj_list(graphdom::edge_type::directed);
                std::set<const std::size_t*> vertices_encountered_in_k_adj_list_directed;
                for(auto edge_itr = k_adj_list_directed.cbegin(); edge_itr != k_adj_list_directed.cend(); ++edge_itr) {
                    ASSERT_EQ(edge_itr.edge_type(),graphdom::edge_type::directed);
                    const std::size_t* const edge_itr_vertex_raw_pointer = &(*(*edge_itr));
                    EXPECT_TRUE( ( vertices_encountered_in_k_adj_list_directed.emplace( edge_itr_vertex_raw_pointer ) ).second );
                    ASSERT_NE( expected_vertices_in_k_adj_lists.find( edge_itr_vertex_raw_pointer ) , expected_vertices_in_k_adj_lists.end() );
                }
                ASSERT_EQ(vertices_encountered_in_k_adj_list_directed.size(),expected_vertices_in_k_adj_lists.size());
            }
        }
    }
};

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_HANDLE_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_CONST_HANDLE_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_CONST_HANDLE_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_INSERTION_WITHOUT_LABEL_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_SPECIFIC_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_SPECIFIC_VERTEX_HANDLE_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_HANDLE_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_CONST_HANDLE_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_CONST_HANDLE_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS(full_labeled_multiset_digraph,tested_graph);

MULTISET_DIGRAPH_CORRECT_EDGES_ERASION_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_C_METHODS(full_labeled_multiset_digraph,tested_graph);

IS_A_LABELED_VERTEX_GRAPH(full_labeled_multiset_digraph,tested_graph,std::size_t,std::string);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_LVALUE_LABEL_LVALUE_SPECIFIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_LVALUE_LABEL_RVALUE_SPECIFIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_RVALUE_LABEL_LVALUE_SPECIFIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_RVALUE_LABEL_RVALUE_SPECIFIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_LVALUE_LABEL_LVALUE_GENERIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_LVALUE_LABEL_RVALUE_GENERIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_RVALUE_LABEL_LVALUE_GENERIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_VERTEX_MULTISET_GRAPH_CORRECT_VERTEX_INSERTION_WITH_LABEL_CORE_RVALUE_LABEL_RVALUE_GENERIC_VERTEX_HANDLE_TEST(full_labeled_multiset_digraph,tested_graph_3);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_HANDLE_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_CONST_HANDLE_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_CONST_HANDLE_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_HANDLE_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_CONST_HANDLE_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_CONST_HANDLE_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_VERTEX_CONST_HANDLE_CONST_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_4);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_SPECIFIC_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_SPECIFIC_VERTEX_HANDLE_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_LVALUE_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_SPECIFIC_VERTEX_HANDLE_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_SPECIFIC_VERTEX_HANDLE_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_NOT_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);

LABELED_EDGE_DIGRAPH_CORRECT_EDGE_INSERTION_WITH_LABEL_WITHOUT_REPETITIONS_RVALUE_SPECIFIC_VERTEX_HANDLE_CONST_ADJ_LIST_C_METHODS_TEST(full_labeled_multiset_digraph,tested_graph_5);