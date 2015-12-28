#include <gtest/gtest.h>
#include "algo/DepthFirstSearch.hpp"
#include "AlgoTest/GraphHelper.h"

TEST(DepthFirstSearchTest, WorksOnSingleVertex)
{
    SimpleGraph graph(1);
    DepthFirstSearcher searcher(graph);
    int verticesCount = 0;
    auto increaseVerticesCount = [&](int)
    {
        verticesCount++;
        return false;
    };

    int edgesCount = 0;
    auto increaseEdgesCount = [&](int, int, bool)
    {
        edgesCount++;
        return false;
    };

    searcher.setVertexPreprocessCallback(increaseVerticesCount);
    searcher.setEdgePostprocessCallback(increaseEdgesCount);

    EXPECT_FALSE(searcher.search(0));
    EXPECT_EQ(0, edgesCount);
    EXPECT_EQ(1, verticesCount);
}

TEST(DepthFirstSearchTest, WorksOnLinearGraph)
{
    int nVertices = 10;
    auto graph = GraphHelper::createLinearGraph(nVertices);

    DepthFirstSearcher searcher(graph);
    int verticesCount = 0;
    auto increaseVerticesCount = [&](int vertex)
    {
        EXPECT_EQ(verticesCount++, vertex);
        return false;
    };

    int edgesCount = 0;
    auto increaseEdgesCount = [&](int from, int to, bool discovery)
    {
        if (discovery)
        {
            EXPECT_EQ(edgesCount++, from);
            EXPECT_EQ(edgesCount, to);
        }
        return false;
    };

    searcher.setVertexPreprocessCallback(increaseVerticesCount);
    searcher.setEdgePostprocessCallback(increaseEdgesCount);

    EXPECT_FALSE(searcher.search(0));
}

TEST(DepthFirstSearchTest, WorksOnSimpleCycle)
{
    int nVertices = 20;
    auto graph = GraphHelper::createSimpleCycleGraph(nVertices);

    DepthFirstSearcher searcher(graph);
    int verticesCount = 0;
    auto increaseVerticesCount = [&](int vertex)
    {
        EXPECT_EQ(verticesCount++, vertex);
        return false;
    };

    int discoveryEdgesCount = 0;
    int backEdgesCount = 0;
    auto processEdge = [&](int from, int to, bool discovery)
    {
        if (discovery)
        {
            EXPECT_EQ(discoveryEdgesCount++, from);
            EXPECT_EQ(discoveryEdgesCount, to);
        }
        else
        {
            EXPECT_EQ(0, to);
            EXPECT_EQ(nVertices - 1, from);
            ++backEdgesCount;
        }
        return false;
    };

    searcher.setVertexPreprocessCallback(increaseVerticesCount);
    searcher.setEdgePostprocessCallback(processEdge);

    EXPECT_FALSE(searcher.search(0));
    EXPECT_EQ(1, backEdgesCount); // Back edges are counted twice
}

//              4
//          1 < 
//      0 <---- 5
//          2 - 3
TEST(DepthFirstSearchTest, WorksOnConcreteCase)
{

    SimpleGraph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 5);
    g.addEdge(0, 2);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(2, 3);

    DepthFirstSearcher searcher(g);

    // We will stop in vertex 2
    vector<int> expectedVertices = { 0, 1, 4, 5, 2 };
    int iVertex = 0;
    searcher.setVertexPreprocessCallback([&](int vInd)
    {
        EXPECT_EQ(expectedVertices[iVertex++], vInd);
        return (vInd == 2);
    });

    EXPECT_TRUE(searcher.search(0));
}
