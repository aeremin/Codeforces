#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/652/problem/C
class Solver652C
{
public:
    void run();
};

void Solver652C::run()
{
    int n, m;
    cin >> n >> m;
    auto p = readVector<int>( n );
    vector<int> pInv( n + 1 );
    for ( int i : range( n ) )
        pInv[p[i]] = i;
    
    auto bannedPairs = readVector<int>( 2 * m );
    vector<vector<int>> banned( n + 1 );
    for ( int i : range( m ) ) {
        auto elt1 = bannedPairs[2 * i];
        auto elt2 = bannedPairs[2 * i + 1];
        banned[elt1].push_back( elt2 );
        banned[elt2].push_back( elt1 );
    }

    vector<int> maxR( n );
    for ( int i : range( n ) ) {
        maxR[i] = n - 1;
        for ( auto foe : banned[p[i]] )
        {
            auto foePos = pInv[foe];
            if ( foePos > i )
                relax_min( maxR[i], foePos - 1 );
        }
    }

    int64_t ans = 0;
    int l = n - 1;
    for ( int r = n - 1; r >= 0; --r ) {
        while ( l > 0 && maxR[l - 1] >= r ) --l;
        ans += r - l + 1;
    }

    cout << ans;
}

class Solver652CTest : public ProblemTest {};

TEST_F(Solver652CTest, Example1)
{
    string input = R"(4 2
1 3 2 4
3 2
2 4
)";
    string output = R"(5
)";
    setInput(input);
    Solver652C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver652CTest, Example2)
{
    string input = R"(9 5
9 7 2 3 1 4 6 5 8
1 6
4 5
2 7
7 2
2 7
)";
    string output = R"(20
)";
    setInput(input);
    Solver652C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F( Solver652CTest, Example3 ) {
    string input = R"(9 0
9 7 2 3 1 4 6 5 8
)";
    string output = R"(45
)";
    setInput( input );
    Solver652C().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}

TEST_F( Solver652CTest, Example4 ) {
    string input = R"(4 3
1 2 3 4
1 2
3 2
3 4
)";
    string output = R"(4
)";
    setInput( input );
    Solver652C().run();
    EXPECT_EQ_FUZZY( output, getOutput() );
}