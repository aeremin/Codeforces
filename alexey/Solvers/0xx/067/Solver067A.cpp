#include <Solvers/pch.h>
#include "util/relax.h"

using namespace std;

class Solver067A
{
public:
    void run();
};

void Solver067A::run()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> minAllowed(n);
    minAllowed[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i)
    {
        if (s[i] == 'R')
            minAllowed[i] = 1;
        else if (s[i] == '=')
            minAllowed[i] = minAllowed[i + 1];
        else
            minAllowed[i] = minAllowed[i + 1] + 1;
    }

    vector<int> ans = { minAllowed[0] };
    for (int i = 1; i < n; ++i)
    {
        ans.push_back(minAllowed[i]);
        if (s[i - 1] == 'R')
            relax_max(ans.back(), ans[i - 1] + 1);
        else if (s[i - 1] == '=')
            relax_max(ans.back(), ans[i - 1]);
    }

    for (auto elt : ans)
        cout << elt << " ";
}

class Solver067ATest : public ProblemTest
{
};

TEST_F( Solver067ATest, Example1 )
{
    setInput("5\nLRLR");
    Solver067A().run();
    EXPECT_EQ("2 1 2 1 2 ", getOutput());
}

TEST_F( Solver067ATest, Example2 )
{
    setInput("5\n=RRR");
    Solver067A().run();
    EXPECT_EQ("1 1 2 3 4 ", getOutput());
}
