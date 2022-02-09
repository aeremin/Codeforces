#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/676/problem/A
class Solver676A {
public:
    void run();
};

void Solver676A::run() {
    int n = read<int>();
    auto a = readVector<int>(n);

    auto b = a;

    auto pos = [&](int t) {
        for (int i : range(n))
            if (b[i] == t)
                return i;
        return -1;
    };

    int ans = numeric_limits<int>::min();
    for (int i : range(n))
        for (int j : range(i)) {
            b = a;
            swap(b[i], b[j]);
            relax_max(ans, abs(pos(1) - pos(n)));
        }

    cout << ans;
}


class Solver676ATest : public ProblemTest {};


TEST_F(Solver676ATest, Example1) {
    string input = R"(5
4 5 1 3 2
)";
    string output = R"(3
)";
    setInput(input);
    Solver676A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver676ATest, Example2) {
    string input = R"(7
1 6 5 3 4 7 2
)";
    string output = R"(6
)";
    setInput(input);
    Solver676A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver676ATest, Example3) {
    string input = R"(6
6 5 4 3 2 1
)";
    string output = R"(5
)";
    setInput(input);
    Solver676A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

