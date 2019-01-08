#include <gtest/gtest.h>
#include "graph/graph.h"

using namespace std;

TEST(GraphTest, HasEdge) {
    DirectedGraph<int, int> g(3);
    g.add_directed_edge(0, 2, 17);
    g.add_directed_edge(1, 2, 23);
    EXPECT_TRUE(g.has_edge(0, 2));
    EXPECT_FALSE(g.has_edge(2, 0));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_FALSE(g.has_edge(1, 0));
}

TEST(GraphTest, GetEdge) {
    DirectedGraph<int, int> g(3);
    g.add_directed_edge(0, 2, 17);
    g.add_directed_edge(1, 2, 23);
    EXPECT_EQ(std::optional<int>{17}, g.get_edge(0, 2));
    EXPECT_EQ(std::optional<int>{}, g.get_edge(2, 0));
    EXPECT_EQ(std::optional<int>{}, g.get_edge(0, 1));
    EXPECT_EQ(std::optional<int>{}, g.get_edge(1, 0));
}
