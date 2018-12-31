#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Residue.hpp"
using namespace std;

using ProblemResidue = Residue<int64_t, 998244353>;

class Solver1091D {
public:
    void run();
};

void Solver1091D::run() {
    int n;
    cin >> n;

    vector<ProblemResidue> factorials(n + 1);
    factorials[0] = 1;
    for (int i : range(1, n + 1))
        factorials[i] = factorials[i - 1] * int64_t(i);

    vector<ProblemResidue> invertedFactorials(n + 1);
    invertedFactorials[n] = factorials[n].inversed();
    for (int i = n - 1; i >= 0; --i)
        invertedFactorials[i] = invertedFactorials[i + 1] * int64_t(i + 1);

    ProblemResidue res = factorials[n];
    for (int x = 1; x < n; ++x) {
        res += factorials[n - 1 - x] * int64_t(n - 1 - x) * factorials[n] * invertedFactorials[x + 1] * invertedFactorials[n - x - 1] * int64_t(x);
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

