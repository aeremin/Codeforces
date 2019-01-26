#include <gtest/gtest.h>

#include "algo/graph/complement.h"


TEST(ComplementTest, EmptyGraph) {
    UndirectedGraph<> g(3);
    const auto complement = ComplementGraph(g);
    EXPECT_TRUE(complement.has_edge(0, 1));
    EXPECT_TRUE(complement.has_edge(1, 2));
    EXPECT_TRUE(complement.has_edge(0, 2));
}

TEST(ComplementTest, FullGraph) {
    UndirectedGraph<> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 2);
    const auto complement = ComplementGraph(g);
    EXPECT_FALSE(complement.has_edge(0, 1));
    EXPECT_FALSE(complement.has_edge(1, 2));
    EXPECT_FALSE(complement.has_edge(0, 2));
}

TEST(ComplementTest, SomeGraph) {
    UndirectedGraph<> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    const auto complement = ComplementGraph(g);
    EXPECT_FALSE(complement.has_edge(0, 1));
    EXPECT_FALSE(complement.has_edge(1, 2));
    EXPECT_TRUE(complement.has_edge(0, 2));
}