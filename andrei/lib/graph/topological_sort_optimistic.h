// Graph topological sort.
//
// Returns directed graph vertices in such order {v_1, v_2, ..., v_n} that
// there is no edge (v_i, v_j) for any (j < i).
//
// * topological_sort_reachable_optimistic(graph, starting_vertices)
// * topological_sort_optimistic(graph)
//   Assumes that graph is acyclic.
//   If graph does contain a cycle, the behavior is undefined.
//
// See also: topological_sort_checked

#pragma once

#include "graph/dfs.h"


template<typename DirectedGraphT, typename VertexListT>
std::vector<int> topological_sort_reachable_optimistic(const DirectedGraphT& graph,
                                                       const VertexListT& starting_vertices) {
  std::vector<int> result;
  dfs(graph,
      starting_vertices,
      [&result](const GraphTraversalState&, int v) {
        result.push_back(v);
        return IterationControl::Proceed;
      });
  return result;
}

template<typename DirectedGraphT>
std::vector<int> topological_sort_reachable_optimistic(const DirectedGraphT& graph,
                                                       const std::initializer_list<int>& starting_vertices) {
  return topological_sort_reachable_optimistic<DirectedGraphT, std::initializer_list<int>>(graph, starting_vertices);
}

template<typename DirectedGraphT>
std::vector<int> topological_sort_optimistic(const DirectedGraphT& graph) {
  return topological_sort_reachable_optimistic(graph, range(graph.num_vertices()));
}
