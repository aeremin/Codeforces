#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/651/problem/A
class Solver651A
{
public:
    void run();
};

void Solver651A::run()
{
    int a, b;
    cin >> a >> b;
    cout << max(0, a + b - 2 - (((a - b) % 3 == 0) ? 1 : 0));
}

class Solver651ATest : public ProblemTest {};

TEST_F(Solver651ATest, Example1)
{
    string input = R"(3 5
)";
    string output = R"(6
)";
    setInput(input);
    Solver651A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver651ATest, Example2)
{
    string input = R"(4 4
)";
    string output = R"(5
)";
    setInput(input);
    Solver651A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


