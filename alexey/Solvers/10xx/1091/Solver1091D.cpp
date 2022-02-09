#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/number_theory/residue.h"
#include "algo/combinatorics/combinatorics_helper.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1091/problem/D
class Solver1091D {
public:
    void run();
};

void Solver1091D::run() {
    int n;
    cin >> n;

    using Helper = CombinatoricsHelper<int64_t, 998244353>;
    Helper helper{ n };

    auto res = helper.factorial(n);
    for (int x = 1; x < n; ++x) {
        res += Helper::ValueType(x) * Helper::ValueType(n - x - 1) * helper.factorial(n - x - 1) * helper.binomial_coefficient(n, x + 1);
    }

    cout << res;
}


class Solver1091DTest : public ProblemTest {};


TEST_F(Solver1091DTest, Example1) {
    setInput(R"(
3

)");
    string output = R"(9
)";
    Solver1091D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1091DTest, Example2) {
    setInput(R"(
4

)");
    string output = R"(56
)";
    Solver1091D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1091DTest, Example3) {
    setInput(R"(
10

)");
    string output = R"(30052700
)";
    Solver1091D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

