#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"
#include "algo/functor_iterator.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/626/problem/C
class Solver626C
{
public:
    void run();
};

void Solver626C::run()
{
    auto n = read<int>();
    auto m = read<int>();
    auto canFitIn = [&](int h) -> int
    {
        auto div2and3 = h / 6;
        auto div2not3 = h / 2 - div2and3;
        auto div3not2 = h / 3 - div2and3;
        auto nn = max(0, n - div2not3);
        auto mm = max(0, m - div3not2);
        if (nn + mm <= div2and3)
            return 1;
        else
            return 0;
    };

    auto l = makeFunctorIterator(0, canFitIn);
    auto r = makeFunctorIterator(10000000, canFitIn);
    print( lower_bound(l, r, 1).getParameter() );
}

class Solver626CTest : public ProblemTest {};

TEST_F(Solver626CTest, Example1)
{
    string input = R"(1 3
)";
    string output = R"(9
)";
    setInput(input);
    Solver626C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver626CTest, Example2)
{
    string input = R"(3 2
)";
    string output = R"(8
)";
    setInput(input);
    Solver626C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver626CTest, Example3)
{
    string input = R"(5 0
)";
    string output = R"(10
)";
    setInput(input);
    Solver626C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver626CTest, Example4)
{
    string input = R"(0 5
)";
    string output = R"(15
)";
    setInput(input);
    Solver626C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver626CTest, Example5)
{
    string input = R"(4 2
)";
    string output = R"(9
)";
    setInput(input);
    Solver626C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
