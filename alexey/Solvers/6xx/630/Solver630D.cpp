#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/630/problem/D
class Solver630D
{
public:
    void run();
};

void Solver630D::run()
{
    int64_t n;
    cin >> n;
    cout << 1 + 3 * n * (n + 1);
}

class Solver630DTest : public ProblemTest {};

TEST_F(Solver630DTest, Example1)
{
    string input = R"(2
)";
    string output = R"(19)";
    setInput(input);
    Solver630D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


