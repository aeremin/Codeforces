#include "graph/dfs.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "graph/graph.h"
#include "graph/generator/simple.h"

using namespace testing;


class GraphTraversalCollect {
public:
  GraphTraversalCollect(std::vector<int>& vertices__) : vertices_(vertices__) {}
  IterationControl operator()(const GraphTraversalState&, int v) const {
    vertices_.push_back(v);
    return IterationControl::Proceed;
  };
private:
  std::vector<int>& vertices_;
};


TEST(DfsTest, Empty) {
  auto graph = generate_empty_graph<UndirectedGraph<>>(10);
  {
    std::vector<int> visited;
    EXPECT_EQ(IterationResult::Done, dfs(graph, {3}, GraphTraversalCollect(visited)));
    EXPECT_THAT(visited, ElementsAre(3));
  }
  {
    std::vector<int> on_see, on_enter, on_exit;
    EXPECT_EQ(IterationResult::Done, dfs(graph, {3}, GraphTraversalCollect(on_see),
                                         GraphTraversalCollect(on_enter), GraphTraversalCollect(on_exit)));
    EXPECT_THAT(on_see, ElementsAre());
    EXPECT_THAT(on_enter, ElementsAre(3));
    EXPECT_THAT(on_exit, ElementsAre(3));
  }
}

// TODO: Full graph test
// TODO: Check call sequence for each vertex

// Payloads no not affect the algorithms - just check compilability.
TEST(DfsTest, Payload) {
  auto graph = generate_full_undirected_graph<UndirectedGraph<std::string>>(1);
  dfs(graph, {0}, graph_traversal_noop_continue);
}

TEST(DfsTest, CallSequence) {
  DirectedGraph<> graph(20);
  graph.add_directed_edge(0, 1);
  graph.add_directed_edge(0, 10);
  graph.add_directed_edge(0, 11);
  graph.add_directed_edge(1, 5);
  graph.add_directed_edge(2, 1);
  graph.add_directed_edge(5, 4);
  graph.add_directed_edge(5, 3);
  graph.add_directed_edge(3, 2);
  graph.add_directed_edge(4, 2);
  graph.add_directed_edge(12, 13);
  graph.add_directed_edge(13, 14);
  graph.add_directed_edge(14, 0);
  graph.add_directed_edge(14, 2);

  std::vector<int> vertices;
  dfs(graph, {3, 7}, [&vertices](const GraphTraversalState&, int v){
    vertices.push_back(v);
    return IterationControl::Proceed;
  });
  EXPECT_THAT(vertices, ElementsAre(4, 5, 1, 2, 3, 7));
}
