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
)
