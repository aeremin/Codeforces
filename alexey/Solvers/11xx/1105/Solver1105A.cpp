#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1105/problem/A
class Solver1105A {
public:
    void run();
};

void Solver1105A::run() {
    auto lengths = readVector<int>(read<int>());
    pair<int, int> ans = { numeric_limits<int>::max(), 0 };
    for (int t : range(1, 100)) {
        int candidate = 0;
        for (auto l : lengths) {
            if (l < t - 1)
                candidate += t - 1 - l;
            if (l > t + 1)
                candidate += l - 1 - t;
        }
        relax_min(ans, {candidate, t});
    }

    cout << ans.second << " " << ans.first;
}


class Solver1105ATest : public ProblemTest {};


TEST_F(Solver1105ATest, Example1) {
    setInput(R"(
3
10 1 4

)");
    string output = R"(
3 7

)";
    Solver1105A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1105ATest, Example2) {
    setInput(R"(
5
1 1 2 2 3

)");
    string output = R"(
2 0

)";
    Solver1105A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

