#pragma once
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

template<class PerEdgeData, class PerVertexData>
class Graph
{

public:
    struct Edge : public pair<size_t, PerEdgeData> {
        using pair<size_t, PerEdgeData>::pair;
        int vertex() const { return this->first; }
    };

    struct OutVertex
    {
        int vertex;
    };


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

    const vector<Edge>& vertexNeighbors(size_t vInd) const
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
   
    const vector<Edge>& out_nbrs( int v ) const
    {
        return edges_[v];
    }

private:
    vector<vector<Edge>> edges_;
    vector<PerVertexData> vertexData_;
};

struct EmptyStruct {};

using SimpleGraph = Graph<EmptyStruct, EmptyStruct>;
