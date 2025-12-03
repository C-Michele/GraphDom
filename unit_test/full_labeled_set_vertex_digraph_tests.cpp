#include <string>

#include "gtest/gtest.h"
#include "generic_graph_tests.h"
#include "generic_set_vertex_graph_tests.h"
#include "../graph.h"
#include "../full_labeled_set_vertex_digraph.h"

using tested_graph = MAIN_LIBRARY_NAMESPACE::full_labeled_set_vertex_digraph<std::size_t,std::string,std::string>;

SET_VERTEX_GRAPH_IS_A_GRAPH_TEST(full_labeled_set_vertex_graph,tested_graph,std::size_t);