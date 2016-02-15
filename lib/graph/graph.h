// TODO: Try to replace "bilateral edge" with something concise, similarly to "arc"

#pragma once

#include <limits>
#include <vector>

#include "util/getters.h"


using GraphIndex = int;

constexpr GraphIndex kMaxGraphIndex = std::numeric_limits<GraphIndex>::max();
constexpr GraphIndex kInvalidGraphVertex = -1;


namespace internal {

#define UNDIRECTED_ONLY  \
  template<bool kDirectedLocal = kDirected, typename = typename std::enable_if<!kDirectedLocal>::type>
#define DIRECTED_ONLY  \
  template<bool kDirectedLocal = kDirected, typename = typename std::enable_if<kDirectedLocal>::type>

template<bool kDirected>
class Graph_AdjacencyList {
public:
  Graph_AdjacencyList(GraphIndex num_vertices__ = 0) : edges_(num_vertices__) {}

  GraphIndex num_vertices() const {
    return GraphIndex(edges_.size());
  }
  void extend_to_fit(GraphIndex num_vertices__) {
    ++num_vertices__;
    if (num_vertices__ > GraphIndex(edges_.size()))
      edges_.resize(num_vertices__);
  }

  void add_bilateral_edge(GraphIndex a, GraphIndex b) {
    at(edges_, a).push_back(b);
    at(edges_, b).push_back(a);
  }
  void add_bilateral_edge_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_bilateral_edge(a, b);
  }
  DIRECTED_ONLY void add_arc(GraphIndex a, GraphIndex b) {
    at(edges_, a).push_back(b);
  }
  DIRECTED_ONLY void add_arc_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_arc(a, b);
  }

  UNDIRECTED_ONLY const std::vector<GraphIndex>& nbrs(GraphIndex a) const {
    return at(edges_, a);
  }
  UNDIRECTED_ONLY const std::vector<GraphIndex>& in_nbrs(GraphIndex a) const {
    return at(edges_, a);
  }
  const std::vector<GraphIndex>& out_nbrs(GraphIndex a) const {
    return at(edges_, a);
  }

private:
  std::vector<std::vector<GraphIndex>> edges_;
};

#undef UNDIRECTED_ONLY
#undef DIRECTED_ONLY

}  // namespace internal

using UndirectedGraph_AdjacencyList = internal::Graph_AdjacencyList<false>;
using DirectedGraph_AdjacencyList = internal::Graph_AdjacencyList<true>;
