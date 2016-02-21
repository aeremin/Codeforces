#include <Solvers/pch.h>

using namespace std;

class Solver533E
{
public:
    void run();
};

void Solver533E::run()
{
    int len;
    cin >> len;
    string s1, s2;
    cin >> s1 >> s2;
    int l = 0;
    while (s1[l] == s2[l]) ++l;
    int r = len - 1;
    while (s1[r] == s2[r]) --r;
    int ans = 0;
    if (s1.substr(l, r - l) == s2.substr(l + 1, r - l))
        ++ans;
    if (s1.substr(l + 1, r - l) == s2.substr(l, r - l))
        ++ans;
    cout << ans;
}

class Solver533ETest : public ProblemTest
{
};

TEST_F( Solver533ETest, Example1 )
{
    setInput("7        reading        trading");
    Solver533E().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver533ETest, Example2 )
{
    setInput("5        sweet        sheep");
    Solver533E().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver533ETest, Example3)
{
    setInput("3        toy        try");
    Solver533E().run();
    EXPECT_EQ("2", getOutput());
}