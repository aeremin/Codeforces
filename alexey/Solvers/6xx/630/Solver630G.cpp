#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/binomial_coefficients.h"

using namespace std;

class Solver630G
{
public:
    void run();
};

void Solver630G::run()
{
    int64 n;
    cin >> n;
    cout << BinomialCoefficient<int64>(n + 2, 3) * BinomialCoefficient<int64>(n + 4, 5);
}

class Solver630GTest : public ProblemTest {};

TEST_F(Solver630GTest, Example1)
{
    string input = R"(2
)";
    string output = R"(24)";
    setInput(input);
    Solver630G().run();
    EXPECT_EQ(output, getOutput());
}


