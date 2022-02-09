#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "math/binomial_coefficients.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/630/problem/H
class Solver630H
{
public:
    void run();
};

void Solver630H::run()
{
    int64 n;
    cin >> n;
    cout << BinomialCoefficient<int64>(n, 5) * BinomialCoefficient<int64>(n, 5) * 120;
}

class Solver630HTest : public ProblemTest {};

TEST_F(Solver630HTest, Example1)
{
    string input = R"(5
)";
    string output = R"(120)";
    setInput(input);
    Solver630H().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


