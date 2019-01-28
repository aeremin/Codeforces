#pragma once
#include <vector>
#include "graph/graph.h"
#include "graph/dfs.h"

// Checks only component containing startVertex
// Time complexity is O(V+E).
bool HasCycle(const UndirectedGraph<>& graph, std::vector<int>* cycle = nullptr, int startVertex = 0) {
    int backEdgeFrom = 0;
    int backEdgeTo = 0;
    bool result = false;
    std::vector<int> parents(graph.num_vertices(), kInvalidGraphVertex);

    auto on_see = [&](const GraphTraversalState& s, int to) {
        if (s.visited[to] && to != parents[s.previous_vertex]) {
            result = true;
            backEdgeFrom = s.previous_vertex;
            backEdgeTo = to;
            return IterationControl::AbortBluntly;
        }
        return IterationControl::Proceed;
    };

    auto on_enter = [&](const GraphTraversalState& s, int to) {
        parents[to] = s.previous_vertex;
        return IterationControl::Proceed;
    };

    dfs(graph, { startVertex }, on_see, on_enter, graph_traversal_noop_continue);

    if (result && cycle) {
        cycle->clear();
        cycle->push_back(backEdgeTo);
        for (int vertex = backEdgeFrom; vertex != backEdgeTo; vertex = parents[vertex])
            cycle->push_back(vertex);
    }

    return result;
}