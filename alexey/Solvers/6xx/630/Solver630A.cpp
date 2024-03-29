#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/630/problem/A
class Solver630A
{
public:
    void run();
};

void Solver630A::run()
{
    cout << 25;
}

class Solver630ATest : public ProblemTest {};

TEST_F(Solver630ATest, Example1)
{
    string input = R"(2
)";
    string output = R"(25)";
    setInput(input);
    Solver630A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


