#include <gtest/gtest.h>
#include "algo/graph/GraphHelper.h"
#include "algo/graph/has_cycle.h"

TEST(HasCycleTest, WorksOnLinearGraph)
{
    const int nVertices = 10;
    auto g = GraphHelper::createLinearGraph(nVertices);
    EXPECT_FALSE(HasCycle(g));
}

TEST(HasCycleTest, WorksOnSimpleCycle)
{
    const int nVertices = 3;
    auto g = GraphHelper::createSimpleCycleGraph( nVertices );
    std::vector<int> cycle;
    EXPECT_TRUE(HasCycle(g, &cycle));
    EXPECT_EQ(nVertices, (int)cycle.size());
}