
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1106/problem/C
      
class Solver1106C {
  public:
    void run();
};

void Solver1106C::run() {
    auto a = readVector<int>(read<int>());
    sort(begin(a), end(a));
    int64_t ans = 0;
    for (int i : range(a.size() / 2)) {
        auto s = a[i] + a[a.size() - 1 - i];
        ans += s * s;
    }

    cout << ans;
}


class Solver1106CTest : public ProblemTest {};
    
TEST_F(Solver1106CTest, Example1) {
    setInput(R"(
4
8 5 2 3

)");
    string output = R"(
164

)";
    Solver1106C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106CTest, Example2) {
    setInput(R"(
6
1 1 1 2 2 2

)");
    string output = R"(
27

)";
    Solver1106C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


