#pragma once
#include <cassert>
#include "algo/graph/Graph.hpp"

template<class PerEdgeData, class PerVertexData>
class BipartitionChecker
{
public:
    BipartitionChecker( const Graph<PerEdgeData, PerVertexData>& graph ) 
        : 
        graph_(graph),
        part_( graph_.num_vertices(), -1 )
    {
        for ( size_t i = 0; i < graph_.num_vertices(); ++i )
            if ( part_[i] == -1 )
                isBipartite_ = isBipartite_ && dfs_( i );
    }

    bool isBipartite() const { return isBipartite_; }

    std::pair<std::vector<size_t>, std::vector<size_t>> getSomePartitioning() const
    {
        assert( isBipartite() );
        std::pair<std::vector<size_t>, std::vector<size_t>> result;
        for ( size_t i = 0; i < part_.size(); ++i )
        {
            if ( part_[i] == 0 )
                result.first.push_back( i );
            else
                result.second.push_back( i );
        }
        return result;
    }

private:
    bool dfs_( size_t vInd )
    {
        part_[vInd] = currentPart_;
        currentPart_ = 1 - currentPart_;
        bool res = true;
        for ( auto p : graph_.out_nbrs( vInd ) )
        {
            auto neiInd = p.first;
            if ( part_[neiInd] == -1 )
                res = res && dfs_( neiInd );
            else
                res = res && ( currentPart_ == part_[neiInd] );
        }
        currentPart_ = 1 - currentPart_;
        return res;
    }

private:
    const Graph<PerEdgeData, PerVertexData>& graph_;
    bool isBipartite_ = true;
    std::vector<int> part_;
    int currentPart_ = 0;
};

template<class PerEdgeData, class PerVertexData>
BipartitionChecker<PerEdgeData, PerVertexData> makeBipartitionChecker(const Graph<PerEdgeData, PerVertexData>& graph)
{
    return BipartitionChecker<PerEdgeData, PerVertexData>(graph);
}