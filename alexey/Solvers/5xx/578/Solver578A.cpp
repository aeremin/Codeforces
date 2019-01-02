#include "Solvers/pch.h"

// Solution for Codeforces problem http://codeforces.com/contest/578/problem/A
class Solver578A
{
public:
    void run();
};

void Solver578A::run()
{
    int64_t a, b;
    cin >> a >> b;
    if (a < b)
    {
        cout << -1;
    }
    else
    {
        double l = double(a - b) / double(2 * b);
        int64_t roundedL = l;
        double x1 = (roundedL > 0) ? (double(a - b) / (2.0 * roundedL)) : DBL_MAX;
        double x2 = double(a + b) / (2.0 * roundedL + 2.0);
        cout << setprecision(10) << fixed << min(x1, x2);
    }
}

class Solver578ATest : public ProblemTest {};

TEST_F(Solver578ATest, Example1)
{
    setInput("3 1");
    Solver578A().run();
    EXPECT_EQ("1.0000000000", getOutput());
}

TEST_F(Solver578ATest, Example2)
{
    setInput("1 3");
    Solver578A().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver578ATest, Example3)
{
    setInput("4 1");
    Solver578A().run();
    EXPECT_EQ("1.2500000000", getOutput());
}

TEST_F(Solver578ATest, Example4)
{
    setInput("5 3");
    Solver578A().run();
    EXPECT_EQ("4.0000000000", getOutput());
}
