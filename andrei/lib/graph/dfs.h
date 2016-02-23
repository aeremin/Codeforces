// Depth-first search.
//
// Signature:
//   dfs(graph, starting_vertices, [on_see, on_enter], on_exit)
//
// See graph/traversal.h for details.

#pragma once

#include "graph/traversal.h"


template<typename GraphT, typename VertexListT, typename OnSeeT, typename OnEnterT, typename OnExitT>
IterationResult dfs(const GraphT& graph,
                    const VertexListT& starting_vertices,
                    const OnSeeT& on_see,
                    const OnEnterT& on_enter,
                    const OnExitT& on_exit) {
  using GraphTraversalStack = std::stack<GraphTraversalExecutionItem, std::vector<GraphTraversalExecutionItem>>;
  return traverse_graph<GraphTraversalStack, GraphT, VertexListT, OnSeeT, OnEnterT, OnExitT>(
      graph, starting_vertices, on_see, on_enter, on_exit);
}

template<typename GraphT, typename OnSeeT, typename OnEnterT, typename OnExitT>
IterationResult dfs(const GraphT& graph,
                    const std::initializer_list<GraphIndex>& starting_vertices,
                    const OnSeeT& on_see,
                    const OnEnterT& on_enter,
                    const OnExitT& on_exit) {
  return dfs<GraphT, std::initializer_list<GraphIndex>, OnSeeT, OnEnterT, OnExitT>(
      graph, starting_vertices, on_see, on_enter, on_exit);
}

template<typename GraphT, typename VertexListT, typename VisitorT>
IterationResult dfs(const GraphT& graph,
                    const VertexListT& starting_vertices,
                    const VisitorT& visitor) {
  return dfs(graph, starting_vertices, graph_traversal_noop_continue, graph_traversal_noop_continue, visitor);
}

template<typename GraphT, typename VisitorT>
IterationResult dfs(const GraphT& graph,
                    const std::initializer_list<GraphIndex>& starting_vertices,
                    const VisitorT& visitor) {
  return dfs<GraphT, std::initializer_list<GraphIndex>, VisitorT>(
      graph, starting_vertices, visitor);
}
