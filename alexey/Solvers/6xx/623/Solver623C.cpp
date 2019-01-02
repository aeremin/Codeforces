#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"
#include "algo/io/readvector.hpp"
#include "algo/FunctorIterator.hpp"
#include "math/sqr.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/623/problem/C
class Solver623C
{
public:
    void run();
};

void Solver623C::run()
{
    size_t nPts;
    cin >> nPts;
    auto pts = readVector<GeomVector2I>(nPts);
    sort(begin(pts), end(pts));
    vector<int64_t> x, y;
    for (auto pt : pts)
    {
        x.push_back(pt[0]);
        y.push_back(pt[1]);
    }

    vector<pair<int64_t, int64_t>> minMaxPrefixes(nPts), minMaxSuffixes(nPts);
    minMaxPrefixes.front() = { y.front(), y.front() };
    minMaxSuffixes.back() =  { y.back(), y.back() };
    for (size_t i = 1; i < nPts; ++i)
    {
        minMaxPrefixes[i] = { min(y[i], minMaxPrefixes[i - 1].first), max(y[i], minMaxPrefixes[i - 1].second) };
        minMaxSuffixes[nPts - 1 - i] = { min(y[nPts - 1 - i], minMaxSuffixes[nPts - i].first), max(y[nPts - 1 - i], minMaxSuffixes[nPts - i].second) };
    }

    auto getMinMaxY = [&]( int l, int r )  -> pair<int64_t, int64_t>
    { 
        if (r == l)
            return { 0, 0 };
        if (l == 0)
            return minMaxPrefixes[r - 1];
        else
            return minMaxSuffixes[l];
    };

    
    auto fullMinMaxY = getMinMaxY(0, nPts);

    int64_t fullYDiam = fullMinMaxY.second - fullMinMaxY.first;
    int64_t fullXDiam = x.back() - x.front();
    int64_t fullDiam = min(fullXDiam, fullYDiam);

    auto canHaveDiameterLessOrEqual = [&]( int64_t diamSquared )->int
    {
        int64_t diam = sqrt( diamSquared );

        if (fullDiam <= diam)
            return 1;

        for ( auto xc : x )
        {
            int64_t xMax, xMin;
            if (xc > 0)
            {
                xMax = xc;
                xMin = max(-xc, xc - diam);
            }
            else
            {
                xMin = xc;
                xMax = min(-xc, xc + diam);
            }
            
            auto xl = lower_bound( begin( x ), end( x ), xMin ) - begin( x );
            auto xr = upper_bound( begin( x ), end( x ), xMax ) - begin( x );
            
            auto minMaxYLeft  = getMinMaxY(0, xl);
            auto minMaxYRight = getMinMaxY(xr, nPts);
            auto yMax = max(minMaxYLeft.second, minMaxYRight.second);
            auto yMin = min(minMaxYLeft.first, minMaxYRight.first);
            if ( max( { sqr(yMax) + sqr(xc), sqr(yMin) + sqr(xc), sqr(yMax - yMin) } ) <= diamSquared )
                return 1;
        }
        return 0;
    };

    auto l = makeFunctorIterator( int64_t(0), canHaveDiameterLessOrEqual );
    auto r = makeFunctorIterator( sqr(fullDiam) + 1, canHaveDiameterLessOrEqual );
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
    EXPECT_EQ_FUZZY(getOutput(), output);
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
    EXPECT_EQ_FUZZY(getOutput(), output);
}


