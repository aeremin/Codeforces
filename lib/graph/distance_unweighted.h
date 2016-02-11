// Distance in an unweighted graph (directed or non-directed graphs).
//
// * find_distance_unweighted(graph, source)
//   Returns an array containing distance from source to each vertex:
//   result[v] = / 0, if v == source;
//               | 1, 2, 3, ..., if v is reachable from source;
//               \ kMaxGraphIndex, otherwise.
//
// * find_distance_unweighted(graph, source, destination)
//   Returns distance from source to destination.
//   Equal to `find_distance_unweighted(graph, source)[destination]`, but
//   faster if the distance is small.

#pragma once

#include "graph/bfs.h"


// TODO: Move to math library; add 'max' and 'bound'
template<typename T>
void inplace_min(T& value, const T& other) {
  value = std::min(value, other);
}


template<typename GraphT>
std::vector<GraphIndex> find_distance_unweighted(const GraphT& graph,
                                                 GraphIndex source) {
  std::vector<GraphIndex> distances(graph.num_vertices(), kMaxGraphIndex);
  distances[source] = 0;
  bfs(graph,
      {source},
      [&](const GraphTraversalState& state, GraphIndex v) {
        if (state.previous_vertex != kInvalidGraphVertex) {
          assert(distances[state.previous_vertex] != kMaxGraphIndex);
          inplace_min(distances[v], distances[state.previous_vertex] + 1);
        }
        return IterationControl::Proceed;
      });
  return distances;
}

template<typename GraphT>
GraphIndex find_distance_unweighted(const GraphT& graph,
                                    GraphIndex source,
                                    GraphIndex destination) {
  std::vector<GraphIndex> distances(graph.num_vertices(), kMaxGraphIndex);
  distances[source] = 0;
  bfs(graph,
      {source},
      [&](const GraphTraversalState& state, GraphIndex v) {
        if (state.previous_vertex != kInvalidGraphVertex) {
          assert(distances[state.previous_vertex] != kMaxGraphIndex);
          inplace_min(distances[v], distances[state.previous_vertex] + 1);
        }
        if (v == destination)
          return IterationControl::AbortBluntly;
        return IterationControl::Proceed;
      });
  return distances[destination];
}
