
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/combinatorics/combinatorics_helper.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1109/problem/D
      
class Solver1109D {
  public:
    void run();
};

void Solver1109D::run() {
    auto n = read<int>();
    auto m = read<int>();
    auto a = read<int>();
    auto b = read<int>();
    CombinatoricsHelper<int64_t, cCodeforcesModulo> h(max(n, m));
    vector<CodeforcesResidue64> powers_m = { 1 };
    powers_m.reserve(n);
    for (int i : range(n)) powers_m.push_back(powers_m.back() * m);

    vector<CodeforcesResidue64> powers_n = {1};
    powers_n.reserve(n);
    for (int i : range(n))
        powers_n.push_back(powers_n.back() * n);

    CodeforcesResidue64 ans = 0;
    for (int l : range(min(m, n - 1))) {
        auto mu = (l + 2 == n) ? CodeforcesResidue64(1) : CodeforcesResidue64(l + 2) * powers_n[n - l - 3];
        ans += h.factorial(n - 2) * h.inverted_factorial(n - l - 2) * h.binomial_coefficient(m - 1, l) * powers_m[n - l - 2] * mu;
    }

    cout << ans;
}


class Solver1109DTest : public ProblemTest {};
    
TEST_F(Solver1109DTest, Example1) {
    setInput(R"(
3 2 1 3

)");
    string output = R"(
5

)";
    Solver1109D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109DTest, Example2) {
    setInput(R"(
3 1 1 2

)");
    string output = R"(
2

)";
    Solver1109D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109DTest, Example3) {
    setInput(R"(
5 15 1 5

)");
    string output = R"(
345444

)";
    Solver1109D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


