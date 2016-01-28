#include <Solvers/pch.h>
#include "algo/DisjointSet.hpp"
#include "algo/graph/Graph.hpp"
#include "algo/numbertheory/Residue.hpp"
#include "algo/graph/BipartitionChecker.hpp"

using namespace std;

class Solver554E
{
public:
    void run();
};

void Solver554E::run()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> love, hate;

    for ( int i = 0; i < m; ++i )
    {
        int a, b, c;
        cin >> a >> b >> c;
        if ( c == 1 )
            love.emplace_back( a - 1, b - 1 );
        else
            hate.emplace_back( a - 1, b - 1);
    }

    DisjointSet ds( n );
    for ( auto& p : love )
        ds.unionSets( p.first, p.second );

    SimpleGraph graph( n );
    for ( auto& p : hate )
        graph.addEdge( ds.rep( p.first ), ds.rep( p.second ) );

    if ( !BipartitionChecker<EmptyStruct, EmptyStruct>( graph ).isBipartite() )
    {
        cout << 0;
        return;
    }

    for ( auto& p : hate )
        ds.unionSets( p.first, p.second );

    CodeforcesResidue64 ans = 1;
    for ( int i = 1; i < ds.getComponentsCount(); ++i )
        ans *= 2;
    cout << ans;

}

class Solver554ETest : public ProblemTest {};

TEST_F(Solver554ETest, Example1)
{
    string input = R"(3 0
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver554E().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver554ETest, Example2)
{
    string input = R"(4 4
1 2 1
2 3 1
3 4 0
4 1 0
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver554E().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver554ETest, Example3)
{
    string input = R"(4 4
1 2 1
2 3 1
3 4 0
4 1 1
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver554E().run();
    EXPECT_EQ(output, getOutput());
}


