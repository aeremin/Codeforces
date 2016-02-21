#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/pi.h"

using namespace std;

class Solver630Q
{
public:
    void run();
    
    double vol(double l, int n)
    {
        auto x = l / (2 * (tan(kPi / n)));
        auto rr = l * l / 4.0 + x * x;
        auto h = sqrt(l * l - rr);
        auto s = l * x * n / 2;
        return s * h / 3;
    }
};

void Solver630Q::run()
{
    double a, b, c;
    cin >> a >> b >> c;
    cout << setprecision(12) << fixed << vol(a, 3) + vol(b, 4) + vol(c, 5);
}

class Solver630QTest : public ProblemTest {};

TEST_F(Solver630QTest, Example1)
{
    string input = R"(2 5 3
)";
    string output = R"(38.546168065709)";
    setInput(input);
    Solver630Q().run();
    EXPECT_EQ(output, getOutput());
}


