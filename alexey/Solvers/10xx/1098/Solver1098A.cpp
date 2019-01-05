#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1098/problem/A
class Solver1098A {
public:
    void run();
};

void Solver1098A::run() {
    auto n = read<int>();

    vector<int64_t> parents(n);
    parents[0] = -1;
    for (int i : range(1, n))
        parents[i] = read<int>() - 1;

    auto sums = readVector<int64_t>(n);

    vector<vector<int>> childs(n);
    for (int i : range(1, n)) {
        childs[parents[i]].push_back(i);
    }

    int64_t ans = sums[0];

    for (int i : range(n)) {
        // Height is even, value be calculated by parent.
        if (sums[i] != -1) continue;
        
        // We can safely assume that value is 0, no modification
        // on ans is required.
        if (childs[i].empty()) continue;

        int64_t parent_sum = sums[parents[i]];
        int64_t min_child_sum = numeric_limits<int64_t>::max();
        for (auto child : childs[i]) {
            relax_min(min_child_sum, sums[child]);
        }
        int64_t value = min_child_sum - parent_sum;
        if (value < 0) {
            cout << -1;
            return;
        }
        
        ans += value;

        for (auto& child : childs[i]) {
            ans += sums[child] - parent_sum - value;
        }
    }

    cout << ans;
}


class Solver1098ATest : public ProblemTest {};


TEST_F(Solver1098ATest, Example1) {
    setInput(R"(
5
1 1 1 1
1 -1 -1 -1 -1

)");
    string output = R"(
1

)";
    Solver1098A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1098ATest, Example2) {
    setInput(R"(
5
1 2 3 1
1 -1 2 -1 -1

)");
    string output = R"(
2

)";
    Solver1098A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1098ATest, Example3) {
    setInput(R"(
3
1 2
2 -1 1

)");
    string output = R"(
-1

)";
    Solver1098A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


