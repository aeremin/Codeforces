#pragma once

#include <stack>

#include "graph.h"


// TODO: Move somewhere
enum class IterationControl {
  Continue,
  Abort,
};

// TODO: Move somewhere
class Nothing {};

// Depth-first search.
// Typespec:
//     IterationControl visitor(StateT&, GraphIndex)
//
// TODO: Test.
// TODO: Simplify.
// TODO: Optimize.
template<typename GraphT, typename VisitorT, typename StateT>
void dfs(const GraphT& graph,
         const std::vector<GraphIndex>& starting_vetrices,
         const VisitorT& visitor,
         StateT& state) {
  struct StackItem {
    GraphIndex vertex;
    GraphIndex i_neighbour;
  };
  VisitedBitset visited(graph.num_vertices(), false);
  std::stack<StackItem> stack;
  bool aborting = false;
  for (GraphIndex start : starting_vetrices) {
    if (!visited[start]) {
      visited[start] = true;
      stack.push({start, 0});
    }
    while (!stack.empty()) {
      auto& top = stack.top();
      bool we_need_to_go_deeper = false;
      if (!aborting) {
        const auto& neighbourhood = graph.out_nbrs(top.vertex);
        while (top.i_neighbour < GraphIndex(neighbourhood.size())) {
          GraphIndex neighbour = neighbourhood[top.i_neighbour];
          ++top.i_neighbour;
          if (!visited[neighbour]) {
            visited[neighbour] = true;
            stack.push({neighbour, 0});
            we_need_to_go_deeper = true;
            break;
          }
        }
      }
      if (!we_need_to_go_deeper) {
        if (visitor(state, top.vertex) == IterationControl::Abort) {
          aborting = true;
        }
        stack.pop();
      }
    }
  }
}

// Depth-first search.
// Typespec:
//     void visitor(GraphIndex)
//
template<typename GraphT, typename VisitorT>
void dfs(const GraphT& graph,
         const std::vector<GraphIndex>& starting_vetrices,
         const VisitorT& visitor) {
  Nothing state;
  dfs(graph, starting_vetrices,
      [&visitor](Nothing, GraphIndex vertex){
        visitor(vertex);
        return IterationControl::Continue;
      },
      state);
}
