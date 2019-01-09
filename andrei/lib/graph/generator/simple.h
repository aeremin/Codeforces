#pragma once

#include "graph/graph.h"
#include "internal_tests/random.h"
#include "iter/range.h"


template<typename GraphT>
GraphT generate_empty_graph(int num_vertices) {
  return GraphT(num_vertices);
}

template<typename GraphT>
GraphT generate_full_undirected_graph(int num_vertices) {
  GraphT graph(num_vertices);
  for (int i : range(num_vertices)) {
    for (int j : range(i))
      graph.add_edge(i, j);
  }
  return graph;
}

template<typename GraphT>
GraphT generate_full_directed_graph(int num_vertices) {
  GraphT graph(num_vertices);
  for (int i : range(num_vertices)) {
    for (int j : range(num_vertices)) {
      if (i != j)
        graph.add_directed_edge(i, j);
    }
  }
  return graph;
}

template<typename GraphT>
GraphT generate_random_graph_independent_edges(int num_vertices, double edge_probability) {
  GraphT graph(num_vertices);
  for (int i : range(num_vertices)) {
    for (int j : range(i)) {
      if (canonical_random_double(random_engine) < edge_probability)
        graph.add_bilateral_edge(i, j);
    }
  }
  return graph;
}
