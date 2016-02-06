#pragma once

#include <stack>

#include "graph.h"


// TODO: Move somewhere
class Nothing {};

// Depth-first search.
// Typespec:
//     ResultT visitor(ResultT, GraphIndex)
//
// TODO: Test.
// TODO: Simplify.
// TODO: Optimize.
template<typename SimpleGraphT, typename VisitorT, typename ResultT>
ResultT dfs(const SimpleGraphT& graph,
            const std::vector<GraphIndex>& starting_vetrices,
            const VisitorT& visitor,
            ResultT initial) {
  struct StackItem {
    GraphIndex vertex;
    GraphIndex i_neighbour;
  };
  VisitedBitset visited(graph.num_vertices(), false);
  std::stack<StackItem> stack;
  for (GraphIndex start : starting_vetrices) {
    if (!visited[start]) {
      visited[start] = true;
      stack.push({start, 0});
    }
    while (!stack.empty()) {
      auto& top = stack.top();
      const auto& neighbourhood = graph.neighbours(top.vertex);
      bool we_need_to_go_deeper = false;
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
      if (!we_need_to_go_deeper) {
        initial = visitor(std::move(initial), top.vertex);
        stack.pop();
      }
    }
  }
  return initial;
}

// Depth-first search.
// Typespec:
//     void visitor(GraphIndex)
//
template<typename SimpleGraphT, typename VisitorT>
void dfs(const SimpleGraphT& graph,
         const std::vector<GraphIndex>& starting_vetrices,
         const VisitorT& visitor) {
  dfs(graph, starting_vetrices,
      [&visitor](Nothing, GraphIndex vertex){
        visitor(vertex);
        return Nothing{};
      },
      Nothing{});
}
