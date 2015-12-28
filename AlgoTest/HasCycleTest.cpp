#include <gtest/gtest.h>
#include "AlgoTest/GraphHelper.h"
#include "algo/DepthFirstSearch.hpp"

TEST(HasCycleTest, WorksOnLinearGraph)
{
    const int nVertices = 10;
    auto g = GraphHelper::createLinearGraph(nVertices);
    EXPECT_FALSE(hasCycle(g));
}

TEST(HasCycleTest, WorksOnSimpleCycle)
{
    const int nVertices = 10;
    auto g = GraphHelper::createSimpleCycleGraph( nVertices );
    vector<int> cycle;
    EXPECT_TRUE(hasCycle(g, &cycle));
    EXPECT_EQ(nVertices, (int)cycle.size());
}