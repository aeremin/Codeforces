#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/binomial_coefficients.h"
#include "math/quick_power.h"
using namespace std;

class Solver630I
{
public:
    void run();
};

void Solver630I::run()
{
    int64_t n;
    cin >> n;
    cout << 4 * ((n - 3) * quick_power<int64_t>(4, n - 4) * 9 +
                  2 * quick_power<int64_t>(4, n - 3) * 3);
}

class Solver630ITest : public ProblemTest {};

TEST_F(Solver630ITest, Example1)
{
    string input = R"(3
)";
    string output = R"(24)";
    setInput(input);
    Solver630I().run();
    EXPECT_EQ(output, getOutput());
}


