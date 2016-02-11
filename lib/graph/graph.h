#pragma once

#include <limits>
#include <vector>

#include "util/check.h"


using GraphIndex = int;

constexpr GraphIndex kMaxGraphIndex = std::numeric_limits<GraphIndex>::max();
constexpr GraphIndex kInvalidGraphVertex = -1;


class SimpleGraph_AdjacencyList {
public:
  SimpleGraph_AdjacencyList(GraphIndex num_vertices__ = 0) : edges_(num_vertices__) {}

  GraphIndex num_vertices() const {
    return GraphIndex(edges_.size());
  }
  void extend_to_fit(GraphIndex num_vertices__) {
    ++num_vertices__;
    if (num_vertices__ > GraphIndex(edges_.size()))
      edges_.resize(num_vertices__);
  }

  void add_edge(GraphIndex a, GraphIndex b) {
    vec_at(edges_, a).push_back(b);
    vec_at(edges_, b).push_back(a);
  }
  void add_edge_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_edge(a, b);
  }

  const std::vector<GraphIndex>& nbrs(GraphIndex a) const {
    return vec_at(edges_, a);
  }
  const std::vector<GraphIndex>& in_nbrs(GraphIndex a) const {
    return vec_at(edges_, a);
  }
  const std::vector<GraphIndex>& out_nbrs(GraphIndex a) const {
    return vec_at(edges_, a);
  }

private:
  std::vector<std::vector<GraphIndex>> edges_;
};

class DirectedGraph_AdjacencyList {
public:
  DirectedGraph_AdjacencyList(GraphIndex num_vertices__ = 0) : edges_(num_vertices__) {}

  GraphIndex num_vertices() const {
    return GraphIndex(edges_.size());
  }
  void extend_to_fit(GraphIndex num_vertices__) {
    ++num_vertices__;
    if (num_vertices__ > GraphIndex(edges_.size()))
      edges_.resize(num_vertices__);
  }

  void add_edge(GraphIndex a, GraphIndex b) {
    vec_at(edges_, a).push_back(b);
  }
  void add_edge_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_edge(a, b);
  }

  const std::vector<GraphIndex>& out_nbrs(GraphIndex a) const {
    return vec_at(edges_, a);
  }

private:
  std::vector<std::vector<GraphIndex>> edges_;
};
