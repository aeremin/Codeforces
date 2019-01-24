// Distance in an unweighted graph (directed or non-directed graphs).
//
// * find_distance_unweighted(graph, source)
//   Returns an array containing distance from source to each vertex:
//   result[v] = / 0, if v == source;
//               | 1, 2, 3, ..., if v is reachable from source;
//               \ max_int, otherwise.
//
// * find_distance_unweighted(graph, source, destination)
//   Returns distance from source to destination.
//   Equal to `find_distance_unweighted(graph, source)[destination]`, but
//   faster if the distance is small.

#pragma once

#include "graph/bfs.h"
#include "util/check.h"
#include "util/relax.h"


template <typename GraphT>
std::vector<int> find_distance_unweighted(const GraphT& graph, int source) {
    std::vector<int> distances(graph.num_vertices(), std::numeric_limits<int>().max());
    distances[source] = 0;
    bfs(graph, {source}, [&](const GraphTraversalState& state, int v) {
        if (state.previous_vertex != kInvalidGraphVertex) {
            CHECK_INTERNAL(distances[state.previous_vertex] != std::numeric_limits<int>().max());
            relax_min(distances[v], distances[state.previous_vertex] + 1);
        }
        return IterationControl::Proceed;
    });
    return distances;
}

template <typename GraphT>
int find_distance_unweighted(const GraphT& graph, int source, int destination) {
    std::vector<int> distances(graph.num_vertices(), std::numeric_limits<int>().max());
    distances[source] = 0;
    bfs(graph, {source}, [&](const GraphTraversalState& state, int v) {
        if (state.previous_vertex != kInvalidGraphVertex) {
            CHECK_INTERNAL(distances[state.previous_vertex] != std::numeric_limits<int>().max());
            relax_min(distances[v], distances[state.previous_vertex] + 1);
        }
        if (v == destination)
            return IterationControl::AbortBluntly;
        return IterationControl::Proceed;
    });
    return distances[destination];
}
