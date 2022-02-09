#include <Solvers/pch.h>
#include "algo/sort_with_mapping.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/620/problem/D
class Solver620D
{
public:
    void run();
    vector<tuple<int64_t, int, int>> sumsOfTwo( const vector<int64_t>& v ) const
    {
        vector<tuple<int64_t, int, int>> r;
        for ( size_t i = 0; i < v.size(); ++i )
            for ( size_t j = i + 1; j < v.size(); ++j )
                r.push_back( make_tuple(v[i] + v[j], i, j));
        return r;
    }
};

void Solver620D::run()
{
    int n; cin >> n;
    vector<int64_t> a( n );
    for ( auto& elt : a ) cin >> elt;

    int m; cin >> m;
    vector<int64_t> b( m );
    for ( auto& elt : b ) cin >> elt;

    
    auto suma = accumulate( begin( a ), end( a ), int64_t(0) );
    auto sumb = accumulate( begin( b ), end( b ), int64_t( 0 ) );
    auto diff = suma - sumb;

    auto aa = a;
    auto bb = b;

    vector<size_t> revA, revB;
    sortWithMappings( aa, nullptr, &revA );
    sortWithMappings( bb, nullptr, &revB );

    auto a2 = sumsOfTwo( aa );
    auto b2 = sumsOfTwo( bb );
    sort( begin( a2 ), end( a2 ) );
    sort( begin( b2 ), end( b2 ) );


    auto bestDiff = abs( diff );

    vector<pair<int, int>> ans;
    for ( size_t i = 0; i < a.size(); ++i )
        for ( size_t j = 0; j < b.size(); ++j )
        {
            auto currDiff = diff + 2 * ( b[j] - a[i] );
            if ( abs( currDiff ) < bestDiff )
            {
                bestDiff = abs( currDiff );
                ans = { { i + 1, j + 1 } };
            }
        }


    for ( auto s1 : a2 )
    {
        auto mostWanted = make_tuple( -diff / 2 + get<0>( s1 ), 0, 0 );
        auto lb = lower_bound( begin( b2 ), end( b2 ), mostWanted );
        vector<decltype( lb )> itersToCheck;
        if ( lb != end( b2 ) ) itersToCheck.push_back( lb );
        if ( lb != begin( b2 ) ) itersToCheck.push_back( lb - 1 );
        for ( auto it : itersToCheck )
        {
            auto currDiff = diff + 2 * ( get<0>( *it ) - get<0>( s1 ) );
            if ( abs( currDiff ) < bestDiff )
            {
                bestDiff = abs( currDiff );
                ans = { { revA[get<1>( s1 )] + 1, revB[get<1>( *it )] +1 }, { revA[get<2>( s1 )] + 1, revB[get<2>( *it )] + 1} };
            }
        }
    }

    cout << bestDiff << "\n";
    cout << ans.size() << "\n";
    for ( auto p : ans )
        cout << p.first << " " << p.second << "\n";
}

class Solver620DTest : public ProblemTest
{
};

TEST_F( Solver620DTest, Example1 )
{
    setInput("4          100 100 100 100              4              1 1 1 1");
    Solver620D().run();
    EXPECT_EQ("0\n2\n1 1\n2 2\n", getOutput());
}
