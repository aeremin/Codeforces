#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/448/problem/A
class Solver448A
{
public:
    void run();
};

void Solver448A::run()
{
    int a1, a2, a3;
    cin >> a1 >> a2 >> a3;
    int b1, b2, b3;
    cin >> b1 >> b2 >> b3;
    int n;
    cin >> n;
    if ((a1 + a2 + a3 + 4) / 5 + (b1 + b2 + b3 + 9) / 10 <= n)
        cout << "YES";
    else
        cout << "NO";
}

class Solver448ATest : public ProblemTest {};

TEST_F(Solver448ATest, Example1)
{
    string input = R"(1 1 1
1 1 1
4
)";
    string output = R"(YES
)";
    setInput(input);
    Solver448A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448ATest, Example2)
{
    string input = R"(1 1 3
2 3 4
2
)";
    string output = R"(YES
)";
    setInput(input);
    Solver448A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448ATest, Example3)
{
    string input = R"(1 0 0
1 0 0
1
)";
    string output = R"(NO
)";
    setInput(input);
    Solver448A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


