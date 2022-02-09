#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/630/problem/J
class Solver630J
{
public:
    void run();
};

void Solver630J::run()
{
    int64_t n;
    cin >> n;
    cout << n / 2520;
}

class Solver630JTest : public ProblemTest {};

TEST_F(Solver630JTest, Example1)
{
    string input = R"(3000
)";
    string output = R"(1)";
    setInput(input);
    Solver630J().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


