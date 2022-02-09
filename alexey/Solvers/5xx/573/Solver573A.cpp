#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/number_theory/greatest_common_divisor.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/573/problem/A
class Solver573A
{
public:
    void run();

    void eliminate2and3(int& a)
    {
        while (a % 2 == 0) a /= 2;
        while (a % 3 == 0) a /= 3;
    }
};

void Solver573A::run()
{
    int n = read<int>();
    auto bets = readVector<int>(n);
    bool can = true;
    for (int i = 1; i < n; ++i)
    {
        auto d = greatestCommonDivisor(bets[0], bets[i]);
        int b1 = bets[0] / d;
        int b2 = bets[i] / d;
        eliminate2and3(b1);
        eliminate2and3(b2);
        can = can && b1 == 1 && b2 == 1;
    }

    if (can) cout << "Yes";
        else cout << "No";
}

class Solver573ATest : public ProblemTest {};

TEST_F(Solver573ATest, Example1)
{
    string input = R"(4
75 150 75 50
)";
    string output = R"(Yes
)";
    setInput(input);
    Solver573A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver573ATest, Example2)
{
    string input = R"(3
100 150 250
)";
    string output = R"(No
)";
    setInput(input);
    Solver573A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


