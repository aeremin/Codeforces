#include <gtest/gtest.h>
#include "algo/graph/ConnectedComponentsDecomposer.hpp"
#include "GraphHelper.h"

TEST(ConnectedComponentsDecomposerTest, WorksOnSimpleCycle)
{
    const int nVertices = 10;
    auto g = GraphHelper::createSimpleCycleGraph(nVertices);
    ConnectedComponentsDecomposer decomposer(g);
    decomposer.run();

    for (int elt : decomposer.getVertexToComponentMap())
        EXPECT_EQ(0, elt);

    auto components = decomposer.getComponents();
    EXPECT_EQ(1, (int)components.size());
    EXPECT_EQ(nVertices, (int)components[0].size());
}

TEST(ConnectedComponentsDecomposerTest, WorksOnConcreteTwoComponentsGraph)
{
    // 0 - 1  2
    //  \ /   |
    //   3    4
    SimpleGraph g( 5 );
    g.add_edge(0, 1);
    g.add_edge(3, 1);
    g.add_edge(3, 0);

    g.add_edge(2, 4);

    ConnectedComponentsDecomposer decomposer(g);
    decomposer.run();

    vector<int> expectedComponent = { 0, 0, 1, 0, 1 };
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(expectedComponent[i], decomposer.getVertexToComponentMap()[i]);

    auto components = decomposer.getComponents();
    EXPECT_EQ(2, (int)components.size());
    EXPECT_EQ(3, (int)components[0].size());
    EXPECT_EQ(2, (int)components[1].size());
}
