#pragma once
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

template<class PerEdgeData, class PerVertexData>
class Graph
{

public:
    Graph( int nVertices, vector<PerVertexData> vertexData = {} )
        : 
        edges_(nVertices),
        vertexData_(move(vertexData))
    {
        if (vertexData_.empty())
            vertexData_.resize(nVertices);
    };

    void addEdge( size_t from, size_t to, PerEdgeData data = {} )
    {
        edges_[from].push_back( { to, data } );
        edges_[to].push_back( { from, data } );
    }

    void addUndirectedEdge(size_t from, size_t to, PerEdgeData data = {})
    {
        edges_[from].push_back({ to, data });
    }

    const vector<pair<size_t, PerEdgeData>>& vertexNeighbors(size_t vInd) const
    {
        return edges_[vInd];
    }

    const PerVertexData& getVertexData(int vInd) const
    {
        return vertexData_[vInd];
    }

    PerVertexData& getVertexData(int vInd)
    {
        return vertexData_[vInd];
    }
    
    size_t vertexCount() const
    {
        return edges_.size();
    }

private:
    vector<vector<pair<size_t, PerEdgeData>>> edges_;
    vector<PerVertexData> vertexData_;
};

struct EmptyStruct {};

using SimpleGraph = Graph<EmptyStruct, EmptyStruct>;