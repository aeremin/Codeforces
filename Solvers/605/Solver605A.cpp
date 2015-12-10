#include "Solvers/pch.h"
#include "Solver605A.h"
#include "algo/MaximaIncreasingSubsequence.hpp"

void Solver605A::run()
{
    size_t n;
    cin >> n;
    std::vector<int> numToPosition(n);
    for (size_t i = 0; i < n; ++i)
    {
        int r;
        cin >> r;
        numToPosition[r - 1] = i;
    }
    
    cout << n - lenOfMaximalIncreasingSubsegment(begin(numToPosition), end(numToPosition));
}

class Solver605ATest : public ProblemTest {};

TEST_F(Solver605ATest, Example1)
{
    setInput("5    4 1 2 5 3");
    Solver605A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver605ATest, Example2)
{
    setInput("4        4 1 3 2");
    Solver605A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver605ATest, Example3)
{
    setInput("7        1 3 5 7 2 4 6");
    Solver605A().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver605ATest, Example4)
{
    setInput("8        6 2 1 8 5 7 3 4");
    Solver605A().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver605ATest, Example5)
{
    setInput("3        1 2 3");
    Solver605A().run();
    EXPECT_EQ("0", getOutput());
}
