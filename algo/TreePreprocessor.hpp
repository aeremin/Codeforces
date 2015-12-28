#pragma once
#include "Graph.hpp"
#include <stdint.h>

template<class PerEdgeData, class PerVertexData>
class TreePreprocessor
{
public:
    TreePreprocessor( const Graph<PerEdgeData, PerVertexData>& graph )
        : graph_( graph ),
        depths_( graph.vertexCount(), -1 ),
        binaryLiftData_( graph.vertexCount() )
    {
        depths_[0] = 0;
        binaryLiftData_[0].push_back( { -1, {}, {} } );
        dfs_( 0 );
        calculateBinaryLifts_();
    }

    struct LiftData
    {
        int parent;
        PerEdgeData edgeData;
        PerVertexData vertexData;
    };

    LiftData lift( int vInd, size_t dist )
    {
        LiftData result = { vInd, {}, {} };
        size_t jumpLog = 0;
        while ( dist > 0 )
        {
            if ( dist % 2 == 0 )
            {
                dist /= 2;
                ++jumpLog;
            }
            else
            {
                --dist;
                auto liftData = binaryLiftData_[result.parent][jumpLog];
                result.parent = liftData.parent;
                result.edgeData = concatenate( result.edgeData, liftData.edgeData );
                result.vertexData = concatenate( result.vertexData, liftData.vertexData );
            }
        }
        return result;
    }

    int leastCommonAncestor( int vInd1, int vInd2 )
    {
        if ( depths_[vInd1] < depths_[vInd2] ) swap( vInd1, vInd2 );
        vInd1 = lift( vInd1, depths_[vInd1] - depths_[vInd2] ).parent;
        if ( vInd1 == vInd2 ) return vInd1;
        int maxJumpLog = 0;
        while ( ( 1 << maxJumpLog ) <= depths_[vInd1] ) ++maxJumpLog;
        return lcaInternal_( vInd1, vInd2, maxJumpLog );
    }

    pair<PerEdgeData, PerVertexData> valueOnPath( int vInd1, int vInd2 )
    {
        auto lca = leastCommonAncestor( vInd1, vInd2 );
        auto dist1 = depths_[vInd1] - depths_[lca];
        auto lift1 = lift( vInd1, dist1 );
        auto dist2 = depths_[vInd2] - depths_[lca];
        auto lift2 = lift( vInd2, dist2 );
        return{ concatenate( lift1.edgeData, lift2.edgeData ),
                concatenate( concatenate( lift1.vertexData, lift2.vertexData ), graph_.getVertexData( lca ) ) };

    }

private:
    const Graph<PerEdgeData, PerVertexData>& graph_;
    vector<int> depths_;

    vector<vector<LiftData>> binaryLiftData_;

    int lcaInternal_( int vInd1, int vInd2, int maxJumpLog )
    {
        if ( vInd1 == vInd2 ) return vInd1;
        for ( auto jumpLog = maxJumpLog - 1; jumpLog >= 0; --jumpLog )
        {
            auto parent1 = binaryLiftData_[vInd1][jumpLog].parent;
            auto parent2 = binaryLiftData_[vInd2][jumpLog].parent;
            if ( parent1 != parent2 ) return lcaInternal_( parent1, parent2, jumpLog );
        }
        return binaryLiftData_[vInd1][0].parent;
    }

    void dfs_( int vInd )
    {
        for ( auto& edge : graph_.vertexNeighbors( vInd ) )
        {
            if ( binaryLiftData_[edge.first].empty() )
            {
                binaryLiftData_[edge.first].push_back( { vInd, edge.second, graph_.getVertexData( edge.first ) } );
                depths_[edge.first] = depths_[vInd] + 1;
                dfs_( edge.first );
            }
        }
    }

    void calculateBinaryLifts_()
    {
        for ( uint64_t jumpLog = 1; ( 1 << jumpLog ) < graph_.vertexCount(); ++jumpLog )
        {
            for ( size_t iVertex = 0; iVertex < graph_.vertexCount(); ++iVertex )
            {
                auto firstHalfJumpData = binaryLiftData_[iVertex][jumpLog - 1];
                if ( firstHalfJumpData.parent == -1 )
                    binaryLiftData_[iVertex].push_back( { -1, {}, {} } );
                else
                {
                    auto secondHalfJumpData = binaryLiftData_[firstHalfJumpData.parent][jumpLog - 1];
                    LiftData concatenated;
                    concatenated.parent = secondHalfJumpData.parent;
                    concatenated.edgeData = concatenate( firstHalfJumpData.edgeData, secondHalfJumpData.edgeData );
                    concatenated.vertexData = concatenate( firstHalfJumpData.vertexData, secondHalfJumpData.vertexData );
                    binaryLiftData_[iVertex].push_back( move( concatenated ) );
                }
            }
        }
    }
};
