#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/pi.h"
using namespace std;

class Solver630P
{
public:
    void run();

    double segLen(int n, int k)
    {
        return 2 * sin((kPi * k) / n);
    }
};

void Solver630P::run()
{
    int n;
    double R;
    cin >> n >> R;

    auto k = n / 2;
    auto B = segLen(n, k);
    auto a = segLen(n, 1);
    auto A = segLen(n, k - 1);
    auto r = (a * sin((kPi * (k - 1)) / n)) / (A * sin(kPi * 2.0 / n));
    auto l = B / (1 + r) * r;
    auto s = 0.5 * l * l * sin(kPi * 3.0 / n) * n;
    auto ss = (kPi / n - 0.5 * sin(2 * kPi / n)) * n;

    auto S = (kPi - s - ss) * R * R;
    
    cout << setprecision(11) << fixed << S;
}

class Solver630PTest : public ProblemTest {};

TEST_F(Solver630PTest, Example1)
{
    string input = R"(7 10
)";
    string output = R"(108.395919545675)";
    output.pop_back();
    setInput(input);
    Solver630P().run();
    EXPECT_EQ(output, getOutput());
}


