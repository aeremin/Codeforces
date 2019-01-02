#include "Solvers/pch.h"

// Solution for Codeforces problem http://codeforces.com/contest/581/problem/A
class Solver581A
{
public:
    void run();
};

void Solver581A::run()
{
    int64_t red, blue;
    cin >> red >> blue;
    auto hipsterDays = std::min(red, blue);
    auto nonHipsterDays = (red + blue - 2 * hipsterDays) / 2;
    cout << hipsterDays << " " << nonHipsterDays;
}

class Solver581ATest : public ProblemTest {};

TEST_F(Solver581ATest, Example1)
{
    setInput("3 1");
    Solver581A().run();
    EXPECT_EQ("1 1", getOutput());
}

TEST_F(Solver581ATest, Example2)
{
    setInput("2 3");
    Solver581A().run();
    EXPECT_EQ("2 0", getOutput());
}

TEST_F(Solver581ATest, Example3)
{
    setInput("7 3");
    Solver581A().run();
    EXPECT_EQ("3 2", getOutput());
}