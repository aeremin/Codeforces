#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver676B {
public:
    void run();
};

void Solver676B::run() {
    int n, t;
    cin >> n >> t;
    vector<vector<int>> amount(n, vector<int>(n));
    for (int i : range(t)) {
        vector<vector<int>> inflow(n, vector<int>(n));
        for (int level : range(n))
            for (int pos : range(level + 1)) {
                int in = 0;
                if (level == 0) {
                    in = 1;
                }
                else {
                    if (pos > 0 && amount[level - 1][pos - 1] == (1 << (level - 1)))
                        in += inflow[level - 1][pos - 1];
                    if (pos < level && amount[level - 1][pos] == (1 << (level - 1)))
                        in += inflow[level - 1][pos];
                }

                amount[level][pos] += in;
                if (amount[level][pos] > (1 << level)) {
                    inflow[level][pos] = amount[level][pos] - (1 << level);
                    amount[level][pos] = 1 << level;
                }
            }
    }

    int ans = 0;
    for (int level : range(n))
        for (int pos : range(level + 1))
            ans += amount[level][pos] == (1 << level);

    cout << ans;
}


class Solver676BTest : public ProblemTest {};


TEST_F(Solver676BTest, Example1) {
    string input = R"(3 5
)";
    string output = R"(4
)";
    setInput(input);
    Solver676B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver676BTest, Example2) {
    string input = R"(4 8
)";
    string output = R"(6
)";
    setInput(input);
    Solver676B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

