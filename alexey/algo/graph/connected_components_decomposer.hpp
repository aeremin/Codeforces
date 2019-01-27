#pragma once
#include <algorithm>
#include <vector>

#include "graph/dfs.h"
#include "graph/graph.h"
#include "graph/traversal.h"

// Decomposes undirected graph into connected components.
// Run time is O(V+E).
class ConnectedComponentsDecomposer {
  public:
      explicit ConnectedComponentsDecomposer(const UndirectedGraph<>& g) {
        int nVertices = g.num_vertices();
        vertexToComponent_.clear();
        vertexToComponent_.resize(nVertices);
        fill(begin(vertexToComponent_), end(vertexToComponent_), -1);

        int iComponent = 0;
        for (int i = 0; i < nVertices; ++i) {
            if (vertexToComponent_[i] >= 0)
                continue;  // Lies in processed component

            components_.push_back(std::vector<int>());
            dfs(g, {i}, [&](const GraphTraversalState& state, int index) {
                components_.back().push_back(index);
                vertexToComponent_[index] = iComponent;
                return IterationControl::Proceed;
            });
            iComponent++;
        }
    }

    const std::vector<int>& vertext_to_component() const { return vertexToComponent_; }

    const std::vector<std::vector<int>>& components() const { return components_; }

  private:
    std::vector<int> vertexToComponent_;
    std::vector<std::vector<int>> components_;
};