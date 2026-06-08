cmake_minimum_required(VERSION 3.31)
project(graphdom)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} INTERFACE
        include/graphdom/utility.h)

target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_subdirectory(unit_test)