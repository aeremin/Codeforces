#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/numbertheory/Residue.hpp"
using namespace std;

class Solver659G
{
public:
    void run();
};

void Solver659G::run()
{
    int n = read<int>();
    auto hh = readVector<int64_t>( n );
    
    deque<int> h( begin( hh ), end( hh ) );
    h.push_front( numeric_limits<int>::max() );
    h.push_back( numeric_limits<int>::max() );

    pair<CodeforcesResidue64, CodeforcesResidue64> ans, ansNext;
    for ( int i : range( 1, n + 1 ) ) {
        int64_t maxCutCurrent = h[i] - 1;
        int64_t maxCutCurrentR = min( h[i], h[i + 1] ) - 1;
        int64_t maxCutCurrentL = min( h[i], h[i - 1] ) - 1;
        int64_t maxCutCurrentRL = min( { h[i], h[i - 1], h[i + 1] } ) - 1;

        ansNext.first = ans.first * maxCutCurrentRL + maxCutCurrentR;
        ansNext.second = ans.second + ans.first * maxCutCurrentL + maxCutCurrent;
        ans = ansNext;
    }

    cout << ans.second;
}

class Solver659GTest : public ProblemTest {};

TEST_F(Solver659GTest, Example1)
{
    string input = R"(2
1 1
)";
    string output = R"(0
)";
    setInput(input);
    Solver659G().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659GTest, Example2)
{
    string input = R"(3
3 4 2
)";
    string output = R"(13
)";
    setInput(input);
    Solver659G().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


