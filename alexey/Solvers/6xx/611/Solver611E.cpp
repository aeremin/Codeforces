#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/611/problem/E
class Solver611E
{
public:
    void run();
};

void Solver611E::run()
{
    int n;
    cin >> n;
    vector<int> fighters(3);
    for (auto& f : fighters) cin >> f;
    sort(begin(fighters), end(fighters));
    auto a = fighters[0];
    auto b = fighters[1];
    auto c = fighters[2];
    vector<int> sums = { a, b, c, a + b, b + c, a + c, a + b + c };
    sort(begin(sums), end(sums));
    vector<int> badGuyLevelCount(8, 0);
    for (int i = 0; i < n; ++i)
    {
        int f;
        cin >> f;
        badGuyLevelCount[lower_bound(begin(sums), end(sums), f) - begin(sums)]++;
    }

    if (badGuyLevelCount[7] > 0)
    {
        cout << -1;
        return;
    }

    int ans = 0;
    
    ans += badGuyLevelCount[6];

    ans += badGuyLevelCount[5];
    badGuyLevelCount[0] = max(0, badGuyLevelCount[0] - badGuyLevelCount[5]);

    ans += badGuyLevelCount[4];
    if (badGuyLevelCount[1] >= badGuyLevelCount[4])
        badGuyLevelCount[1] -= badGuyLevelCount[4];
    else
    {
        badGuyLevelCount[0] = max(0, badGuyLevelCount[0] - (badGuyLevelCount[4] - badGuyLevelCount[1]));
        badGuyLevelCount[1] = 0;
    }

    if (a + b > c)
    {
        ans += badGuyLevelCount[3];
        if (badGuyLevelCount[2] >= badGuyLevelCount[3])
            badGuyLevelCount[2] -= badGuyLevelCount[3];
        else if (badGuyLevelCount[1] + badGuyLevelCount[2] >= badGuyLevelCount[3])
        {
            badGuyLevelCount[1] -= (badGuyLevelCount[3] - badGuyLevelCount[2]);
            badGuyLevelCount[2] = 0;
        }
        else
        {
            badGuyLevelCount[0] = max(0, badGuyLevelCount[0] - (badGuyLevelCount[3] - badGuyLevelCount[1] - badGuyLevelCount[2]));
            badGuyLevelCount[2] = 0;
            badGuyLevelCount[1] = 0;
        }

        ans += max({
            (badGuyLevelCount[1] + badGuyLevelCount[2] + 1) / 2,
            (badGuyLevelCount[0] + badGuyLevelCount[1] + 2 * badGuyLevelCount[2] + 3) / 4,
            (badGuyLevelCount[0] + badGuyLevelCount[1] + badGuyLevelCount[2] + 2) / 3 });
    }
    else
    {
        ans += max({ badGuyLevelCount[3],
            (badGuyLevelCount[1] + badGuyLevelCount[2] + badGuyLevelCount[3] + 1) / 2,
            (badGuyLevelCount[0] + badGuyLevelCount[1] + 2 * badGuyLevelCount[2] + 2 * badGuyLevelCount[3] + 3) / 4,
            (badGuyLevelCount[0] + badGuyLevelCount[1] + badGuyLevelCount[2] + badGuyLevelCount[3] + 2) / 3 });
    }

    cout << ans;
}

class Solver611ETest : public ProblemTest
{
};

TEST_F( Solver611ETest, Example1 )
{
    setInput("5        10 20 30        1 1 1 1 50");
    Solver611E().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver611ETest, Example2 )
{
    setInput("5        10 20 30        1 1 1 1 51");
    Solver611E().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver611ETest, Example3)
{
    setInput("7        30 20 10        34 19 50 33 88 15 20");
    Solver611E().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver611ETest, Example4)
{
    setInput("6        10 5 10        10 9 5 25 20 5");
    Solver611E().run();
    EXPECT_EQ("3", getOutput());
}