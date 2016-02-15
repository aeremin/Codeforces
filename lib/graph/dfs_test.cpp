#include "graph/dfs.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "graph/generator/simple.h"

using namespace testing;


class GraphTraversalCollect {
public:
  GraphTraversalCollect(std::vector<GraphIndex>& vertices__) : vertices_(vertices__) {}
  IterationControl operator()(const GraphTraversalState&, GraphIndex v) const {
    vertices_.push_back(v);
    return IterationControl::Proceed;
  };
private:
  std::vector<GraphIndex>& vertices_;
};


TEST(DfsTest, Empty) {
  auto graph = generate_empty_graph<SimpleGraph_AdjacencyList>(10);
  {
    std::vector<GraphIndex> visited;
    EXPECT_EQ(IterationResult::Done, dfs(graph, {3}, GraphTraversalCollect(visited)));
    EXPECT_THAT(visited, ElementsAre(3));
  }
  {
    std::vector<GraphIndex> on_see, on_enter, on_exit;
    EXPECT_EQ(IterationResult::Done, dfs(graph, {3}, GraphTraversalCollect(on_see),
                                         GraphTraversalCollect(on_enter), GraphTraversalCollect(on_exit)));
    EXPECT_THAT(on_see, ElementsAre());
    EXPECT_THAT(on_enter, ElementsAre(3));
    EXPECT_THAT(on_exit, ElementsAre(3));
  }
}

// TODO: Full graph test
// TODO: Check call sequence for each vertex
