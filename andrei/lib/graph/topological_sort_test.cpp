// NOTE. Some tests here are overspecified (they expect a particular order).

#include "graph/topological_sort.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "graph/adjacency_list.h"

using testing::ElementsAre;


TEST(TopologicalSortTest, Basic) {
  DirectedGraph_Nonloaded_AdjacencyList graph(20);
  graph.add_arc(0, 1);
  graph.add_arc(0, 10);
  graph.add_arc(0, 11);
  graph.add_arc(1, 5);
  graph.add_arc(5, 4);
  graph.add_arc(5, 3);
  graph.add_arc(3, 2);
  graph.add_arc(4, 2);
  graph.add_arc(12, 13);
  graph.add_arc(13, 14);
  graph.add_arc(14, 0);
  graph.add_arc(14, 2);

  {
    auto top_sorted_opt = topological_sort_reachable_optimistic(graph, {0});
    EXPECT_THAT(top_sorted_opt, ElementsAre(2, 4, 3, 5, 1, 10, 11, 0));

    auto top_sorted_chk = topological_sort_reachable_checked(graph, {0});
    ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::Ok);
    EXPECT_THAT(top_sorted_opt, ElementsAre(2, 4, 3, 5, 1, 10, 11, 0));
  }

  graph.add_arc(2, 1);  // bam!

  {
    auto top_sorted_opt = topological_sort_reachable_optimistic(graph, {0});
    EXPECT_THAT(top_sorted_opt, ElementsAre(2, 4, 3, 5, 1, 10, 11, 0));

    auto top_sorted_chk = topological_sort_reachable_checked(graph, {0});
    ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
    EXPECT_EQ(top_sorted_chk.loop_length(), 4);
    EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(2, 4, 5, 1, 0));
    EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre(0));
    EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(2, 4, 5, 1));
  }

  DirectedGraph_Nonloaded_AdjacencyList graph2(20);

  graph2.add_arc(0, 1);
  graph2.add_arc(2, 3);
  graph2.add_arc(4, 5);
  graph2.add_arc(5, 4);  // bam!
  graph2.add_arc(6, 7);
  graph2.add_arc(8, 9);

  graph2.add_arc(10, 0);  // bam!
  graph2.add_arc(10, 4);  // bam!
  graph2.add_arc(10, 11);  // bam!

  {
    auto top_sorted_chk = topological_sort_reachable_checked(graph2, {0, 2, 4, 6, 8});
    ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
    EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(5, 4));
    EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre());
    EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(5, 4));
  }

  {
    auto top_sorted_chk = topological_sort_reachable_checked(graph2, {0, 2, 10, 6, 8});
    ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
    EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(5, 4, 10));
    EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre(10));
    EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(5, 4));
  }

  {
    auto top_sorted_chk = topological_sort_reachable_checked(graph2, {0, 2, 5, 6, 8});
    ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
    EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(4, 5));
    EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre());
    EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(4, 5));
  }

  {
    auto top_sorted_chk = topological_sort_reachable_checked(graph2, {5});
    ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
    EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(4, 5));
    EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre());
    EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(4, 5));
  }

  {
    auto top_sorted_chk = topological_sort_reachable_checked(graph2, {10});
    ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
    EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(5, 4, 10));
    EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre(10));
    EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(5, 4));
  }
}
