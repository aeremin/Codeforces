#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/graph/Graph.hpp"
#include "algo/graph/max_flow_push_relabel.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/546/problem/E
class Solver546E
{
public:
    void run();
};

void Solver546E::run()
{
    int nCities, nRoads;
    cin >> nCities >> nRoads;
    auto cntBefore = readVector<int>( nCities );
    auto cntAfter = readVector<int>( nCities );

    Graph<int, EmptyStruct> g( 2 * nCities + 2 );
    for ( int i : range( nRoads ) ) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g.add_directed_edge( a, b + nCities, numeric_limits<int>::max() );
        g.add_directed_edge( b, a + nCities, numeric_limits<int>::max() );
    }

    for ( int i : range( nCities ) ) {
        g.add_directed_edge( i, i + nCities, numeric_limits<int>::max() );
        g.add_directed_edge( 2 * nCities, i, cntBefore[i] );
        g.add_directed_edge( i + nCities, 2 * nCities + 1, cntAfter[i] );
    }

    auto neededFlow = max( accumulate( begin( cntBefore ), end( cntBefore ), 0 ),
                           accumulate( begin( cntAfter ), end( cntAfter ), 0 ) );

    MaxFlowPushRelabel<int, EmptyStruct> flowCalc( g );
    auto flow = flowCalc.GetMaxFlow( 2 * nCities, 2 * nCities + 1 );
    if ( flow.totalFlow != neededFlow ) {
        cout << "NO";
        return;
    }

    cout << "YES\n";
    vector<vector<int>> ans( nCities, vector<int>( nCities ) );
    for ( auto u : range( nCities ) )
        for ( auto[vertex, payload] : flow.flow.out_nbrs( u ) )
            ans[u][vertex - nCities] += payload;

    for ( auto& line : ans ) {
        printVector( line );
        print( '\n' );
    }
}

class Solver546ETest : public ProblemTest {};

TEST_F(Solver546ETest, Example1)
{
    string input = R"(4 4
1 2 6 3
3 5 3 1
1 2
2 3
3 4
4 2
)";
    string output = R"(YES
1 0 0 0
2 0 0 0
0 2 3 1
0 3 0 0
)";
    setInput(input);
    Solver546E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver546ETest, Example2)
{
    string input = R"(2 0
1 2
2 1
)";
    string output = "NO";
    setInput(input);
    Solver546E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


