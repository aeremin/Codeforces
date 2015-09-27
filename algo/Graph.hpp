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

    void addEdge(size_t from, size_t to)
    {
        if (max(from, to) >= edges_.size())
            edges_.resize(max(from, to) + 1);
       
        edges_[from].push_back(to);
        edges_[to].push_back(from);
    }

    const vector<size_t>& vertexNeighbors(size_t vInd) const
    {
        return edges_[vInd];
    }

    size_t vertexCount() const
    {
        return edges_.size();
    }

private:
    vector<vector<size_t>> edges_;
};