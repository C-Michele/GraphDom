#ifndef GENERIC_UGRAPH_TESTS_H
#define GENERIC_UGRAPH_TESTS_H

#include <utility>

#include "generic_graph_tests.h"
#include "gtest/gtest.h"
#include "../set_vertex_graph.h"
#include "../multiset_vertex_graph.h"
#include "../non_mixed_graph.h"
#include "../mixed_graph.h"

#define UGRAPH_IS_A_NON_MIXED_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                               \
    TEST(TEST_SUITE_NAME,is_a_non_mixed_graph) {                                                                            \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        EXPECT_NE(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::non_mixed_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);    \
    }                                                                                                                       \

#define UGRAPH_IS_NOT_A_NON_MIXED_GRAPH_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME,VERTEX_TYPENAME)                           \
    TEST(TEST_SUITE_NAME,is_not_a_mixed_graph) {                                                                            \
        CONCRETE_CLASS_NAME graph;                                                                                          \
        EXPECT_EQ(dynamic_cast< typename MAIN_LIBRARY_NAMESPACE::mixed_graph<VERTEX_TYPENAME>* >( &graph ),nullptr);        \
    }                                                                                                                       \

#define UGRAPH_THE_EDGES_INSERTION_IS_SYMMETRICAL_TEST(TEST_SUITE_NAME,CONCRETE_CLASS_NAME)                                                                                                                                     \
    TEST(TEST_SUITE_NAME,the_edges_insertion_is_symmetrical){                                                                                                                                                                   \
        CONCRETE_CLASS_NAME graph;                                                                                                                                                                                              \
        const std::size_t number_of_different_vertex_values = 100;                                                                                                                                                              \
        const std::size_t number_of_repetitions = 10;                                                                                                                                                                           \
        typename std::vector<typename MAIN_LIBRARY_NAMESPACE::graph<std::size_t>::VERTEX_PTR_NAME> inserted_vertices;                                                                                                           \
        inserted_vertices.reserve( ( dynamic_cast<MAIN_LIBRARY_NAMESPACE::set_vertex_graph<VertexType>*>(&graph) != nullptr ) ? number_of_different_vertex_values : number_of_different_vertex_values*number_of_repetitions );  \
        for(std::size_t i = 0; i < number_of_different_vertex_values; ++i) {                                                                                                                                                    \
            for(std::size_t j = 0; j < number_of_repetitions; ++j) {                                                                                                                                                            \
                const auto insertion_result = graph_vertex_insertion(graph,i);                                                                                                                                                  \
                if(insertion_result.second){                                                                                                                                                                                    \
                    inserted_vertices.emplace_back( insertion_result.first );                                                                                                                                                   \
                }                                                                                                                                                                                                               \
            }                                                                                                                                                                                                                   \
        }                                                                                                                                                                                                                       \
        for(std::size_t first = 0; first < inserted_vertices.size(); ++first ) {                                                                                                                                                \
            for(std::size_t second = first+1; second < inserted_vertices.size(); ++second ){                                                                                                                                    \
                graph.insert_edge(inserted_vertices[first],inserted_vertices[second]);                                                                                                                                          \
                auto second_adj_list = inserted_vertices[second].adj_list();                                                                                                                                                    \
                bool first_found_in_adj_list = false;                                                                                                                                                                           \
                for( auto edge_itr = second_adj_list.begin(); ( edge_itr!=second_adj_list.end() ) && !first_found_in_adj_list ; ++edge_itr ){                                                                                   \
                    if( *edge_itr == inserted_vertices[first] ){                                                                                                                                                                \
                        first_found_in_adj_list = true;                                                                                                                                                                         \
                    }                                                                                                                                                                                                           \
                    ASSERT_TRUE(first_found_in_adj_list);                                                                                                                                                                       \
                }                                                                                                                                                                                                               \
            }                                                                                                                                                                                                                   \
        }                                                                                                                                                                                                                       \
    }                                                                                                                                                                                                                           \

#endif //GENERIC_UGRAPH_TESTS_H