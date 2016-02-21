#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/Range.hpp"
#include "algo/io/readvector.hpp"
#include "algo/SlidingWindowMinFinder.h"
#include "algo/Relax.hpp"
using namespace std;

class Solver594A
{
public:
    void run();
};

void Solver594A::run()
{
    auto n = read<int>();
    auto pos = readVector<int>(n);
    sort(begin(pos), end(pos));
    
    auto l = n / 2 - 1;
    int ans = numeric_limits<int>::max();
    for (int i : range(l + 1))
        relaxMin(ans, pos[i + l + 1] - pos[i]);

    print(ans);
}

class Solver594ATest : public ProblemTest {};

TEST_F(Solver594ATest, Example1)
{
    string input = R"(6
0 1 3 7 15 31
)";
    string output = R"(7
)";
    output.pop_back();
    setInput(input);
    Solver594A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver594ATest, Example2)
{
    string input = R"(2
73 37
)";
    string output = R"(36
)";
    output.pop_back();
    setInput(input);
    Solver594A().run();
    EXPECT_EQ(output, getOutput());
}


