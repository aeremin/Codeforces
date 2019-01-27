#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "algo/graph/rooted_graph.h"

using testing::UnorderedElementsAre;

//     1
//    / \
//   0   2
//  / \
// 3   4 
TEST(RootedGraphTest, Tree) {
    UndirectedGraph<> g(5);
    g.add_edge(1, 0);
    g.add_edge(1, 2);
    g.add_edge(0, 3);
    g.add_edge(0, 4);

    RootedGraph rooted(g, 1);

    EXPECT_EQ(rooted.parent(0), 1);
    EXPECT_EQ(rooted.parent(1), std::optional<int>());
    EXPECT_EQ(rooted.parent(2), 1);
    EXPECT_EQ(rooted.parent(3), 0);
    EXPECT_EQ(rooted.parent(4), 0);

    EXPECT_THAT(rooted.childs(1), UnorderedElementsAre(0, 2));
    EXPECT_THAT(rooted.childs(0), UnorderedElementsAre(3, 4));
    for (int v: {2, 3, 4})
        EXPECT_THAT(rooted.childs(v), UnorderedElementsAre());

    EXPECT_EQ(rooted.subtree_size(0), 3);
    EXPECT_EQ(rooted.subtree_size(1), 5);
    EXPECT_EQ(rooted.subtree_size(2), 1);
    EXPECT_EQ(rooted.subtree_size(3), 1);
    EXPECT_EQ(rooted.subtree_size(4), 1);

    for (int v: {0, 1, 2, 3, 4})
        EXPECT_THAT(rooted.back_edges(v), UnorderedElementsAre());

    EXPECT_THAT(rooted.leaves(), UnorderedElementsAre(2, 3, 4));

    EXPECT_EQ(rooted.depth(0), 1);
    EXPECT_EQ(rooted.depth(1), 0);
    EXPECT_EQ(rooted.depth(2), 1);
    EXPECT_EQ(rooted.depth(3), 2);
    EXPECT_EQ(rooted.depth(4), 2);

    EXPECT_THAT(rooted.vertices_with_depth(0), UnorderedElementsAre(1));
    EXPECT_THAT(rooted.vertices_with_depth(1), UnorderedElementsAre(0, 2));
    EXPECT_THAT(rooted.vertices_with_depth(2), UnorderedElementsAre(3, 4));
    EXPECT_THAT(rooted.vertices_with_depth(3), UnorderedElementsAre());
    EXPECT_THAT(rooted.vertices_with_depth(4), UnorderedElementsAre());
}

//   1
//  /|\
// | 0 2
// |/ 
// 3   
TEST(RootedGraphTest, BackEdge) {
    UndirectedGraph<> g(4);
    g.add_edge(1, 0);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(0, 3);

    RootedGraph rooted(g, 1);

    // It's either 0 or 3, depending on traversal order...
    ASSERT_EQ(rooted.vertices_with_depth(2).size(), 1);
    int deepest_root = rooted.vertices_with_depth(2)[0];
    // ... but in any case, it has back edge to 1.
    EXPECT_THAT(rooted.back_edges(deepest_root), UnorderedElementsAre(1));
}