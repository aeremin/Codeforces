#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/number_theory/residue.h"
#include "algo/geometry/geomvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1105/problem/C
class Solver1105C {
public:
    void run();
};

GeomVector3I distribution(int64_t n) {
    return {n / 3, (n + 2) / 3, (n + 1) / 3};
}

void Solver1105C::run() { 
    array<CodeforcesResidue64, 3> dp = {1, 0, 0};
    auto n = read<int>();
    auto l = read<int64_t>();
    auto r = read<int64_t>();
    auto d = distribution(r) - distribution(l - 1);
    for (int i : range(n)) {
        array<CodeforcesResidue64, 3> dp_next = {0, 0, 0};
        for (int j: range(3))
            for (int k : range(3)) dp_next[(j + k) % 3] += dp[j] * d[k];
        dp = dp_next;
    }
    cout << dp[0];
}


class Solver1105CTest : public ProblemTest {};


TEST_F(Solver1105CTest, Example1) {
    setInput(R"(
2 1 3

)");
    string output = R"(
3

)";
    Solver1105C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1105CTest, Example2) {
    setInput(R"(
3 2 2

)");
    string output = R"(
1

)";
    Solver1105C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1105CTest, Example3) {
    setInput(R"(
9 9 99

)");
    string output = R"(
711426616

)";
    Solver1105C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

