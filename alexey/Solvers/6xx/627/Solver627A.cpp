#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver627A
{
public:
    void run();

    int indicator(uint64_t n, uint64_t mask)
    {
        return ((n & mask) > 0) ? 1 : 0;
    }
};

void Solver627A::run()
{
    uint64_t s, x;
    cin >> s >> x;
    uint64_t ans = 1;
    auto overflowIndicator = s ^ x;
    if (overflowIndicator % 2 == 1)
        ans *= 0;
    overflowIndicator /= 2;
    unordered_map<int, int> possibilitesCount = { {0, 1}, {1, 2}, {2, 1} };
    for (int i : range(60))
    {
        auto currMask = uint64_t(1) << i;
        auto prevMask = currMask / 2;
        auto currSum = indicator(s, currMask) + 2 * indicator(overflowIndicator, currMask) - indicator(overflowIndicator, prevMask);
        ans *= possibilitesCount[currSum];
    }
    if (overflowIndicator == 0)
        ans -= 2;

    cout << ans;
}

class Solver627ATest : public ProblemTest {};

TEST_F(Solver627ATest, Example1)
{
    string input = R"(9 5
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver627A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver627ATest, Example2)
{
    string input = R"(3 3
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver627A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver627ATest, Example3)
{
    string input = R"(5 2
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver627A().run();
    EXPECT_EQ(output, getOutput());
}


