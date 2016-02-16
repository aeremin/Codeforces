// Graph basic definitions.
//
// GraphIndex is an integers type used to store graph vertex and edge indices.
// It is provided so that you can switch between int32/int64 without bloating
// code with even more templates.
//
// Supported graph types are:
//   - Nondirected / directed;
//   - Without edge payload / with payload (e.g. weight).
//
// All graph classes implement a subset of the following interface
// (only the functions that make sense for the graph type and can be
// executed fast on the given storage type are present):
//
//   * num_vertices
//     Returns the number of vertices in the graph.
//
//   * extend_to_fit(a)
//     Extends graph so that it can store vertex number 'a', i.e. to
//     at least `a + 1` vertex.
//
//   * add_bilateral_edge(a, b, [payload])
//   * add_bilateral_edge_with_vertices(a, b, [payload])
//     Adds edges ('a', 'b') and ('b', 'a'), with 'payload' attachted.
//     '..._with_vertices' version also extends the graph if necessary.
//
//   * add_arc(a, b, [payload])
//   * add_arc_with_vertices(a, b, [payload])
//     Adds edge ('a', 'b'), with 'payload' attachted.
//     '..._with_vertices' version also extends the graph if necessary.
//
//   * in_nbrs(a)
//     Edges going into the vertex 'a'.
//
//   * out_nbrs(a)
//     Edges going out of the vertex 'a'.

// TODO: Try to replace "bilateral edge" with something concise, similarly to "arc"

#pragma once

#include <limits>


using GraphIndex = int;

constexpr GraphIndex kMaxGraphIndex = std::numeric_limits<GraphIndex>::max();
constexpr GraphIndex kInvalidGraphVertex = -1;
