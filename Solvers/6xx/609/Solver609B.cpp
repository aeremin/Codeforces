#include "Solvers/pch.h"

using namespace std;

class Solver609B
{
public:
    void run();
};


void Solver609B::run()
{
    int sentinelValue = 10000;

    int n;
    cin >> n;
    vector<int> stones(n);
    for (auto& s : stones) cin >> s;

    vector<vector<int>> ans(n, vector<int>(n, sentinelValue));
    for (int i = 0; i < n; ++i)
    {
        ans[i][i] = 1;
        for (int j = i - 1; j >= 0; --j)
        {
            int a = sentinelValue;
            
            if (stones[j] == stones[i])
            {
                if ((i - j) == 1)
                    a = 1;
                else
                    a = ans[j][i] = ans[j + 1][i - 1];
            }

            
            for (int k = j + 1; k <= i; ++k )
                a = min(a, ans[j][k - 1] + ans[k][i]);
        
            ans[j][i] = a;
        }
    }

    cout << ans[0][n - 1];
}

class Solver609BTest : public ProblemTest {};

TEST_F(Solver609BTest, Example1)
{
    setInput("7        1 4 4 2 3 2 1");
    Solver609B().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver609BTest, Example2)
{
    setInput("3        1 2 3");
    Solver609B().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver609BTest, Example3)
{
    setInput("3        1 2 1");
    Solver609B().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver609BTest, Example4)
{
    setInput("8        1 2 2 1 1 3 3 1");
    Solver609B().run();
    EXPECT_EQ("2", getOutput());
}