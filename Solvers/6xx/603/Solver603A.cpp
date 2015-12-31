#include "Solvers/pch.h"
#include "Solver603A.h"

void Solver603A::run()
{
    int n;
    cin >> n;
    std::vector<int> results(n);
    for (auto& r : results)
    {
        char c;
        cin >> c;
        if (c == '0')
            r = 0;
        else
            r = 1;
    }

    std::vector<int> diffs;
    std::adjacent_difference(begin(results), end(results), std::back_inserter(diffs));
    int zeros = std::count(begin(diffs) + 1, end(diffs), 0);
    std::cout << n - zeros + std::min(2, zeros);
}

class Solver603ATest : public ProblemTest {};

TEST_F(Solver603ATest, Example1)
{
    setInput("8        10000011");
    Solver603A().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver603ATest, Example2)
{
    setInput("2        01");
    Solver603A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver603ATest, Example3)
{
    setInput("3        001");
    Solver603A().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver603ATest, Example4)
{
    setInput("5        00000");
    Solver603A().run();
    EXPECT_EQ("3", getOutput());
}