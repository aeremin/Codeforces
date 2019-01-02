#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/358/problem/D
class Solver358D
{
public:
    void run();
};

void Solver358D::run()
{
    int nHares; cin >> nHares;
    vector<int> a(nHares), b(nHares), c(nHares);
    for (auto ptr : { &a, &b, &c })
        for (auto& elt : *ptr)
            cin >> elt;

    vector<pair<int, int>> maxHappiness(nHares);
    maxHappiness[0] = { a[0], b[0] };
    for (int i = 1; i < nHares; ++i)
    {
        maxHappiness[i].first = max(a[i] + maxHappiness[i - 1].second, b[i] + maxHappiness[i - 1].first);
        maxHappiness[i].second = max(b[i] + maxHappiness[i - 1].second, c[i] + maxHappiness[i - 1].first);
    }

    cout << maxHappiness[nHares - 1].first;
}

class Solver358DTest : public ProblemTest
{
};

TEST_F( Solver358DTest, Example1 )
{
    setInput("4        1 2 3 4        4 3 2 1        0 1 1 0");
    Solver358D().run();
    EXPECT_EQ("13", getOutput());
}

TEST_F( Solver358DTest, Example2 )
{
    setInput("7        8 5 7 6 1 8 9        2 7 9 5 4 3 1        2 3 3 4 1 1 3");
    Solver358D().run();
    EXPECT_EQ("44", getOutput());
}

TEST_F(Solver358DTest, Example3)
{
    setInput("3        1 1 1        1 2 1        1 1 1");
    Solver358D().run();
    EXPECT_EQ("4", getOutput());
}
