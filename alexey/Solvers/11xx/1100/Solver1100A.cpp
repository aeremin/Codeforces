#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1100/problem/A
class Solver1100A {
public:
    void run();
};

void Solver1100A::run() {
    auto n = read<int>();
    auto step = read<int>();
    auto vals = readVector<int>(n);
    const int sum = accumulate(begin(vals), end(vals), 0, plus<>());
    int ans = 0;
    for (int start = 0; start < step; ++start) {
        int currSum = sum;
        for (int j = start; j < n; j += step)
            currSum -= vals[j];
        relax_max(ans, abs(currSum));
    }
    cout << ans;
}


class Solver1100ATest : public ProblemTest {};


TEST_F(Solver1100ATest, Example1) {
    setInput(R"(
4 2
1 1 -1 1

)");
    string output = R"(
2

)";
    Solver1100A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1100ATest, Example2) {
    setInput(R"(
14 3
-1 1 -1 -1 1 -1 -1 1 -1 -1 1 -1 -1 1

)");
    string output = R"(
9

)";
    Solver1100A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

