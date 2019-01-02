#include <Solvers/pch.h>
#include "iter/range.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/596/problem/A
class Solver596A
{
public:
    void run();
};

void Solver596A::run()
{
    set<int> xs, ys;
    int n;
    cin >> n;
    for (int i : range(n)) {
        int x, y;
        cin >> x >> y;
        xs.insert(x);
        ys.insert(y);
    }
    auto res = (*xs.rbegin() - *begin(xs)) * (*ys.rbegin() - *begin(ys));
    if (res == 0)
        res = -1;
    cout << res;
}


class Solver596ATest : public ProblemTest
{
};

TEST_F( Solver596ATest, Example1 )
{
    setInput("2    0 0    1 1");
    Solver596A().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver596ATest, Example2 )
{
    setInput("1    1 1");
    Solver596A().run();
    EXPECT_EQ("-1", getOutput());
}
