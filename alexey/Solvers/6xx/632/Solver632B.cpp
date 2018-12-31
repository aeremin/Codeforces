#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

class Solver632B
{
public:
    void run();
};

void Solver632B::run()
{
    int n = read<int>();
    auto pows = readVector<int64_t>( n );
    auto ownership = readVector<char>( n );

    int64_t startBobPower = 0;
    for ( int i : range( n ) )
        if ( ownership[i] == 'B' )
            startBobPower += pows[i];

    int64_t currDiff = 0;
    int64_t maxPow = startBobPower;
    for ( int i : range( n ) )
    {
        int sgn = ( ownership[i] == 'B' ) ? -1 : 1;
        currDiff += sgn * pows[i];
        relax_max( maxPow, startBobPower + currDiff );
    }

    currDiff = 0;
    for ( int j : range( n ) )
    {
        int i = n - 1 - j;
        int sgn = ( ownership[i] == 'B' ) ? -1 : 1;
        currDiff += sgn * pows[i];
        relax_max( maxPow, startBobPower + currDiff );
    }

    cout << maxPow;
}

class Solver632BTest : public ProblemTest {};

TEST_F(Solver632BTest, Example1)
{
    string input = R"(5
1 2 3 4 5
ABABA
)";
    string output = R"(11
)";
    setInput(input);
    Solver632B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver632BTest, Example2)
{
    string input = R"(5
1 2 3 4 5
AAAAA
)";
    string output = R"(15
)";
    setInput(input);
    Solver632B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver632BTest, Example3)
{
    string input = R"(1
1
B
)";
    string output = R"(1
)";
    setInput(input);
    Solver632B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


