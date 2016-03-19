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

    void add_edge( int from, int to, PerEdgeData data = {} )
    {
        edges_[from].push_back( { to, data } );
        edges_[to].push_back( { from, data } );
    }

    void add_undirected_edge(int from, int to, PerEdgeData data = {})
    {
        edges_[from].push_back({ to, data });
    }

    const PerVertexData& get_vertex_data(int vInd) const
    {
        return vertexData_[vInd];
    }

    PerVertexData& get_vertex_data(int vInd)
    {
        return vertexData_[vInd];
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
