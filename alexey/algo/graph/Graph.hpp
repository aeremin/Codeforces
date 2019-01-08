#pragma once
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

template<class PerEdgeData, class PerVertexData>
class Graph
{

public:
    Graph( int nVertices )
        :
        edges_(nVertices),
        vertexData_(nVertices)
    {
    };

    Graph( std::vector<PerVertexData> vertexData )
        :
        edges_(vertexData.size()),
        vertexData_(move(vertexData))
    {
    };

    void add_edge( int from, int to, PerEdgeData data = {} )
    {
        edges_[from].insert( { to, data } );
        edges_[to].insert( { from, data } );
    }

    void add_directed_edge(int from, int to, PerEdgeData data = {})
    {
        edges_[from].insert({ to, data });
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

    const std::unordered_map<int, PerEdgeData>& out_nbrs( int v ) const
    {
        return edges_[v];
    }

private:
    std::vector<std::unordered_map<int, PerEdgeData>> edges_;
    std::vector<PerVertexData> vertexData_;
};

struct EmptyStruct {};

using SimpleGraph = Graph<EmptyStruct, EmptyStruct>;
