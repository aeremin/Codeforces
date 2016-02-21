#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/Range.hpp"
using namespace std;

class Solver630A
{
public:
    void run();
};

void Solver630A::run()
{
    cout << 25;
}

class Solver630ATest : public ProblemTest {};

TEST_F(Solver630ATest, Example1)
{
    string input = R"(2
)";
    string output = R"(25)";
    setInput(input);
    Solver630A().run();
    EXPECT_EQ(output, getOutput());
}


