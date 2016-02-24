// Graph specified by an adjacency list.
//
// See graph/defs.h for graph interface description.
//
// If an edge between to vertices exists, the effect of adding it again
// is undefined.

#pragma once

#include <type_traits>
#include <vector>

#include "graph/basic.h"
#include "util/getters.h"
#include "util/templates.h"


namespace internal {

template<typename PayloadT>
class Graph_AdjacencyList_HalfEdge {
public:
  Graph_AdjacencyList_HalfEdge(GraphIndex vertex__, PayloadT payload__ = {}) : vertex_(vertex__), payload_(payload__) {}
  GraphIndex vertex() const { return vertex_; }
  PayloadT payload() const { return payload_; }
private:
  GraphIndex vertex_ = kInvalidGraphVertex;
  PayloadT payload_ = {};
};
template<>
class Graph_AdjacencyList_HalfEdge<void> {
public:
  Graph_AdjacencyList_HalfEdge(GraphIndex vertex__) : vertex_(vertex__) {}
  GraphIndex vertex() const { return vertex_; }
  operator GraphIndex() const { return vertex_; }
private:
  GraphIndex vertex_ = kInvalidGraphVertex;
};

#define UNDIRECTED_GRAPH  \
  bool kDirectedLocal = kDirected, typename = typename std::enable_if<!kDirectedLocal>::type
#define DIRECTED_GRAPH  \
  bool kDirectedLocal = kDirected, typename = typename std::enable_if<kDirectedLocal>::type
#define LOADED_GRAPH  \
  typename Payload = PayloadT, typename = typename std::enable_if<!std::is_void<Payload>::value>::type

template<bool kDirected, typename PayloadT>
class Graph_AdjacencyList {
public:
  using HalfEdge = Graph_AdjacencyList_HalfEdge<PayloadT>;

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
    at(edges_, a).push_back({b});
    at(edges_, b).push_back({a});
  }
  void add_bilateral_edge_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_bilateral_edge(a, b);
  }
  RESTRICT(LOADED_GRAPH) void add_bilateral_edge(GraphIndex a, GraphIndex b, const Payload& p) {
    at(edges_, a).push_back({b, p});
    at(edges_, b).push_back({a, p});
  }
  RESTRICT(LOADED_GRAPH) void add_bilateral_edge_with_vertices(GraphIndex a, GraphIndex b, const Payload& p) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_bilateral_edge(a, b, p);
  }
  RESTRICT(DIRECTED_GRAPH) void add_arc(GraphIndex a, GraphIndex b) {
    at(edges_, a).push_back({b});
  }
  RESTRICT(DIRECTED_GRAPH) void add_arc_with_vertices(GraphIndex a, GraphIndex b) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_arc(a, b);
  }
  RESTRICT(LOADED_GRAPH, DIRECTED_GRAPH) void add_arc(GraphIndex a, GraphIndex b, const Payload& p) {
    at(edges_, a).push_back({b, p});
  }
  RESTRICT(LOADED_GRAPH, DIRECTED_GRAPH) void add_arc_with_vertices(GraphIndex a, GraphIndex b, const Payload& p) {
    extend_to_fit(a);
    extend_to_fit(b);
    add_arc(a, b, p);
  }

  RESTRICT(UNDIRECTED_GRAPH) const std::vector<HalfEdge>& in_nbrs(GraphIndex a) const {
    return at(edges_, a);
  }
  const std::vector<HalfEdge>& out_nbrs(GraphIndex a) const {
    return at(edges_, a);
  }

private:
  std::vector<std::vector<HalfEdge>> edges_;
};

#undef UNDIRECTED_GRAPH
#undef DIRECTED_GRAPH
#undef LOADED_GRAPH

}  // namespace internal


template<typename PayloadT>
using UndirectedGraph_AdjacencyList = internal::Graph_AdjacencyList<false, PayloadT>;
template<typename PayloadT>
using DirectedGraph_AdjacencyList = internal::Graph_AdjacencyList<true, PayloadT>;

using UndirectedGraph_Nonloaded_AdjacencyList = UndirectedGraph_AdjacencyList<void>;
using DirectedGraph_Nonloaded_AdjacencyList = DirectedGraph_AdjacencyList<void>;
