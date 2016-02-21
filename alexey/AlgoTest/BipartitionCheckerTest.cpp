#include <gtest/gtest.h>
#include "algo/graph/BipartitionChecker.hpp"
#include "GraphHelper.h"

TEST(BipartitionCheckerTest, LinearGraphIsBipartite)
{
    auto graph = GraphHelper::createLinearGraph(5);
    auto checker = makeBipartitionChecker(graph);
    EXPECT_TRUE(checker.isBipartite());
    auto parts = checker.getSomePartitioning();
    std::vector<size_t> expectedPart1 = { 0, 2, 4 };
    std::vector<size_t> expectedPart2 = { 1, 3 };
    EXPECT_EQ(expectedPart1, parts.first);
    EXPECT_EQ(expectedPart2, parts.second);
}

TEST(BipartitionCheckerTest, OddCycleIsNotBipartite)
{
    auto graph = GraphHelper::createSimpleCycleGraph(5);
    auto checker = makeBipartitionChecker(graph);
    EXPECT_FALSE(checker.isBipartite());
}

TEST(BipartitionCheckerTest, GraphWithSelfLoopIsNotBipartite)
{
    SimpleGraph graph(10);
    graph.addEdge(5, 5);
    auto checker = makeBipartitionChecker(graph);
    EXPECT_FALSE(checker.isBipartite());
}

TEST(BipartitionCheckerTest, HexagonWithMainDiagonalsIsBipartite)
{
    auto graph = GraphHelper::createSimpleCycleGraph(6);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    auto checker = makeBipartitionChecker(graph);
    EXPECT_TRUE(checker.isBipartite());
    auto parts = checker.getSomePartitioning();
    std::vector<size_t> expectedPart1 = { 0, 2, 4 };
    std::vector<size_t> expectedPart2 = { 1, 3, 5 };
    EXPECT_EQ(expectedPart1, parts.first);
    EXPECT_EQ(expectedPart2, parts.second);
}