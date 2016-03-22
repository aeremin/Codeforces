#include <gtest/gtest.h>
#include "algo/graph/max_flow_push_relabel.h"
#include <cstdint>

using namespace std;

TEST( MaxFlowPushRelabelTest, OneDirectedEdge ) {
    Graph<int, EmptyStruct> g(2);
    g.add_undirected_edge( 0, 1, 7 );
    MaxFlowPushRelabel<int, EmptyStruct> calc( g );
    EXPECT_EQ(7, calc.GetMaxFlow( 0, 1 ).totalFlow);
}

TEST( MaxFlowPushRelabelTest, ChainGraph ) {
    Graph<int, EmptyStruct> g( 5 );
    g.add_undirected_edge( 0, 1, 5 );
    g.add_undirected_edge( 1, 2, 7 );
    g.add_undirected_edge( 2, 3, 3 );
    g.add_undirected_edge( 3, 4, 4 );

    MaxFlowPushRelabel<int, EmptyStruct> calc( g );
    EXPECT_EQ( 3, calc.GetMaxFlow( 0, 4 ).totalFlow );
}

TEST( MaxFlowPushRelabelTest, FourVerticesExample ) {
    Graph<int, EmptyStruct> g( 4 );
    map<pair<int, int>, int> caps = { { { 0, 1 }, 72 }, { { 0, 2 }, 272 }, { { 0, 3 }, 132 },
                                      { { 1, 2 }, 50 }, { { 1, 3 }, 308 }, { { 2, 3 }, 36 } };
    for ( auto edge : caps )
        g.add_undirected_edge( edge.first.first, edge.first.second, edge.second );

    MaxFlowPushRelabel<int, EmptyStruct> calc( g );
    EXPECT_EQ( 240, calc.GetMaxFlow( 0, 3 ).totalFlow);
    EXPECT_EQ( 322, calc.GetMaxFlow( 0, 2 ).totalFlow);
    EXPECT_EQ( 0, calc.GetMaxFlow( 2, 0 ).totalFlow);
}

TEST( MaxFlowPushRelabelTest, NotAccessibleSink ) {
    Graph<int, EmptyStruct> g( 3 );
    g.add_undirected_edge( 0, 1, 10 );

    MaxFlowPushRelabel<int, EmptyStruct> calc( g );
    EXPECT_EQ( 0, calc.GetMaxFlow( 0, 2 ).totalFlow);
}