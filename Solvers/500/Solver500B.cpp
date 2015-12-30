#include <Solvers/pch.h>
#include "algo/DisjointSet.hpp"

using namespace std;

class Solver500B
{
public:
    void run();
};

void Solver500B::run()
{
    int n;
    cin >> n;

    vector<int> p(n);
    for ( auto& t : p )
        cin >> t;

    DisjointSet disjointSet( n );

    vector<vector<char>> can;
    for ( int i = 0; i < n; ++i )
    {
        can.push_back( vector<char>() );
        for ( int j = 0; j < n; ++j )
        {
            char canc;
            cin >> canc;
            can[i].push_back( canc );
        }
    }

    for ( int i = 0; i < n; ++i )
        for ( int j = i + 1; j < n; ++j )
        {
            // j > i
            if ( can[i][j] == '1' )
                disjointSet.unionSets( i, j );
        }

    vector<int> res( n );
    vector<bool> taken( n, false );

    for ( int i = 0; i < n; ++i )
    {
        if ( taken[i] ) continue;

        vector<pair<int, int>> group;
        for ( int j = i; j < n; ++j )
        {
            if ( disjointSet.inSameSet(i, j) )
            {
                group.push_back( make_pair( p[j], j ) );
                taken[j] = true;
            }
        }

        sort( begin( group ), end( group ), []( pair<int, int> a, pair<int, int> b )
        {
            return a.first < b.first;
        } );

        auto groupcopy = group;
        sort( begin( groupcopy ), end( groupcopy ), []( pair<int, int> a, pair<int, int> b )
        {
            return a.second < b.second;
        } );

        for ( int k = 0; k < group.size(); ++k )
        {
            res[groupcopy[k].second] = group[k].first;
        }
    }

    for ( int i = 0; i < n; ++i )
        cout << res[i] << ' ';

}

class Solver500BTest : public ProblemTest
{
};

TEST_F( Solver500BTest, Example1 )
{
    setInput(
R"(
7
5 2 4 3 6 7 1
0001001
0000000
0000010
1000001
0000000
0010000
1001000
)");
    Solver500B().run();
    EXPECT_EQ("1 2 4 3 6 7 5 ", getOutput());
}

TEST_F( Solver500BTest, Example2 )
{
    setInput(
R"(
5
4 2 1 5 3
00100
00011
10010
01101
01010
)" );
    Solver500B().run();
    EXPECT_EQ("1 2 3 4 5 ", getOutput());
}
