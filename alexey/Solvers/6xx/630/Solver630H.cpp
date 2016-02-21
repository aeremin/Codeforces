#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/binomial_coefficients.h"
using namespace std;

class Solver630H
{
public:
    void run();
};

void Solver630H::run()
{
    int64_t n;
    cin >> n;
    int64_t one = 1;
    cout << BinomialCoefficient(one, n, 5) * BinomialCoefficient(one, n, 5) * 120;
}

class Solver630HTest : public ProblemTest {};

TEST_F(Solver630HTest, Example1)
{
    string input = R"(5
)";
    string output = R"(120)";
    setInput(input);
    Solver630H().run();
    EXPECT_EQ(output, getOutput());
}


