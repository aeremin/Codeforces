#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/SlidingWindowMinFinder.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/594/problem/A
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
        relax_min(ans, pos[i + l + 1] - pos[i]);

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
    setInput(input);
    Solver594A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver594ATest, Example2)
{
    string input = R"(2
73 37
)";
    string output = R"(36
)";
    setInput(input);
    Solver594A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


