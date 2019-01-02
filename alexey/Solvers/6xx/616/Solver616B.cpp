#include <Solvers/pch.h>
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/616/problem/B
class Solver616B
{
public:
    void run();
};

void Solver616B::run()
{
    int nStreets, nAvenue;
    cin >> nStreets >> nAvenue;
    int ans = 0;
    for (int i = 0; i < nStreets; ++i)
    {
        int minOnAvenue = numeric_limits<int>::max();
        for (int j = 0; j < nAvenue; ++j)
        {
            int v;
            cin >> v;
            relax_min(minOnAvenue, v);
        }
        relax_max(ans, minOnAvenue);
    }
    cout << ans;
}

class Solver616BTest : public ProblemTest
{
};

TEST_F( Solver616BTest, Example1 )
{
    setInput("3 4             4 1 3 5             2 2 2 2             5 4 5 1");
    Solver616B().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver616BTest, Example2 )
{
    setInput("3 3             1 2 3             2 3 1             3 1 2");
    Solver616B().run();
    EXPECT_EQ("1", getOutput());
}
