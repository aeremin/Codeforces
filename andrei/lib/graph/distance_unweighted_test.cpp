#include "graph/distance_unweighted.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "graph/graph.h"


TEST(FindDistanceUnweightedTest, Basic) {
    DirectedGraph<> graph(20);

    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(2, 3);
    graph.add_directed_edge(4, 5);
    graph.add_directed_edge(5, 4);
    graph.add_directed_edge(6, 7);
    graph.add_directed_edge(8, 9);

    graph.add_directed_edge(10, 0);
    graph.add_directed_edge(10, 4);
    graph.add_directed_edge(10, 11);

    EXPECT_EQ(2, find_distance_unweighted(graph, 10, 5));
    EXPECT_EQ(std::numeric_limits<int>().max(), find_distance_unweighted(graph, 11, 10));
}
