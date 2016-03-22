#pragma once
#include <vector>
#include <utility>
#include <algorithm>

template<class PerEdgeData, class PerVertexData>
class Graph
{

public:
    struct Edge : public std::pair<size_t, PerEdgeData> {
        using std::pair<size_t, PerEdgeData>::pair;
        int vertex() const { return this->first; }
    };

    struct OutVertex
    {
        int vertex;
    };

    Graph( int nVertices, std::vector<PerVertexData> vertexData = {} )
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

    const std::vector<Edge>& out_nbrs( int v ) const
    {
        return edges_[v];
    }

private:
    std::vector<std::vector<Edge>> edges_;
    std::vector<PerVertexData> vertexData_;
};

struct EmptyStruct {};

using SimpleGraph = Graph<EmptyStruct, EmptyStruct>;
