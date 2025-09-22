cmake_minimum_required(VERSION 3.31)
project(graphlab)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(MAIN_LIBRARY_NAMESPACE=${PROJECT_NAME})

add_library(${PROJECT_NAME} SHARED graph.h
        utility/address_less.h
        dummy.cpp
        const_vertex_ptr.h
        vertex_ptr.h
        edge_iterator.h
        const_edge_iterator.h
        non_mixed_graph.h
        mixed_graph.h
        set_vertex_graph.h
        multiset_vertex_graph.h
        labeled_edge_non_mixed_graph.h
        labeled_edge_mixed_graph.h
        labeled_edge_graph.h
        labeled_vertex_graph.h
        labeled_vertex_set_vertex_graph.h
        labeled_vertex_multiset_vertex_graph.h
)

add_subdirectory(unit_test)
