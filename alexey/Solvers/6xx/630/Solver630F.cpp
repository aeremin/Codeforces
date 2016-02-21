#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/binomial_coefficients.h"
using namespace std;

class Solver630F
{
public:
    void run();
};

void Solver630F::run()
{
    int64_t n;
    cin >> n;
    cout << BinomialCoefficient<int64>(n, 5) + BinomialCoefficient<int64>(n, 6) + BinomialCoefficient<int64>(n, 7);
}

class Solver630FTest : public ProblemTest {};

TEST_F(Solver630FTest, Example1)
{
    string input = R"(7
)";
    string output = R"(29)";
    setInput(input);
    Solver630F().run();
    EXPECT_EQ(output, getOutput());
}


