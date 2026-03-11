include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_compile_definitions(CPP_REPO_UNIT_TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_TEST_FILES run_all_tests.cpp
        generic_graph_tests.h
        generic_set_vertex_graph_tests.h
        generic_multiset_vertex_graph_tests.h
        full_labeled_set_vertex_digraph_tests.cpp
        full_labeled_multiset_vertex_digraph_tests.cpp
        generic_set_vertex_digraph_tests.h
        generic_multiset_vertex_digraph_tests.h
        generic_digraph_tests.h
        generic_set_vertex_ugraph_tests.h
        full_labeled_set_vertex_ugraph_tests.cpp
        generic_ugraph_tests.h)
add_executable(run_all_tests ${SOURCE_TEST_FILES})
target_link_libraries(run_all_tests gtest_main graphlab)