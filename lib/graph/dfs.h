// Depth-first search.
//
// Supports all graphs, directed or non-directed. Only need to know the
// outer neighbourhood.
//
// All callbacks must have the following signature:
// ` IterationControl callback(const DfsState&, GraphIndex);
//
// Callback types:
//   - on_see: a vertex is being considered as a candidate to go to.
//   - on_enter: a vertex is pushed to stack
//   - on_exit: a vertex is poped from stack - this is the most important
//     part for dfs
//
// Callback sequence for each vertex:
//   (on_see (on_enter on_see* on_exit on_see*)?)?

#pragma once

#include <cassert>
#include <stack>

#include "graph/graph.h"
#include "util/callbacks.h"


struct DfsState {
  VisitedBitset visited;
  bool aborting = false;
};

IterationControl dfs_noop_continue(const DfsState&, GraphIndex) {
  return IterationControl::Continue;
};


// TODO: Test.
// TODO: Benchmark.
// TODO: Try to simplify.
template<typename GraphT, typename OnSeeT, typename OnEnterT, typename OnExitT>
IterationResult dfs(const GraphT& graph,
                    const std::vector<GraphIndex>& starting_vetrices,
                    const OnSeeT& on_see,
                    const OnEnterT& on_enter,
                    const OnExitT& on_exit) {
  struct StackItem {
    GraphIndex vertex;
    GraphIndex i_neighbour;
  };
  DfsState state;
  const DfsState& const_state = state;
  state.visited.resize(graph.num_vertices(), false);
  std::stack<StackItem> stack;
  for (GraphIndex start : starting_vetrices) {
    if (!state.visited[start]) {
      if (on_enter(const_state, start) == IterationControl::Abort) {
        state.aborting = true;
      } else {
        state.visited[start] = true;
        stack.push({start, 0});
      }
    }
    while (!stack.empty()) {
      auto& top = stack.top();
      bool we_need_to_go_deeper = false;
      if (!state.aborting) {
        const auto& neighbourhood = graph.out_nbrs(top.vertex);
        while (top.i_neighbour < GraphIndex(neighbourhood.size())) {
          GraphIndex neighbour = neighbourhood[top.i_neighbour];
          if (on_see(const_state, neighbour) == IterationControl::Abort) {
            we_need_to_go_deeper = false;
            state.aborting = true;
            break;
          }
          ++top.i_neighbour;
          if (!state.visited[neighbour]) {
            if (on_enter(const_state, neighbour) == IterationControl::Abort) {
              state.aborting = true;
            } else {
              state.visited[neighbour] = true;
              stack.push({neighbour, 0});
              we_need_to_go_deeper = true;
            }
            break;
          }
        }
      }
      if (!we_need_to_go_deeper) {
        if (on_exit(const_state, top.vertex) == IterationControl::Abort) {
          state.aborting = true;
        }
        stack.pop();
      }
    }
  }
  return state.aborting ? IterationResult::Aborted : IterationResult::Done;
}

template<typename GraphT, typename VisitorT>
IterationResult dfs(const GraphT& graph,
                    const std::vector<GraphIndex>& starting_vetrices,
                    const VisitorT& visitor) {
  return dfs(graph, starting_vetrices, dfs_noop_continue, dfs_noop_continue, visitor);
}
