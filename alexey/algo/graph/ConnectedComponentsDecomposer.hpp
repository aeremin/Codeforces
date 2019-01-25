#pragma once
#include <algorithm>
#include <vector>

#include "DepthFirstSearch.hpp"
#include "graph/graph.h"

using std::fill;
using std::vector;

class ConnectedComponentsDecomposer {
  public:
    explicit ConnectedComponentsDecomposer(const UndirectedGraph<>& g) : graph_(g), searcher_(g) {}

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
            searcher_.setVertexPreprocessCallback([&](int index) -> bool {
                components_.back().push_back(index);
                vertexToComponent_[index] = iComponent;
                return false;
            });
            searcher_.search(i);
            iComponent++;
        }
    }

    const vector<int>& getVertexToComponentMap() const { return vertexToComponent_; }

    const vector<vector<int>>& getComponents() const { return components_; }

  private:
    const UndirectedGraph<>& graph_;
    DepthFirstSearcher searcher_;

    vector<int> vertexToComponent_;
    vector<vector<int>> components_;
};