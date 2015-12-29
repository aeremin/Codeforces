#include <Solvers/pch.h>

using namespace std;

class Solver498A
{
public:
    void run();

    int64_t sgn(int64_t x)
    {
        return x > 0 ? 1 : -1;
    }
};

void Solver498A::run()
{
    int64_t xH, yH;
    cin >> xH >> yH;
    int64_t xU, yU;
    cin >> xU >> yU;

    int64_t nRoads;
    cin >> nRoads;

    int64_t steps = 0;
    for (int64_t i = 0; i < nRoads; ++i)
    {
        int64_t a, b, c;
        cin >> a >> b >> c;
        if (sgn(xH * a + yH * b + c) != sgn(xU * a + yU * b + c))
            steps++;
    }

    cout << steps;
}

class Solver498ATest : public ProblemTest
{
};

TEST_F( Solver498ATest, Example1 )
{
    setInput("1 1        -1 -1        2        0 1 0        1 0 0");
    Solver498A().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver498ATest, Example2 )
{
    setInput("1 1        -1 -1        3        1 0 0        0 1 0        1 1 -3");
    Solver498A().run();
    EXPECT_EQ("2", getOutput());
}