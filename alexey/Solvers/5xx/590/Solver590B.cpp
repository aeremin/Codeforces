#include "Solvers/pch.h"

class Solver590B
{
public:
    void run();
};

void Solver590B::run()
{
    int64_t x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x2 -= x1;
    y2 -= y1;

    int64_t vmax, t;
    cin >> vmax >> t;

    int64_t vx, vy, wx, wy;
    cin >> vx >> vy >> wx >> wy;

    double l = 0;
    double r = 1e9;
    while (r - l > 1e-10)
    {
        auto m = (r + l) / 2;
        bool can = false;
        if (m < t)
        {
            can = (x2 - m * vx) * (x2 - m * vx) + (y2 - m * vy) * (y2 - m * vy) < m * m * vmax * vmax;
        }
        else
        {
            auto tt = m - t;
            can = (x2 - t * vx - tt * wx) * (x2 - t * vx - tt * wx) + (y2 - t * vy - tt * wy) * (y2 - t * vy - tt * wy) < m * m * vmax * vmax;
        }
        if (can)
            r = m;
        else
            l = m;
    }

    cout << setprecision(9) << fixed << l;
}

class Solver590BTest : public ProblemTest {};

TEST_F(Solver590BTest, Example1)
{
    setInput("0 0 5 5        3 2        -1 -1        -1 0");
    Solver590B().run();
    EXPECT_EQ("3.729935587", getOutput());
}

TEST_F(Solver590BTest, Example2)
{
    setInput("0 0 0 1000        100 1000        -50 0        50 0");
    Solver590B().run();
    EXPECT_EQ("11.547005384", getOutput());
}