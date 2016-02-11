#pragma once

#include <vector>


using GraphIndex = int;
using GraphVertexBitset = std::vector<char>;

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
    edges_.at(a).push_back(b);
    edges_.at(b).push_back(a);
  }
  void add_edge_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_edge(a, b);
  }

  const std::vector<GraphIndex>& nbrs(GraphIndex a) const {
    return edges_.at(a);
  }
  const std::vector<GraphIndex>& in_nbrs(GraphIndex a) const {
    return edges_.at(a);
  }
  const std::vector<GraphIndex>& out_nbrs(GraphIndex a) const {
    return edges_.at(a);
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
    edges_.at(a).push_back(b);
  }
  void add_edge_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_edge(a, b);
  }

  const std::vector<GraphIndex>& out_nbrs(GraphIndex a) const {
    return edges_.at(a);
  }

private:
  std::vector<std::vector<GraphIndex>> edges_;
};
