#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/graph/Graph.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/638/problem/C
class Solver638C
{
public:
    void run();

    std::unique_ptr<Graph<int, EmptyStruct>> g;
    vector<vector<int>> roadsToFixPerDay;

    void dfs( int v, int p, int forbiddenDay ) {
        auto deg = g->out_nbrs( v ).size();
        if ( deg > roadsToFixPerDay.size() )
            roadsToFixPerDay.resize( deg );
        int day = ( forbiddenDay == 0 ) ? 1 : 0;
        for ( auto[vertex, payload] : g->out_nbrs( v ) ) {
            if ( vertex == p ) continue;
            roadsToFixPerDay[day].push_back(payload);
            dfs( vertex, v, day );
            ++day;
            if ( day == forbiddenDay ) ++day;
        }
    }
};

void Solver638C::run()
{
    int nVertices;
    cin >> nVertices;
    g.reset(new Graph<int, EmptyStruct>( nVertices ));
    for ( int i : range( nVertices - 1 ) ) {
        int a, b;
        cin >> a >> b;
        g->add_edge( a - 1, b - 1, i + 1 );
    }

    dfs( 0, 0, -1 );

    cout << roadsToFixPerDay.size() << '\n';
    for ( auto& toFix : roadsToFixPerDay ) {
        cout << toFix.size() << " ";
        for ( auto& r : toFix )
            cout << r << " ";
        cout << '\n';
    }
}

class Solver638CTest : public ProblemTest {};

TEST_F( Solver638CTest, Example1 ) {
    string input = R"(4
1 2
3 4
3 2
)";
    string output = R"(2
2 1 2 
1 3 
)";
    setInput( input );
    Solver638C().run();
    EXPECT_EQ( output, getOutput() );
}

TEST_F( Solver638CTest, Example2 ) {
    string input = R"(6
3 4
5 4
3 2
1 3
4 6
)";
    string output = R"(3
2 4 2 
1 1 
2 5 3 
)";
    setInput( input );
    Solver638C().run();
    EXPECT_EQ( output, getOutput() );
}