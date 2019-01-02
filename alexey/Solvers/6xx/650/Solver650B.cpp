#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "util/relax.h"
#include "algo/FunctorIterator.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/650/problem/B
class Solver650B
{
public:
    void run();
};

void Solver650B::run() {
    int a, b;
    int t, n;
    cin >> n >> a >> b >> t;
    string orientation;
    cin >> orientation;
    vector<int> inversions = { 0 };
    for (auto& c : orientation) {
        auto inc = (c == 'w') ? 1 : 0;
        inversions.push_back(inversions.back() + inc);
    }

    auto canSee = [&](int cnt) -> int {
        if (cnt == 0)
            return 0;
        for (int forwardCnt : range(1, cnt + 1)) {
            auto backwardCnt = cnt - forwardCnt;
            auto neededTime1 = cnt + forwardCnt * a + backwardCnt * 2 * a - a
                + b *(inversions[forwardCnt] + inversions[n] - inversions[n - backwardCnt]);
            auto neededTime2 = (backwardCnt > 0) ? 
                                                   cnt + forwardCnt * a + backwardCnt * 2 * a - 2 * a
                                                   + b * (inversions[backwardCnt] + inversions[n] - inversions[n - forwardCnt])
                                                 : neededTime1;
            if (min(neededTime1, neededTime2) <= t)
                return 0;
        }
        return 1;
    };

    auto l = makeFunctorIterator(0, canSee);
    auto r = makeFunctorIterator(min(t, n) + 1, canSee);
    cout << upper_bound(l, r, 0).getParameter() - 1;
}

class Solver650BTest : public ProblemTest {};

TEST_F(Solver650BTest, Example1)
{
    string input = R"(4 2 3 10
wwhw
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver650B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver650BTest, Example2)
{
    string input = R"(5 2 4 13
hhwhh
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver650B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver650BTest, Example3)
{
    string input = R"(5 2 4 1000
hhwhh
)";
    string output = R"(5
)";
    output.pop_back();
    setInput(input);
    Solver650B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver650BTest, Example4)
{
    string input = R"(3 1 100 10
whw
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver650B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver650BTest, CanSeeJustOne) {
    string input = R"(3 10 10 10
hhh
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver650B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver650BTest, CanSeeEverything) {
    string input = R"(10 10 10 1000
hhhhhhhhhh
)";
    string output = R"(10
)";
    output.pop_back();
    setInput(input);
    Solver650B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


