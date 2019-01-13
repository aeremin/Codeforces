// Breadth-first search.
//
// Signature:
//   dfs(graph, starting_vertices, [on_see], on_enter, [on_exit])
//
// See graph/traversal.h for details.

#pragma once

#include "graph/traversal.h"


template<typename GraphT, typename VertexListT, typename OnSeeT, typename OnEnterT, typename OnExitT>
IterationResult bfs(const GraphT& graph,
                    const VertexListT& starting_vertices,
                    const OnSeeT& on_see,
                    const OnEnterT& on_enter,
                    const OnExitT& on_exit) {
                    class GraphTraversalQueue : public std::queue<GraphTraversalExecutionItem<GraphT>> {
    public:
        typename std::queue<GraphTraversalExecutionItem<GraphT>>::reference top() { return this->front(); }
    };
    return traverse_graph<GraphTraversalQueue, GraphT, VertexListT, OnSeeT, OnEnterT, OnExitT>(
        graph, starting_vertices, on_see, on_enter, on_exit);
}

template<typename GraphT, typename OnSeeT, typename OnEnterT, typename OnExitT>
IterationResult bfs(const GraphT& graph,
                    const std::initializer_list<int>& starting_vertices,
                    const OnSeeT& on_see,
                    const OnEnterT& on_enter,
                    const OnExitT& on_exit) {
                    return bfs<GraphT, std::initializer_list<int>, OnSeeT, OnEnterT, OnExitT>(
        graph, starting_vertices, on_see, on_enter, on_exit);
}

template<typename GraphT, typename VertexListT, typename VisitorT>
IterationResult bfs(const GraphT& graph,
                    const VertexListT& starting_vertices,
                    const VisitorT& visitor) {
    return bfs(graph, starting_vertices, graph_traversal_noop_continue, visitor, graph_traversal_noop_continue);
}

template<typename GraphT, typename VisitorT>
IterationResult bfs(const GraphT& graph,
                    const std::initializer_list<int>& starting_vertices,
                    const VisitorT& visitor) {
    return bfs<GraphT, std::initializer_list<int>, VisitorT>(
        graph, starting_vertices, visitor);
}
