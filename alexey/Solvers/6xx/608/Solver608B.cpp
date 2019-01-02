#include <Solvers/pch.h>
#include "algo/Indicator.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/608/problem/B
class Solver608B
{
public:
    void run();
};

void Solver608B::run()
{
    string a, b;
    cin >> a >> b;
    auto onesOnPrefix = count(begin(b), end(b) - a.length() + 1 , '1');
    vector<int> onesCount = { int(onesOnPrefix) };
    for (int i = 1; i < a.length(); ++i)
        onesCount.push_back(onesCount.back() + indicator<int>(b[b.length() - a.length() + i] == '1')
                                             - indicator<int>(b[i - 1] == '1'));

    int64_t ans = 0;
    for (int i = 0; i < a.length(); ++i)
        if (a[i] == '0')
            ans += onesCount[i];
        else
            ans += b.length() - a.length() + 1 - onesCount[i];

    cout << ans;
}

class Solver608BTest : public ProblemTest {};

TEST_F(Solver608BTest, Example1)
{
    string input = R"(01
00111
)";
    string output = R"(3
)";
    setInput(input);
    Solver608B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver608BTest, Example2)
{
    string input = R"(0011
0110
)";
    string output = R"(2
)";
    setInput(input);
    Solver608B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


