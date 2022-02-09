#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1105/problem/B
class Solver1105B {
  public:
    void run();
};

void Solver1105B::run() {
    read<int>();
    auto k = read<int>();
    auto s = read<string>();
    int ans = 0;
    for (char c : range('a', char('z' + 1))) {
        int canditate = 0;
        int current_length = 0;
        for (char ch: s) {
            if (ch == c) {
                current_length++;
            } else {
                canditate += current_length / k;
                current_length = 0;
            }
        }
        canditate += current_length / k;
        relax_max(ans, canditate);
    }
    cout << ans;
}


class Solver1105BTest : public ProblemTest {};


TEST_F(Solver1105BTest, Example1) {
    setInput(R"(
8 2
aaacaabb

)");
    string output = R"(
2

)";
    Solver1105B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1105BTest, Example2) {
    setInput(R"(
2 1
ab

)");
    string output = R"(
1

)";
    Solver1105B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1105BTest, Example3) {
    setInput(R"(
4 2
abab

)");
    string output = R"(
0

)";
    Solver1105B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
