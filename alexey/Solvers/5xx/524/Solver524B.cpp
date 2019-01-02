#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/524/problem/B
class Solver524B
{
public:
    void run();
};

void Solver524B::run()
{
    int nPeople;
    cin >> nPeople;
    vector<pair<int, int>> people(nPeople);
    vector<int> possibleHeights;
    for (auto& p : people)
    {
        cin >> p.first >> p.second;
        if (p.first < p.second)
            swap(p.first, p.second);
        possibleHeights.push_back(p.first);
        possibleHeights.push_back(p.second);
    }

    int ans = numeric_limits<int>::max();

    for (int i = 0; i < possibleHeights.size(); ++i)
    {
        auto H = possibleHeights[i];
        auto W = 0;
        bool isPossible = true;
        for (auto& p : people)
        {
            if (p.first <= H)
                W += p.second;
            else if (p.second <= H)
                W += p.first;
            else
                isPossible = false;
        }
        if (isPossible)
            ans = min(ans, W * H);
    }

    cout << ans;
}

class Solver524BTest : public ProblemTest
{
};

TEST_F(Solver524BTest, Example1)
{
    setInput("3        10 1        20 2        30 3");
    Solver524B().run();
    EXPECT_EQ("180", getOutput());
}

TEST_F(Solver524BTest, Example2)
{
    setInput("3        3 1        2 2        4 3");
    Solver524B().run();
    EXPECT_EQ("21", getOutput());
}

TEST_F(Solver524BTest, Example3)
{
    setInput("1        5 10");
    Solver524B().run();
    EXPECT_EQ("50", getOutput());
}
