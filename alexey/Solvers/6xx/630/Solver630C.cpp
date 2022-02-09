#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/630/problem/C
class Solver630C
{
public:
    void run();
};

void Solver630C::run()
{
    int n;
    cin >> n;
    cout << (int64_t(1) << (n + 1)) - 2;
}

class Solver630CTest : public ProblemTest {};

TEST_F(Solver630CTest, Example1)
{
    string input = R"(2
)";
    string output = R"(6)";
    setInput(input);
    Solver630C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


