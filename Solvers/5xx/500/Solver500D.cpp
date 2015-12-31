#include <Solvers/pch.h>

using namespace std;

class Solver500D
{
public:
    void run();

    vector<vector<int>> g;
    int nCities;

    vector<int> color;

    vector<int> time_in, time_out;
    int dfs_timer = 0;

    void dfs( int v )
    {
        time_in[v] = dfs_timer++;
        color[v] = 1;
        for ( auto it = g[v].begin(); it != g[v].end(); ++it )
            if ( color[*it] == 0 )
                dfs( *it );
        color[v] = 2;
        time_out[v] = dfs_timer++;
    }

    struct Road
    {
        int from, to, len;
    };
};

void Solver500D::run()
{
    int nCities;
    cin >> nCities;
    g.resize( nCities );
    time_in.resize( nCities );
    time_out.resize( nCities );
    color.resize( nCities );

    vector<Road> roads;
    for ( int i = 1; i < nCities; ++i )
    {
        Road road;
        cin >> road.from >> road.to >> road.len;
        roads.push_back( road );
        g[road.from - 1].push_back( road.to - 1 );
        g[road.to - 1].push_back( road.from - 1 );
    }

    dfs( 0 );

    vector<double> roadProb;

    double fullProb = double( nCities ) * double( nCities - 1 ) * double( nCities - 2 );

    for ( int i = 0; i < roads.size(); ++i )
    {
        Road r = roads[i];
        int index1 = r.from - 1;
        int index2 = r.to - 1;
        int index;
        if ( time_in[index1] > time_in[index2] ) index = index1; else index = index2;
        double part1 = ( time_out[index] - time_in[index] ) / 2 + 1;
        double part2 = nCities - part1;

        double prob1 = max( 0.0, part1 * ( part1 - 1 ) * ( part1 - 2 ) );
        double prob2 = max( 0.0, part2 * ( part2 - 1 ) * ( part2 - 2 ) );

        roadProb.push_back( 1 - ( prob1 + prob2 ) / fullProb );
    }

    double ev = 0;
    for ( int i = 0; i < roadProb.size(); ++i )
        ev += 2 * roads[i].len * roadProb[i];

    int nQueries;
    cin >> nQueries;
    for ( int iQuery = 0; iQuery < nQueries; ++iQuery )
    {
        int roadInd, newLen;
        cin >> roadInd >> newLen;
        roadInd--;
        ev += 2 * roadProb[roadInd] * ( newLen - roads[roadInd].len );
        roads[roadInd].len = newLen;
        cout << setprecision( 10 ) << fixed << ev << "\n";
    }
}

class Solver500DTest : public ProblemTest
{
};

TEST_F( Solver500DTest, Example1 )
{
    setInput(R"(
3
2 3 5
1 3 3
5
1 4
2 2
1 2
2 1
1 1
)");
    Solver500D().run();
    string expectedAns =
R"(14.0000000000
12.0000000000
8.0000000000
6.0000000000
4.0000000000
)";
    EXPECT_EQ( expectedAns, getOutput() );
}

TEST_F( Solver500DTest, Example2 )
{
    setInput( R"(
6
1 5 3
5 3 2
6 1 7
1 4 4
5 2 3
5
1 2
2 1
3 5
4 1
5 2
)" );
    Solver500D().run();
    string expectedAns =
R"(19.6000000000
18.6000000000
16.6000000000
13.6000000000
12.6000000000
)";
    EXPECT_EQ( expectedAns, getOutput() );
}
