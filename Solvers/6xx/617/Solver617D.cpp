#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"

using namespace std;

class Solver621D
{
public:
    void run();

    bool between(int p, int q, int r)
    {
        return r > min(p, q) && r < max(p, q);
    }
};

void Solver621D::run()
{
    GeomVector2I a, b, c;
    cin >> a[0] >> a[1];
    cin >> b[0] >> b[1];
    cin >> c[0] >> c[1];

    unordered_set<int> xs = { a[0], b[0], c[0] };
    unordered_set<int> ys = { a[1], b[1], c[1] };

    if (xs.size() == 1 || ys.size() == 1)
    {
        cout << 1;
        return;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (a[i] == b[i] && !between(a[1 - i], b[1 - i], c[1 - i]) ||
            a[i] == c[i] && !between(a[1 - i], c[1 - i], b[1 - i]) ||
            c[i] == b[i] && !between(c[1 - i], b[1 - i], a[1 - i]))
        {
            cout << 2;
            return;
        }
    }

    cout << 3;
}

class Solver621DTest : public ProblemTest
{
};

TEST_F( Solver621DTest, Example1 )
{
    setInput("1 -1             1 1             1 2             ");
    Solver621D().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver621DTest, Example2 )
{
    setInput("-1 -1             -1 3             4 3");
    Solver621D().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver621DTest, Example3)
{
    setInput("1 1             2 3             3 2");
    Solver621D().run();
    EXPECT_EQ("3", getOutput());
}
