#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver630J
{
public:
    void run();
};

void Solver630J::run()
{
    int64_t n;
    cin >> n;
    cout << n / 2520;
}

class Solver630JTest : public ProblemTest {};

TEST_F(Solver630JTest, Example1)
{
    string input = R"(3000
)";
    string output = R"(1)";
    setInput(input);
    Solver630J().run();
    EXPECT_EQ(output, getOutput());
}


