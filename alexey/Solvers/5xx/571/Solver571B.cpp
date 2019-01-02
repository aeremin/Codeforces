#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/571/problem/B
class Solver571B
{
public:
    void run();
};

void Solver571B::run()
{
    int n, k;
    cin >> n >> k;
    vector<int> data(n);
    for (auto& elt : data)
        cin >> elt;

    sort(begin(data), end(data));

    auto smallChainLen = n / k;
    auto bigChainLen = smallChainLen + 1;
    auto bigChainCount = n % k;
    auto smallChainCount = k - bigChainCount;

    vector<vector<int>> ans(bigChainCount + 1, vector<int>(smallChainCount + 1));
    for (int iBigChains = 0; iBigChains <= bigChainCount; ++iBigChains)
    {
        for (int iSmallChains = 0; iSmallChains <= smallChainCount; ++iSmallChains)
        {
            if (iSmallChains == 0 && iBigChains == 0)
            {
                ans[iBigChains][iSmallChains] = 0;
                continue;
            }

            int i = iBigChains * bigChainLen + iSmallChains * smallChainLen;
            auto opt1 = iBigChains > 0 ? ans[iBigChains - 1][iSmallChains] + data[i - 1] - data[i - bigChainLen] : numeric_limits<int>::max();
            auto opt2 = iSmallChains > 0 ? ans[iBigChains][iSmallChains - 1] + data[i - 1] - data[i - smallChainLen] : numeric_limits<int>::max();
            ans[iBigChains][iSmallChains] = min(opt1, opt2);
        }
    }

    cout << ans[bigChainCount][smallChainCount];
}

class Solver571BTest : public ProblemTest
{
};

TEST_F(Solver571BTest, Example1)
{
    setInput("3 2        1 2 4");
    Solver571B().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver571BTest, Example2)
{
    setInput("5 2        3 -5 3 -5 3");
    Solver571B().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver571BTest, Example3)
{
    setInput("6 3        4 3 4 3 2 5");
    Solver571B().run();
    EXPECT_EQ("3", getOutput());
}

