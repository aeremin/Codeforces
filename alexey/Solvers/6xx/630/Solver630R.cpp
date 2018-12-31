#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver630R
{
public:
    void run();
};

void Solver630R::run()
{
    int64_t n;
    cin >> n;
    cout << (n % 2 == 0 ? 2 : 1);
}

class Solver630RTest : public ProblemTest {};

TEST_F(Solver630RTest, Example1)
{
    string input = R"(1
)";
    string output = R"(1)";
    setInput(input);
    Solver630R().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver630RTest, Example2)
{
    string input = R"(2
)";
    string output = R"(2)";
    setInput(input);
    Solver630R().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


