#include "Solvers/pch.h"
#include <cstdint>

// Solution for Codeforces problem http://codeforces.com/contest/580/problem/B
class Solver580B
{
public:
    void run();
};

void Solver580B::run()
{
    size_t nFriends;
    int64_t d;
    cin >> nFriends >> d;

    vector<pair<int64_t, int64_t>> friends(nFriends);
    
    for (auto& p : friends)
        cin >> p.first >> p.second;

    sort(begin(friends), end(friends));

    int64_t totalFriendness = 0;
    int64_t maxTotalFriendness = 0;
    deque<pair<int64_t, int64_t>> currentParty;
    
    for (auto& p : friends)
    {
        currentParty.push_back(p);
        totalFriendness += p.second;
        while (currentParty.back().first - currentParty.front().first >= d)
        {
            totalFriendness -= currentParty.front().second;
            currentParty.pop_front();
        }
        maxTotalFriendness = max(maxTotalFriendness, totalFriendness);
    }

    cout << maxTotalFriendness;
}

class Solver580BTest : public ProblemTest {};

TEST_F(Solver580BTest, Example1)
{
    setInput("4 5    75 5   0 100   150 20  75 1");
    Solver580B().run();
    EXPECT_EQ("100", getOutput());
}

TEST_F(Solver580BTest, Example2)
{
    setInput("5 100     0 7        11 32        99 10        46 8        87 54");
    Solver580B().run();
    EXPECT_EQ("111", getOutput());
}

TEST_F(Solver580BTest, ExactlyDifference)
{
    setInput("2 1   1 1    2 1");
    Solver580B().run();
    EXPECT_EQ("1", getOutput());
}

