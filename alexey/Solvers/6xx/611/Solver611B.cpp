#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/611/problem/B
class Solver611B
{
public:
    void run();
};

void Solver611B::run()
{
    int64_t from, to;
    cin >> from >> to;
    int64_t ans = 0;
    for (int64_t i = 1; i < 63; ++i)
    {
        int64_t allOnes = (1ll << i) - 1;
        for (int64_t j = 0; j < i - 1; ++j)
        {
            int64_t curr = allOnes - (1ll << j);
            if (curr >= from && curr <= to) 
                ++ans;
        }
    }

    cout << ans;
}

class Solver611BTest : public ProblemTest
{
};

TEST_F( Solver611BTest, Example1 )
{
    setInput("5 10");
    Solver611B().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver611BTest, Example2 )
{
    setInput("2015 2015");
    Solver611B().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver611BTest, Example3)
{
    setInput("100 105");
    Solver611B().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver611BTest, Example4)
{
    setInput("72057594000000000 72057595000000000");
    Solver611B().run();
    EXPECT_EQ("26", getOutput());
}