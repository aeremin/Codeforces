#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/427/problem/B
class Solver427B
{
public:
    void run();
};

void Solver427B::run()
{
    int n, t, c;
    cin >> n >> t >> c;
    int64_t ans = 0;
    auto dd = readVector<int>(n);
    dd.push_back(t + 1);
    int prev = -1;
    for (int i : range(n+1)) {
        auto d = dd[i];
        if (d <= t && prev == -1) prev = i;
        if (d > t && prev != -1) {
            int cnt = i - prev;
            if (cnt >= c)
                ans += cnt - c + 1;
            prev = -1;
        }
    }

    cout << ans;
}

class Solver427BTest : public ProblemTest {};

TEST_F(Solver427BTest, Example1)
{
    string input = R"(4 3 3
2 3 1 1
)";
    string output = R"(2
)";
    setInput(input);
    Solver427B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver427BTest, Example2)
{
    string input = R"(1 1 1
2
)";
    string output = R"(0
)";
    setInput(input);
    Solver427B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver427BTest, Example3)
{
    string input = R"(11 4 2
2 2 0 7 3 2 2 4 9 1 4
)";
    string output = R"(6
)";
    setInput(input);
    Solver427B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


