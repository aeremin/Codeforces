#pragma once
#include <optional>
#include <vector>

#include "graph/dfs.h"
#include "graph/graph.h"

// Helper for "rooting" undirected connected graph.
class RootedGraph {
  public:
    // Time complexity is O(V+E).
    explicit RootedGraph(const UndirectedGraph<>& g, int root_vertex)
        : root_vertex_(root_vertex),
          parents_(g.num_vertices()),
          childs_(g.num_vertices()),
          subtree_sizes_(g.num_vertices()),
          back_edges_(g.num_vertices()),
          leaves_(),
          depths_(g.num_vertices()),
          vertices_with_depth_(),
          enter_time_(g.num_vertices()) {
        int step = 0;
        auto on_vertice_enter = [&](const GraphTraversalState& state, int v) {
            enter_time_[v] = step++;
            if (state.previous_vertex != kInvalidGraphVertex) {
                parents_[v] = state.previous_vertex;
                childs_[state.previous_vertex].push_back(v);
                depths_[v] = depths_[state.previous_vertex] + 1;
            }
            if (vertices_with_depth_.size() <= depths_[v])
                vertices_with_depth_.emplace_back();
            vertices_with_depth_[depths_[v]].push_back(v);
            return IterationControl::Proceed;
        };

        auto on_vertice_leave = [&](const GraphTraversalState& state, int v) {
            subtree_sizes_[v] = step - enter_time_[v];
            if (subtree_sizes_[v] == 1)
                leaves_.push_back(v);
            return IterationControl::Proceed;
        };

        auto on_vertice_see = [&](const GraphTraversalState& state, int v) {
            if (state.visited[v] && parent(state.previous_vertex) != v)
                back_edges_[state.previous_vertex].push_back(v);
            return IterationControl::Proceed;
        };

        dfs(g, {root_vertex}, on_vertice_see, on_vertice_enter, on_vertice_leave);

        // One additional empty element for all depth bigger than graph depth
        vertices_with_depth_.emplace_back();
    }

    // Returns parent of the vertex (or empty std::optional is vertex is root).
    std::optional<int> parent(int v) const {
        if (v == root_vertex_)
            return {};
        else
            return parents_[v];
    }

    // Returns direct childs of the vertex.
    const std::vector<int>& childs(int v) const { return childs_[v]; };

    // Returns subtree size (v itself is also included).
    int subtree_size(int v) const { return subtree_sizes_[v]; }

    // Returns std::vector of ends ob back edges coming from the vertex.
    const std::vector<int>& back_edges(int v) const { return back_edges_[v]; }

    // Return rooted graph leaves.
    const std::vector<int>& leaves() const { return leaves_; }

    // Returns depth (distance to the root) of the vertex.
    int depth(int v) const { return depths_[v]; }

    // Returns std::vector of vertices with specific depth.
    const std::vector<int>& vertices_with_depth(int d) const {
        if (d >= vertices_with_depth_.size() - 1)
            return vertices_with_depth_.back();
        return vertices_with_depth_[d];
    }

  private:
    int root_vertex_;
    std::vector<int> parents_;
    std::vector<std::vector<int>> childs_;
    std::vector<int> subtree_sizes_;
    std::vector<std::vector<int>> back_edges_;
    std::vector<int> leaves_;
    std::vector<int> depths_;
    std::vector<std::vector<int>> vertices_with_depth_;
    std::vector<int> enter_time_;
};