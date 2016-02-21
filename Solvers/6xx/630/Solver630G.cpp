#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/Range.hpp"
#include "algo/algebra/BinomialCoefficients.hpp"

using namespace std;

class Solver630G
{
public:
    void run();
};

void Solver630G::run()
{
    int64_t n;
    cin >> n;
    int64_t one = 1;
    cout << binomialCoefficient(one, n + 2, 3) * binomialCoefficient(one, n + 4, 5);
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


