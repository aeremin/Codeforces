#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/645/problem/B
class Solver645B
{
public:
    void run();
};

void Solver645B::run() {
    int64_t a, b;
    cin >> a >> b;
    int64_t l = 0;
    int64_t r = a - 1;
    int64_t ans = 0;
    while (r > l && b > 0) {
        ans += 2 * (r - l) - 1;
        ++l;
        --r;
        --b;
    }
    cout << ans;
}

class Solver645BTest : public ProblemTest {};

TEST_F(Solver645BTest, Example1)
{
    string input = R"(5 2
)";
    string output = R"(10
)";
    setInput(input);
    Solver645B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver645BTest, Example2)
{
    string input = R"(1 10
)";
    string output = R"(0
)";
    setInput(input);
    Solver645B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver645BTest, Example3) {
    string input = R"(4 2
)";
    string output = R"(6
)";
    setInput(input);
    Solver645B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver645BTest, Example4) {
    string input = R"(2 10
)";
    string output = R"(1
)";
    setInput(input);
    Solver645B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver645BTest, Example5) {
    string input = R"(5 1
)";
    string output = R"(7
)";
    setInput(input);
    Solver645B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}