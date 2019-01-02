#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/567/problem/C
class Solver567C
{
public:
    void run();
};

void Solver567C::run()
{
    int n = read<int>();
    int k = read<int>();
    auto nums = readVector<int64_t>(n);
    unordered_map<int64_t, int64_t> cnt1, cnt2;
    int64_t ans = 0;
    for (auto l : nums) {
        if (l % (k * k) == 0)
            ans += cnt2[l / k];
        if (l % k == 0)
            cnt2[l] += cnt1[l / k];
        cnt1[l]++;
    }

    cout << ans;
}

class Solver567CTest : public ProblemTest {};

TEST_F(Solver567CTest, Example1)
{
    string input = R"(5 2
1 1 2 2 4
)";
    string output = R"(4)";
    setInput(input);
    Solver567C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver567CTest, Example2)
{
    string input = R"(3 1
1 1 1
)";
    string output = R"(1)";
    setInput(input);
    Solver567C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver567CTest, Example3)
{
    string input = R"(10 3
1 2 6 2 3 6 9 18 3 9
)";
    string output = R"(6)";
    setInput(input);
    Solver567C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


