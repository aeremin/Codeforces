#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/Range.hpp"
using namespace std;

class Solver630B
{
public:
    void run();
};

void Solver630B::run()
{
    double a, t;
    cin >> a >> t;
    cout << setprecision(6) << fixed << a * pow(1.000000011, t);
}

class Solver630BTest : public ProblemTest {};

TEST_F(Solver630BTest, Example1)
{
    string input = R"(1000 1000000
)";
    string output = R"(1011.060722
)";
    output.pop_back();
    setInput(input);
    Solver630B().run();
    EXPECT_EQ(output, getOutput());
}


