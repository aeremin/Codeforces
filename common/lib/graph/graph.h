#pragma once
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <optional>
#include "util/getters.h"

constexpr int kInvalidGraphVertex = -1;

template<bool Directed, class PerEdgeData, class PerVertexData>
class Graph
{

public:
    using NeighborMap = std::unordered_map<int, PerEdgeData>;

    Graph( int nVertices )
        :
        edges_(nVertices),
        vertexData_(nVertices)
    {
    }

    Graph( std::vector<PerVertexData> vertexData )
        :
        edges_(vertexData.size()),
        vertexData_(move(vertexData))
    {
    }

    template<bool IsDirected = Directed, typename = typename std::enable_if<!IsDirected>::type>
    void add_edge( int from, int to, PerEdgeData data = {} )
    {
        edges_[from].insert( { to, data } );
        edges_[to].insert( { from, data } );
    }

    template<bool IsDirected = Directed, typename = typename std::enable_if<IsDirected>::type>
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

    void expand_to_num_vertices(int new_num_vertices) {
        if (new_num_vertices <= num_vertices())
            return;
        edges_.resize(new_num_vertices);
        vertexData_.resize(new_num_vertices);
    }

    const NeighborMap& out_nbrs( int v ) const
    {
        return edges_[v];
    }

    bool has_edge(int from, int to) const {
        return get_edge(from, to).has_value();
    }
    
    std::optional<PerEdgeData> get_edge(int from, int to) const {
        return maybe_get(out_nbrs(from), to);
    }

private:
    std::vector<NeighborMap> edges_;
    std::vector<PerVertexData> vertexData_;
};

struct EmptyStruct {};

template<class PerEdgeData = EmptyStruct, class PerVertexData = EmptyStruct>
using DirectedGraph = Graph<true, PerEdgeData, PerVertexData>;

template<class PerEdgeData = EmptyStruct, class PerVertexData = EmptyStruct>
using UndirectedGraph = Graph<false, PerEdgeData, PerVertexData>;
