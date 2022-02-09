#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/633/problem/A
class Solver633A
{
public:
    void run();
};

void Solver633A::run()
{
    int a, b, c;
    cin >> a >> b >> c;
    bool can = false;
    for ( int i : range( c / a + 1 ) )
        can = can || ( ( c - i * a ) % b == 0 );
    if ( can ) cout << "Yes";
    else cout << "No";
}

class Solver633ATest : public ProblemTest {};

TEST_F(Solver633ATest, Example1)
{
    string input = R"(4 6 15
)";
    string output = R"(No
)";
    setInput(input);
    Solver633A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver633ATest, Example2)
{
    string input = R"(3 2 7
)";
    string output = R"(Yes
)";
    setInput(input);
    Solver633A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver633ATest, Example3)
{
    string input = R"(6 11 6
)";
    string output = R"(Yes
)";
    setInput(input);
    Solver633A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


