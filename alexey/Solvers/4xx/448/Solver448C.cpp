#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/448/problem/C
class Solver448C
{
public:
    void run();

    int64_t ans(vector<int>::iterator l, vector<int>::iterator r, int offs) {
        if (l == r) return 0;
        auto it = min_element(l, r);
        return min<int64_t>(r - l, *it - offs + ans(l, it, *it) + ans(it + 1, r, *it));
    }
};

void Solver448C::run()
{
    auto n = read<int>();
    auto d = readVector<int>(n);
    cout << ans(begin(d), end(d), 0);
}

class Solver448CTest : public ProblemTest {};

TEST_F(Solver448CTest, Example1)
{
    string input = R"(5
2 2 1 2 1
)";
    string output = R"(3
)";
    setInput(input);
    Solver448C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448CTest, Example2)
{
    string input = R"(2
2 2
)";
    string output = R"(2
)";
    setInput(input);
    Solver448C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448CTest, Example3)
{
    string input = R"(1
5
)";
    string output = R"(1
)";
    setInput(input);
    Solver448C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


