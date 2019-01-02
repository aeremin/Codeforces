#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/DisjointSet.hpp"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/659/problem/E
class Solver659E
{
public:
    void run();
};

void Solver659E::run()
{
    int nCities, nRoads;
    cin >> nCities >> nRoads;
    auto roads = readVector<int>( 2 * nRoads );
    DisjointSet ds( nCities );
    for ( int i : range( nRoads ) )
        ds.unionSets( roads[2 * i] - 1, roads[2 * i + 1] - 1 );
    
    unordered_map<int, pair<int, int>> compsSize;
    for ( int i : range( nCities ) )
        compsSize[ds.rep( i )].first++;

    for ( int i : range( nRoads ) ) {
        auto comp = ds.rep( roads[2 * i] - 1 );
        compsSize[comp].second++;
    }

    int ans = 0;
    for ( auto comp : compsSize )
        if ( comp.second.first - 1 == comp.second.second )
            ++ans;

    cout << ans;
}

class Solver659ETest : public ProblemTest {};

TEST_F(Solver659ETest, Example1)
{
    string input = R"(4 3
2 1
1 3
4 3
)";
    string output = R"(1
)";
    setInput(input);
    Solver659E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659ETest, Example2)
{
    string input = R"(5 5
2 1
1 3
2 3
2 5
4 3
)";
    string output = R"(0
)";
    setInput(input);
    Solver659E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659ETest, Example3)
{
    string input = R"(6 5
1 2
2 3
4 5
4 6
5 6
)";
    string output = R"(1
)";
    setInput(input);
    Solver659E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


