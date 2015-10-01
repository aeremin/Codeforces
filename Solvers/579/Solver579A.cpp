#include "Solvers/pch.h"
#include "Solver579A.h"

int nBitsSet(int a)
{
    int result = 0;
    while (a > 0)
    {
        result += (a & 1);
        a /= 2;
    }
    return result;
}

void Solver579A::run()
{
    int a;
    cin >> a;
    cout << nBitsSet(a);
}

class Solver579ATest : public ProblemTest {};

TEST_F(Solver579ATest, Example1)
{
    setInput("5");
    Solver579A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver579ATest, Example2)
{
    setInput("8");
    Solver579A().run();
    EXPECT_EQ("1", getOutput());
}