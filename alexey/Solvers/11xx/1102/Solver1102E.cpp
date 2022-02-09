#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/number_theory/residue.h"
#include "util/relax.h"
using namespace std;

using ProblemResidue = Residue<int64_t, 998244353>;

// Solution for Codeforces problem http://codeforces.com/contest/1102/problem/E
class Solver1102E {
public:
    void run();
};

void Solver1102E::run() {
    auto n = read<int>();
    auto arr = readVector<int>(n);
    map<int, int> gotos;
    for (int i: range(n))
        gotos[arr[i]] = i;

    ProblemResidue ans = 1;
    int maxGoto = 0;
    for (int i: range(n - 1)) {
        relax_max(maxGoto, gotos[arr[i]]);
        if (maxGoto == i)  {
            ans *= 2;
        }
    }

    cout << ans;
}


class Solver1102ETest : public ProblemTest {};


TEST_F(Solver1102ETest, Example1) {
    setInput(R"(
5
1 2 1 2 3

)");
    string output = R"(
2

)";
    Solver1102E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102ETest, Example2) {
    setInput(R"(
2
100 1

)");
    string output = R"(
2

)";
    Solver1102E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102ETest, Example3) {
    setInput(R"(
4
1 3 3 7

)");
    string output = R"(
4

)";
    Solver1102E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
