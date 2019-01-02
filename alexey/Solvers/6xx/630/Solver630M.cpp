#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/630/problem/M
class Solver630M
{
public:
    void run();
};

void Solver630M::run()
{
    int64_t n;
    cin >> n;
    n = n % 360;
    if (n < 0) n += 360;
    if (n >= 315 || n <= 45)
        cout << 0;
    if (n > 45 && n <= 135)
        cout << 1;
    if (n > 135 && n <= 225)
        cout << 2;
    if (n > 225 && n < 315)
        cout << 3;
}

class Solver630MTest : public ProblemTest {};

TEST_F(Solver630MTest, Example1)
{
    string input = R"(60
)";
    string output = R"(1
)";
    setInput(input);
    Solver630M().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver630MTest, Example2)
{
    string input = R"(-60
)";
    string output = R"(3
)";
    setInput(input);
    Solver630M().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


