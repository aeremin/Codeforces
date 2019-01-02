#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/107/problem/B
class Solver107B
{
public:
    void run();
};

void Solver107B::run()
{
    int k, nDep, iDep;
    cin >> k >> nDep >> iDep;
    --iDep;
    valarray<int> studentCounts(nDep);
    for (auto& elt : studentCounts) cin >> elt;
    int l = k - 1;
    int A = studentCounts[iDep] - 1;
    int B = studentCounts.sum() - studentCounts[iDep];
    if (l > A + B)
    {
        cout << -1;
        return;
    }
    if (l > B)
    {
        cout << 1;
        return;
    }
    double p = 1.0;
    for (int i = 1; i <= A; ++i)
        p *= (1 - double(l) / double(B + i));

    cout << setprecision(10) << fixed << 1 - p;
}

class Solver107BTest : public ProblemTest
{
};

TEST_F( Solver107BTest, Example1 )
{
    setInput("3 2 1        2 1");
    Solver107B().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver107BTest, Example2 )
{
    setInput("3 2 1       1 1");
    Solver107B().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver107BTest, Example3)
{
    setInput("3 2 1       2 2");
    Solver107B().run();
    EXPECT_EQ("0.6666666667", getOutput());
}
