
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1111/problem/B
      
class Solver1111B {
  public:
    void run();
};

void Solver1111B::run() {
    auto n = read<int64_t>();
    auto k = read<int64_t>();
    auto m = read<int64_t>();
    auto powers = readVector<int64_t>(n);
    sort(rbegin(powers), rend(powers));
    vector<int64_t> sums;
    partial_sum(begin(powers), end(powers), back_inserter(sums));
    double ans = 0;
    for (auto l : range(min(m + 1, n))) {
        double candidate = (sums[n - l - 1] + min((n - l) * k, m - l)) / double(n - l);
        relax_max(ans, candidate);
    }

    cout << setprecision(8) << ans;
}


class Solver1111BTest : public ProblemTest {};
    
TEST_F(Solver1111BTest, Example1) {
    setInput(R"(
2 4 6
4 7

)");
    string output = R"(
11

)";
    Solver1111B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1111BTest, Example2) {
    setInput(R"(
4 2 6
1 3 2 3

)");
    string output = R"(
5

)";
    Solver1111B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


