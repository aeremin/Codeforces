#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/geometry/geomvector.hpp"
#include "math/sign.h"
using namespace std;

class Solver659D
{
public:
    void run();

    GeomVector2I normalize( const GeomVector2I& v ) const {
        return{ sgn( v[0] ), sgn( v[1] ) };
    }

    GeomVector2I rotateLeft( const GeomVector2I& v ) const {
        return{ -v[1], v[0] };
    }
};

void Solver659D::run()
{
    int nPts;
    cin >> nPts;
    vector<GeomVector2I> pts( nPts );
    for ( auto& pt : pts )
        cin >> pt[0] >> pt[1];

    int ans = 0;

    for ( int i : range( nPts ) ) {
        auto curr = pts[( i + 1 ) % nPts] - pts[i];
        auto next = pts[( i + 2 ) % nPts] - pts[( i + 1 ) % nPts];
        if ( normalize( next ) == normalize( rotateLeft( curr ) )) ans++;
    }
    cout << ans;
}

class Solver659DTest : public ProblemTest {};

TEST_F(Solver659DTest, Example1)
{
    string input = R"(6
0 0
0 1
1 1
1 2
2 2
2 0
0 0
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver659D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver659DTest, Example2)
{
    string input = R"(16
1 1
1 5
3 5
3 7
2 7
2 9
6 9
6 7
5 7
5 3
4 3
4 4
3 4
3 2
5 2
5 1
1 1
)";
    string output = R"(6
)";
    output.pop_back();
    setInput(input);
    Solver659D().run();
    EXPECT_EQ(output, getOutput());
}


