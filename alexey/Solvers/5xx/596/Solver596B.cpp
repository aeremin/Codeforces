#include <Solvers/pch.h>
#include "util/relax.h"
#include "algo/io/readvector.h"
#include "iter/range.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/596/problem/B
class Solver596B
{
public:
    void run();
};

void Solver596B::run()
{
    int n;
    cin >> n;
    auto inp = readVector<int>(n);
    deque<int> nums(begin(inp), end(inp));
    nums.push_front(0);
    int64_t res = 0;
    for (int i : range(n))
        res += abs(nums[i + 1] - nums[i]);
    cout << res;
}

class Solver596BTest : public ProblemTest
{
};

TEST_F( Solver596BTest, Example1 )
{
    setInput("5    1 2 3 4 5");
    Solver596B().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver596BTest, Example2) {
    setInput("4    1 2 2 1");
    Solver596B().run();
    EXPECT_EQ("3", getOutput());
}

