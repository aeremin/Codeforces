#include "graph/distance_unweighted.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "graph/adjacency_list.h"


TEST(FindDistanceUnweightedTest, Basic) {
  DirectedGraph_Nonloaded_AdjacencyList graph(20);

  graph.add_arc(0, 1);
  graph.add_arc(2, 3);
  graph.add_arc(4, 5);
  graph.add_arc(5, 4);
  graph.add_arc(6, 7);
  graph.add_arc(8, 9);

  graph.add_arc(10, 0);
  graph.add_arc(10, 4);
  graph.add_arc(10, 11);

  EXPECT_EQ(2, find_distance_unweighted(graph, 10, 5));
  EXPECT_EQ(kMaxGraphIndex, find_distance_unweighted(graph, 11, 10));
}
