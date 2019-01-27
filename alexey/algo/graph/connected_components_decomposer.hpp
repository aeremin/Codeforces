#pragma once
#include <algorithm>
#include <vector>

#include "graph/dfs.h"
#include "graph/graph.h"
#include "graph/traversal.h"

using std::fill;
using std::vector;

class ConnectedComponentsDecomposer {
  public:
    explicit ConnectedComponentsDecomposer(const UndirectedGraph<>& g) : graph_(g) {}

    void run() {
        int nVertices = graph_.num_vertices();
        vertexToComponent_.clear();
        vertexToComponent_.resize(nVertices);
        fill(begin(vertexToComponent_), end(vertexToComponent_), -1);

        int iComponent = 0;
        for (int i = 0; i < nVertices; ++i) {
            if (vertexToComponent_[i] >= 0)
                continue;  // Lies in processed component

            components_.push_back(vector<int>());
            dfs(graph_, {i}, 
                [&](const GraphTraversalState& state, int index) {
                    components_.back().push_back(index);
                    vertexToComponent_[index] = iComponent;
                    return IterationControl::Proceed;
                });
            iComponent++;
        }
    }

    const vector<int>& getVertexToComponentMap() const { return vertexToComponent_; }

    const vector<vector<int>>& getComponents() const { return components_; }

  private:
    const UndirectedGraph<>& graph_;

    vector<int> vertexToComponent_;
    vector<vector<int>> components_;
};