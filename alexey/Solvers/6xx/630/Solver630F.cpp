#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/algebra/BinomialCoefficients.hpp"
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
    int64_t one = 1;
    cout << binomialCoefficient(one, n, 5) + binomialCoefficient(one, n, 6) + binomialCoefficient(one, n, 7);
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


