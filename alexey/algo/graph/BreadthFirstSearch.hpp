#pragma once
#include <vector>
#include <queue>
#include "algo/graph/Graph.hpp"

template<class VertexProcessCallback, class PerEdgeData, class PerVertexData>
void breadthFirstSearch( const UndirectedGraph<PerEdgeData, PerVertexData>& graph, VertexProcessCallback cbk, size_t startVertex = 0 )
{
    enum class Status {Unprocessed, Queued, Processed };
    std::vector<Status> status( graph.num_vertices(), Status::Unprocessed );
    std::queue<size_t> toProcess;
    toProcess.push( startVertex );
    while ( !toProcess.empty() )
    {
        auto v = toProcess.front();
        toProcess.pop();
        cbk( v );
        status[v] = Status::Processed;

        for ( auto pNei : graph.out_nbrs( v ) )
        {
            if ( status[pNei.first] == Status::Unprocessed )
            {
                toProcess.push( pNei.first );
                status[pNei.first] = Status::Queued;
            }
        }
    }
}
