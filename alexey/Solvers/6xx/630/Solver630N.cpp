#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver630N
{
public:
    void run();
};

void Solver630N::run()
{
    double a, b, c;
    cin >> a >> b >> c;
    double d = sqrt(b * b - 4 * a * c);
    double x1 = (-b - d) / (2 * a);
    double x2 = (-b + d) / (2 * a);
    if (a < 0)
        swap(x1, x2);
    cout << setprecision(10) << fixed << x2 << "\n" << x1;
}

class Solver630NTest : public ProblemTest {};

TEST_F(Solver630NTest, Example1)
{
    string input = R"(1 30 200
)";
    string output = R"(-10.0000000000
-20.0000000000)";          
    setInput(input);
    Solver630N().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


