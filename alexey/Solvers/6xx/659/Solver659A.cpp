#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/659/problem/A
class Solver659A
{
public:
    void run();
};

void Solver659A::run()
{
    int n, a, b;
    cin >> n >> a >> b;
    auto res = ( a + b ) % n;
    if ( res < 0 ) res += n;
    if ( res == 0 ) res = n;
    cout << res;
}

class Solver659ATest : public ProblemTest {};

TEST_F(Solver659ATest, Example1)
{
    string input = R"(6 2 -5
)";
    string output = R"(3
)";
    setInput(input);
    Solver659A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659ATest, Example2)
{
    string input = R"(5 1 3
)";
    string output = R"(4
)";
    setInput(input);
    Solver659A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659ATest, Example3)
{
    string input = R"(3 2 7
)";
    string output = R"(3
)";
    setInput(input);
    Solver659A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


