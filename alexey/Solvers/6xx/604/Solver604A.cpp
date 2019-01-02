#include <Solvers/pch.h>
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/604/problem/A
class Solver604A
{
public:
    void run();
};

void Solver604A::run()
{
    auto times = readVector<int>(5);
    auto tries = readVector<int>(5);
    auto successfulHacks = read<int>();
    auto unsuccessfulHacks = read<int>();
    
    int res = 100 * successfulHacks - 50 * unsuccessfulHacks;
    for (int i : range(5))
    {
        auto problemCostBy250 = (i + 1) * 2;
        res += max(75 * problemCostBy250, (250 - times[i]) * problemCostBy250 - 50 * tries[i]);
    }
    print(res);
}

class Solver604ATest : public ProblemTest {};

TEST_F(Solver604ATest, Example1)
{
    string input = R"(20 40 60 80 100
0 1 2 3 4
1 0
)";
    string output = R"(4900
)";
    setInput(input);
    Solver604A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver604ATest, Example2)
{
    string input = R"(119 119 119 119 119
0 0 0 0 0
10 0
)";
    string output = R"(4930
)";
    setInput(input);
    Solver604A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


