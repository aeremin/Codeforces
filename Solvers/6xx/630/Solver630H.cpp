#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/range.hpp"
#include "algo/algebra/BinomialCoefficients.hpp"
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
    cout << binomialCoefficient(one, n, 5) * binomialCoefficient(one, n, 5) * 120;
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


