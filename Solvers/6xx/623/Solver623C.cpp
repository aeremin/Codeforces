#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"
#include "algo/io/readvector.hpp"
#include "algo/binaryfunctors/Min.hpp"
#include "algo/binaryfunctors/Max.hpp"
#include "algo/updatetypes/SetTo.hpp"
#include "algo/updateappliers/SetToIdempotent.h"
#include "algo/SegmentTree.hpp"
#include "algo/FunctorIterator.hpp"

using namespace std;

class Solver623C
{
public:
    void run();
};

void Solver623C::run()
{
    size_t nPts;
    cin >> nPts;
    auto pts = readVector<GeomVector2I>( nPts );
    sort( begin( pts ), end( pts ) );
    vector<int> x, y;
    for (auto pt : pts )
    {
        x.push_back( pt[0] );
        y.push_back( pt[1] );
    }

    auto maxSegmentTree = makeSegmentTree( y, binaryFunctors::Max<int>(), updateTypes::SetTo<int>() );
    auto minSegmentTree = makeSegmentTree( y, binaryFunctors::Min<int>(), updateTypes::SetTo<int>() );

    int64_t fullYDiam = maxSegmentTree.getValueOnSegment( 0, nPts ) - minSegmentTree.getValueOnSegment( 0, nPts );
    int64_t fullXDiam = x.back() - x.front();

    auto getMaxY = [&]( int l, int r )  {   return ( r > l ) ? maxSegmentTree.getValueOnSegment( l, r ) : 0;  };
    auto getMinY = [&]( int l, int r )  {   return ( r > l ) ? minSegmentTree.getValueOnSegment( l, r ) : 0;  };

    auto canHaveDiameterLessOrEqual = [&]( int64_t diamSquared )->int
    {
        int64_t diam = sqrt( diamSquared );

        if ( fullYDiam <= diam || fullXDiam <= diam )
            return 1;

        for ( auto xc : x )
        {
            auto xl = lower_bound( begin( x ), end( x ), xc - abs(xc) ) - begin( x );
            auto xr = upper_bound( begin( x ), end( x ), xc + abs(xc) ) - begin( x );
            auto yMax = max( getMaxY( 0, xl ), getMaxY( xr, nPts ) );
            auto yMin = min( getMinY( 0, xl ), getMinY( xr, nPts ) );
            if ( max( { yMax * yMax + xc * xc, yMin * yMin + xc * xc, ( yMax - yMin ) * ( yMax - yMin ) } ) <= diamSquared )
                return 1;
        }
        return 0;
    };

    auto l = makeFunctorIterator( int64_t(0), canHaveDiameterLessOrEqual );
    auto r = makeFunctorIterator( numeric_limits<int64_t>::max(), canHaveDiameterLessOrEqual );
    auto res = lower_bound( l, r, 1 ).getParameter();
    cout << res;
}

class Solver623CTest : public ProblemTest {};

TEST_F(Solver623CTest, Example1)
{
    string input = R"(3
1 10
1 20
1 30
)";
    string output = R"(0)";
    setInput(input);
    Solver623C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver623CTest, Example2)
{
    string input = R"(2
1 10
10 1
)";
    string output = R"(2)";
    setInput(input);
    Solver623C().run();
    EXPECT_EQ(output, getOutput());
}


