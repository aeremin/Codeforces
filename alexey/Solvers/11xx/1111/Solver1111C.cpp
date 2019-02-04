
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1111/problem/C
      
class Solver1111C {
  public:
    void run();
    int n, k;
    int64_t A, B;
    vector<int64_t> positions;

    int number_of_avengers(int64_t l, int64_t r) {
        auto it_r = lower_bound(begin(positions), end(positions), r);
        auto it_l = lower_bound(begin(positions), end(positions), l);
        return it_r - it_l;
    };

    int64_t answer_for_interval(int64_t l, int64_t r) {
        auto total_avengers = number_of_avengers(l, r);
        int64_t res = total_avengers == 0 ? A : B * total_avengers * (r - l);
        if (r - l > 1 && total_avengers > 0) {
            auto m = (r + l) / 2;
            relax_min(res, answer_for_interval(l, m) + answer_for_interval(m, r));
        }
        return res;
    };
};

void Solver1111C::run() {
    n = read<int>();
    k = read<int>();
    A = read<int64_t>();
    B = read<int64_t>();
    positions = readVector<int64_t>(k);
    sort(begin(positions), end(positions));
    cout << answer_for_interval(1, (int64_t(1) << n) + 1);
}


class Solver1111CTest : public ProblemTest {};
    
TEST_F(Solver1111CTest, Example1) {
    setInput(R"(
2 2 1 2
1 3

)");
    string output = R"(
6

)";
    Solver1111C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1111CTest, Example2) {
    setInput(R"(
3 2 1 2
1 7

)");
    string output = R"(
8

)";
    Solver1111C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


