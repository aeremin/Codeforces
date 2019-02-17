
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1109/problem/A
      
class Solver1109A {
  public:
    void run();
};

void Solver1109A::run() {
    auto n = read<int>();
    auto nums = readVector<uint64_t>(n);
    vector<map<uint64_t, int64_t>> counts = { {}, {} };
    uint64_t s = 0;
    counts[0][0] = 1;
    for (int i : range(n)) {
        s ^= nums[i];
        counts[(i + 1) % 2][s]++;
    }

    int64_t ans = 0;
    for (int i : range(2)) {
        for (auto[unused, c] : counts[i]) {
            ans += c * (c - 1) / 2;
        }
    }

    cout << ans;
}


class Solver1109ATest : public ProblemTest {};
    
TEST_F(Solver1109ATest, Example1) {
    setInput(R"(5
1 2 3 4 5
)");
    string output = R"(1
)";
    Solver1109A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109ATest, Example2) {
    setInput(R"(6
3 2 2 3 7 6
)");
    string output = R"(3
)";
    Solver1109A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109ATest, Example3) {
    setInput(R"(3
42 4 2
)");
    string output = R"(0
)";
    Solver1109A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


