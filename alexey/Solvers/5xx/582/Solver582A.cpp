#include <Solvers/pch.h>
#include "algo/number_theory/greatest_common_divisor.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/582/problem/A
class Solver582A
{
public:
    void run();
};

void Solver582A::run()
{
    size_t n;
    cin >> n;
    map<int, int> numCounts;
    for (int i = 0; i < n * n; ++i)
    {
        int num;
        cin >> num;
        numCounts[num]++;
    }

    vector<int> ans;
    for (auto it = numCounts.rbegin(); it != numCounts.rend(); ++it)
    {
        auto& p = *it;
        while (p.second > 0)
        {
            ans.push_back(p.first);
            numCounts[p.first]++;
            for (auto& a : ans)
                numCounts[greatestCommonDivisor(a, p.first)] -= 2;
        }
    }

    for (auto a : ans)
        cout << a << " ";
}


class Solver582ATest : public ProblemTest
{
};

TEST_F( Solver582ATest, Example1 )
{
    setInput("4        2 1 2 3 4 3 2 6 1 1 2 2 1 2 3 2");
    Solver582A().run();
    EXPECT_EQ("6 4 3 2 ", getOutput());
}

TEST_F( Solver582ATest, Example2 )
{
    setInput("2        1 1 1 1");
    Solver582A().run();
    EXPECT_EQ("1 1 ", getOutput());
}


TEST_F(Solver582ATest, Example3)
{
    setInput("1  42");
    Solver582A().run();
    EXPECT_EQ("42 ", getOutput());
}