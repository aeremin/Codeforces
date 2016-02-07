#pragma once

#include <algorithm>
#include <numeric>

#include "graph/dfs.h"


struct TopologicalSortResult {
  enum Status {
    Ok,
    LoopDetected,
  };

  Status status;

  // If Ok: topologically sorted vertices.
  // If LoopDetected: vertices of one of the loops, in traversal order.
  std::vector<GraphIndex> vertices;
};

template<typename DirectedGraphT>
std::vector<GraphIndex> topological_sort_reachable_optimistic(const DirectedGraphT& graph,
                                                              const std::vector<GraphIndex>& starting_vetrices) {
  std::vector<GraphIndex> result;
  dfs(graph,
      starting_vetrices,
      [&result](const DfsState&, GraphIndex v) {
        result.push_back(v);
        return IterationControl::Continue;
      });
  return result;
}

template<typename DirectedGraphT>
TopologicalSortResult topological_sort_reachable_checked(const DirectedGraphT& graph,
                                                         const std::vector<GraphIndex>& starting_vetrices) {
  constexpr GraphIndex kNoLoop = -1;
  std::vector<GraphIndex> result;
  VisitedBitset in_current_chain(graph.num_vertices(), false);
  GraphIndex loop_start = kNoLoop;
  IterationResult dfs_result =
      dfs(graph,
          starting_vetrices,
          [&](const DfsState&, GraphIndex v) {  // on seen
            if (in_current_chain[v]) {
              loop_start = v;
              return IterationControl::Abort;
            } else {
              return IterationControl::Continue;
            }
          },
          [&](const DfsState&, GraphIndex v) {  // on enter
            assert(!in_current_chain[v]);
            in_current_chain[v] = true;
            return IterationControl::Continue;
          },
          [&](const DfsState&, GraphIndex v) {  // on exit
            assert(in_current_chain[v]);
            in_current_chain[v] = false;
            result.push_back(v);
            return IterationControl::Continue;
          });
  if (dfs_result == IterationResult::Done) {
    assert(loop_start == kNoLoop);
    return {TopologicalSortResult::Ok, result};
  } else {
    assert(loop_start != kNoLoop);
    auto it = std::find(result.begin(), result.end(), loop_start);
    assert(it != result.end());
    result.erase(it + 1, result.end());
    return {TopologicalSortResult::LoopDetected, result};
  }
}

template<typename DirectedGraphT>
TopologicalSortResult topological_sort_checked(const DirectedGraphT& graph) {
  std::vector<GraphIndex> starting_vetrices(graph.num_vertices());
  std::iota(starting_vetrices.begin(), starting_vetrices.end(), 0);
  return topological_sort_reachable_checked(graph, starting_vetrices);
}
