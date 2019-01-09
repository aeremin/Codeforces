// Graph topological sort.
//
// Returns directed graph vertices in such order {v_1, v_2, ..., v_n} that
// there is no edge (v_i, v_j) for any (j < i).
//
// * topological_sort_reachable_optimistic(graph, [starting_vertices])
//   Assumes that graph is acyclic.
//   If graph does contain a cycle, the behavior is undefined
//   (It's actually completely deterministic and most likely stable,
//   but undefined in the sense that I'm too lazy to define it.)
//
// * topological_sort_reachable_checked(graph, [starting_vertices])
//   Checks if graph contains a cycle. Returns TopologicalSortResult, which is:
//   - Ok, if there are no cycles.
//     In this case content of `vertices()` is the same as the result of
//     optimistic sorting.
//   - LoopDetected, if there were loops.
//     In this case `vertices()` contain one of the loops (also accessible
//     via `loop()`) alongaside with the path from one of the starting vertices
//     to the loop (`preloop()`).
//     Note. Vertices in the loop and preloop are listed in the inversed
//           traverse order to match the successful case.
//     Note. Each vertex is listed only once, including loop starting vertex,
//           which is `loop().back()`.

#pragma once

#include <algorithm>
#include <numeric>

#include "container/span.h"
#include "graph/dfs.h"
#include "iter/range.h"
#include "util/check.h"


class TopologicalSortResult {
public:
  enum Status {
    Ok,
    LoopDetected,
  };

  TopologicalSortResult(Status status__, std::vector<int> vertices__, size_t loop_length__)
      : status_(status__)
      , vertices_(std::move(vertices__))
      , loop_length_(loop_length__) {
  }

  Status status() const {
    return status_;
  }

  const std::vector<int>& vertices() const {
    return vertices_;
  }

  int loop_length() const {
    CHECK_DEFAULT(status_ == LoopDetected);
    return loop_length_;
  }

  span<const int> preloop() const {
    CHECK_DEFAULT(status_ == LoopDetected);
    return {vertices_.data() + loop_length_, vertices_.data() + vertices_.size()};
  }
  span<const int> loop() const {
    CHECK_DEFAULT(status_ == LoopDetected);
    return {vertices_.data(), vertices_.data() + loop_length_};
  }

private:
  Status status_;
  std::vector<int> vertices_;
  int loop_length_;
};


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


template<typename DirectedGraphT, typename VertexListT>
TopologicalSortResult topological_sort_reachable_checked(const DirectedGraphT& graph,
                                                         const VertexListT& starting_vertices) {
  std::vector<int> result;
  std::vector<char> in_current_chain(graph.num_vertices(), false);
  int loop_start_vertex = kInvalidGraphVertex;
  IterationResult dfs_result =
      dfs(graph,
          starting_vertices,
          [&](const GraphTraversalState&, int v) {  // on seen
            if (in_current_chain[v]) {
              loop_start_vertex = v;
              result.clear();
              return IterationControl::AbortGently;
            } else {
              return IterationControl::Proceed;
            }
          },
          [&](const GraphTraversalState&, int v) {  // on enter
            CHECK_INTERNAL(!in_current_chain[v]);
            in_current_chain[v] = true;
            return IterationControl::Proceed;
          },
          [&](const GraphTraversalState&, int v) {  // on exit
            CHECK_INTERNAL(in_current_chain[v]);
            in_current_chain[v] = false;
            result.push_back(v);
            return IterationControl::Proceed;
          });
  if (dfs_result == IterationResult::Done) {
    CHECK_INTERNAL(loop_start_vertex == kInvalidGraphVertex);
    return {TopologicalSortResult::Ok, std::move(result), 0};
  } else {
    CHECK_INTERNAL(loop_start_vertex != kInvalidGraphVertex);
    auto loop_start_it = std::find(result.begin(), result.end(), loop_start_vertex);
    CHECK_INTERNAL(loop_start_it != result.end());
    size_t loop_length = (loop_start_it + 1) - result.begin();
    return {TopologicalSortResult::LoopDetected, std::move(result), loop_length};
  }
}

template<typename DirectedGraphT>
TopologicalSortResult topological_sort_reachable_checked(const DirectedGraphT& graph,
                                                         const std::initializer_list<int>& starting_vertices) {
  return topological_sort_reachable_checked<DirectedGraphT, std::initializer_list<int>>(graph, starting_vertices);
}

template<typename DirectedGraphT>
TopologicalSortResult topological_sort_checked(const DirectedGraphT& graph) {
  return topological_sort_reachable_checked(graph, range(graph.num_vertices()));
}
