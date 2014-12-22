#pragma once
#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::max;

// Undirected graph with unweighted edges
class Graph
{

public:
    Graph(int nVertices = 0) : edges_(nVertices) {};

    void addEdge(int from, int to)
    {
        if (max(from, to) >= edges_.size())
            edges_.resize(max(from, to) + 1);
       
        edges_[from].push_back(to);
        edges_[to].push_back(from);
    }

    const vector<int>& vertexNeighbors(int vInd) const
    {
        return edges_[vInd];
    }

    int vertexCount() const
    {
        return edges_.size();
    }

private:
    vector<vector<int>> edges_;
};