#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/geometry/geomvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/638/problem/D
class Solver638D
{
public:
    void run();

    int n, m, k;
    vector<vector<string>> grid;
    bool isSet( const GeomVector3I& v ) const {
        return v[0] >= 0 && v[0] < n &&
               v[1] >= 0 && v[1] < m &&
               v[2] >= 0 && v[2] < k &&
               grid[v[0]][v[1]][v[2]] == '1';
    }
};

void Solver638D::run()
{
    cin >> n >> m >> k;
    grid.resize( n );
    for ( int i : range( n ) )
        grid[i] = readVector<string>( m );

    int res = 0;
    vector<GeomVector3I>  offs = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
    for ( int x : range(n) )
        for ( int y : range( m ) )
            for ( int z : range( k ) ) {
                GeomVector3I curr = { x, y, z };
                bool important = false;
                for ( auto& offsUp : offs )
                    for ( auto& offsDown : offs )
                        important = important || ( isSet( curr - offsUp ) && isSet( curr + offsDown ) &&
                                                   ( offsDown == offsUp || !isSet( curr - offsUp + offsDown ) ));
                if ( isSet( curr ) && important )
                    ++res;
            }

    cout << res;
}

class Solver638DTest : public ProblemTest {};

TEST_F( Solver638DTest, Example1 ) {
    string input = R"(2 2 3
000
000

111
111
)";
    string output = "2";
    setInput( input );
    Solver638D().run();
    EXPECT_EQ( output, getOutput() );
}

TEST_F( Solver638DTest, Example2 ) {
    string input = R"(3 3 3
111
111
111

111
111
111

111
111
111
)";
    string output = "19";
    setInput( input );
    Solver638D().run();
    EXPECT_EQ( output, getOutput() );
}

TEST_F( Solver638DTest, Example3 ) {
    string input = R"(1 1 10
0101010101
)";
    string output = "0";
    setInput( input );
    Solver638D().run();
    EXPECT_EQ( output, getOutput() );
}
