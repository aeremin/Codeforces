#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "math/sqr.h"
using namespace std;

class Solver559A
{
public:
    void run();
};

void Solver559A::run()
{
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    cout << sqr(a + b + c) - sqr(a) - sqr(c) - sqr(e);
}

class Solver559ATest : public ProblemTest {};

TEST_F(Solver559ATest, Example1)
{
    string input = R"(1 1 1 1 1 1
)";
    string output = R"(6
)";
    output.pop_back();
    setInput(input);
    Solver559A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver559ATest, Example2)
{
    string input = R"(1 2 1 2 1 2
)";
    string output = R"(13
)";
    output.pop_back();
    setInput(input);
    Solver559A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


