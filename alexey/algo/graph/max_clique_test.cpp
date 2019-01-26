#include "algo/graph/max_clique.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using testing::ElementsAre;
using testing::UnorderedElementsAre;

TEST(MaximumCliqueTest, EmptyGraph) {
    UndirectedGraph<> g(20);
    EXPECT_EQ(MaximumClique(g).size(), 1);
}

TEST(MaximumCliqueTest, CompleteGraph) {
    UndirectedGraph<> g(20);
    for (int i : range(20))
        for (int j : range(i)) g.add_edge(i, j);
    EXPECT_THAT(MaximumClique(g),
                UnorderedElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19));
}

//           2
//         / |
//  0 -- 1   |
//         \ |
//           3
TEST(MaximumCliqueTest, SomeGraph) {
    UndirectedGraph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    EXPECT_THAT(MaximumClique(g), UnorderedElementsAre(1, 2, 3));
}