#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1100/problem/B
class Solver1100B {
public:
    void run();
};

void Solver1100B::run() {
    const auto n = read<int>();
    const auto m = read<int>();
    const auto problems = readVector<int>(m);

    map<int, int> counts;
    string res;

    auto reduce_and_remove = [&counts](int p) {
        --counts[p];
        if (counts[p] == 0) counts.erase(p);
    };

    for (auto p : problems) {
        counts[p - 1]++;
        if (counts.size() == n) {
            for (int i = 0; i < n; ++i) {
                reduce_and_remove(i);
            }
            res.push_back('1');
        }
        else {
            res.push_back('0');
        }
    }
    cout << res;
}


class Solver1100BTest : public ProblemTest {};


TEST_F(Solver1100BTest, Example1) {
    setInput(R"(
3 11
2 3 1 2 2 2 3 2 2 3 1

)");
    string output = R"(
00100000001

)";
    Solver1100B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1100BTest, Example2) {
    setInput(R"(
4 8
4 1 3 3 2 3 3 3

)");
    string output = R"(
00001000

)";
    Solver1100B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

