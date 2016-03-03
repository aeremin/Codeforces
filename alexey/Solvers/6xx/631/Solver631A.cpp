#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver631A
{
public:
    void run();
};

void Solver631A::run()
{
    auto n = read<int>();
    auto a = readVector<int>(n);
    auto b = readVector<int>(n);
    int aa = 0;
    for (auto elt : a)
        aa |= elt;
    int bb = 0;
    for (auto elt : b)
        bb |= elt;
    cout << aa + bb;
}

class Solver631ATest : public ProblemTest {};

TEST_F(Solver631ATest, Example1)
{
    string input = R"(5
1 2 4 3 2
2 3 3 12 1
)";
    string output = R"(22)";
    setInput(input);
    Solver631A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver631ATest, Example2)
{
    string input = R"(10
13 2 7 11 8 4 9 8 5 1
5 7 18 9 2 3 0 11 8 6
)";
    string output = R"(46)";
    setInput(input);
    Solver631A().run();
    EXPECT_EQ(output, getOutput());
}


