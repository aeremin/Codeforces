#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/FunctorIterator.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/448/problem/D
class Solver448D
{
public:
    void run();
};

void Solver448D::run()
{
    int64_t n, m, k;
    cin >> n >> m >> k;
    auto countLowerOrEqual = [&](int64_t p) -> int64_t {
        int64_t res = 0;
        for (auto i : range(n))
            res += min(m, p / (i + 1));
        return res;
    };

    auto l = makeFunctorIterator(int64_t(1), countLowerOrEqual);
    auto r = makeFunctorIterator(int64_t(m * n + 1), countLowerOrEqual);
    cout << lower_bound(l, r, k).getParameter();
}

class Solver448DTest : public ProblemTest {};

TEST_F(Solver448DTest, Example1)
{
    string input = R"(2 2 2
)";
    string output = R"(2
)";
    setInput(input);
    Solver448D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448DTest, Example2)
{
    string input = R"(2 3 4
)";
    string output = R"(3
)";
    setInput(input);
    Solver448D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448DTest, Example3)
{
    string input = R"(1 10 5
)";
    string output = R"(5
)";
    setInput(input);
    Solver448D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}



