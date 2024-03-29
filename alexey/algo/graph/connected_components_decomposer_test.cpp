#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "algo/graph/connected_components_decomposer.h"
#include "graph_helper.h"

using testing::UnorderedElementsAre;

TEST(ConnectedComponentsDecomposerTest, WorksOnSimpleCycle)
{
    const int nVertices = 10;
    auto g = GraphHelper::createSimpleCycleGraph(nVertices);
    ConnectedComponentsDecomposer decomposer(g);

    for (int elt : decomposer.vertext_to_component())
        EXPECT_EQ(0, elt);

    auto components = decomposer.components();
    EXPECT_EQ(1, components.size());
    EXPECT_THAT(components[0], UnorderedElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
}

TEST(ConnectedComponentsDecomposerTest, WorksOnConcreteTwoComponentsGraph)
{
    // 0 - 1  2
    //  \ /   |
    //   3    4
    UndirectedGraph<> g( 5 );
    g.add_edge(0, 1);
    g.add_edge(3, 1);
    g.add_edge(3, 0);

    g.add_edge(2, 4);

    ConnectedComponentsDecomposer decomposer(g);

    std::vector<int> expectedComponent = { 0, 0, 1, 0, 1 };
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(expectedComponent[i], decomposer.vertext_to_component()[i]);

    auto components = decomposer.components();
    EXPECT_EQ(2, components.size());
    EXPECT_THAT(components[0], UnorderedElementsAre(0, 1, 3));
    EXPECT_THAT(components[1], UnorderedElementsAre(2, 4));
}
