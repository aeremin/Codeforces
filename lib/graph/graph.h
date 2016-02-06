#pragma once

#include <vector>


using GraphIndex = int;
using VisitedBitset = vector<char>;


class SimpleGraph_AdjacencyList {
public:
  SimpleGraph_AdjacencyList(GraphIndex num_vertices__) : edges_(num_vertices__) {}

  GraphIndex num_vertices() const {
    return GraphIndex(edges_.size());
  }

  void add_edge(GraphIndex a, GraphIndex b) {
    edges_.at(a).push_back(b);
    edges_.at(b).push_back(a);
  }

  const std::vector<GraphIndex>& neighbours(GraphIndex a) const {
    return edges_.at(a);
  }

private:
  std::vector<std::vector<GraphIndex>> edges_;
};
