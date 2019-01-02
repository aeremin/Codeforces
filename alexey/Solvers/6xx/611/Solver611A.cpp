#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/611/problem/A
class Solver611A
{
public:
    void run();
};

void Solver611A::run()
{
    vector<int> monthLengths = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int64_t n;
    cin >> n;
    string s;
    cin >> s;
    cin >> s;
    if (s == "week")
    {
        if (n == 5 || n == 6)
            cout << 53;
        else
            cout << 52;
    }
    else
    {
        int ans = 0;
        for (auto& m : monthLengths)
            if (m >= n) ++ans;
        cout << ans;
    }
}

class Solver611ATest : public ProblemTest
{
};

TEST_F( Solver611ATest, Example1 )
{
    setInput("4 of week");
    Solver611A().run();
    EXPECT_EQ("52", getOutput());
}

TEST_F( Solver611ATest, Example2 )
{
    setInput("30 of month");
    Solver611A().run();
    EXPECT_EQ("11", getOutput());
}