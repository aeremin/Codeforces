#pragma once
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

template<class PerEdgeData, class PerVertexData>
class Graph
{

public:
    struct OutVertex
    {
        int vertex;
    };


    Graph( int nVertices, vector<PerVertexData> vertexData = {} )
        : 
        edges_(nVertices),
        edgesNoData_( nVertices ),
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
        edgesNoData_[from].push_back( { to } );
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

    int num_vertices() const
    {
        return edges_.size();
    }
   
    const vector<OutVertex>& out_nbrs( int v ) const
    {
        return edgesNoData_[v];
    }

private:
    vector<vector<pair<size_t, PerEdgeData>>> edges_;
    vector<vector<OutVertex>> edgesNoData_;
    vector<PerVertexData> vertexData_;
};

struct EmptyStruct {};

using SimpleGraph = Graph<EmptyStruct, EmptyStruct>;