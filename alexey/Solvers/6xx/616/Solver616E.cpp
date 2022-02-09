#include <Solvers/pch.h>
#include "algo/number_theory/residue.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/616/problem/E
class Solver616E
{
public:
    void run();
};

void Solver616E::run()
{
    int64_t n, m;
    cin >> n >> m;
    CodeforcesResidue64 ans = 0;
    CodeforcesResidue64 twoInverted = CodeforcesResidue64(2).inversed();
    if (m > n)
        ans += CodeforcesResidue64(n) * CodeforcesResidue64(m - n);
   
    int64_t l = m + 1;
    for (int64_t d = 2; d * d < n; ++d)
    {
        l = n / d + 1;
        int64_t r = min((n - 1) / (d - 1), m);
        if (r >= l)
        {
            ans += CodeforcesResidue64(r - l + 1) * CodeforcesResidue64(n);
            ans -= CodeforcesResidue64(d - 1) * CodeforcesResidue64(r + l) * CodeforcesResidue64(r - l + 1) * twoInverted;
        }
    }

    for (int d = 1; d < l && d <= m && d < n; ++d)
        ans += (n % d);

    cout << ans;
}

class Solver616ETest : public ProblemTest
{
};

TEST_F( Solver616ETest, Example1 )
{
    setInput("3 4");
    Solver616E().run();
    EXPECT_EQ("4", getOutput());
}

TEST_F( Solver616ETest, Example2 )
{
    setInput("4 4");
    Solver616E().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver616ETest, Example3)
{
    setInput("1 1");
    Solver616E().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver616ETest, Example4)
{
    setInput("10000000000000 10000000000000");
    Solver616E().run();
}
