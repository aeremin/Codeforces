#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/io/printvector.h"
using namespace std;

class Solver674A {
public:
    void run();
};

void Solver674A::run() {
    int n;
    cin >> n;
    auto colors = readVector<int>(n);

    vector<vector<int>> colorOnPrefixCount(n, { 0 });

    for (auto c : colors)
        for (int iColor : range(n))
            colorOnPrefixCount[iColor].push_back(colorOnPrefixCount[iColor].back()
                                                 + (iColor == (c - 1)));

    vector<int> ans(n);

    for (int l : range(n)) {
        int bestCnt = 0;
        int bestColor = -1;

        for (int r : range(l, n)) {
            int candColor = colors[r] - 1;
            int candColorCnt = colorOnPrefixCount[candColor][r + 1] - colorOnPrefixCount[candColor][l];

            if (make_pair(candColorCnt, -candColor) > make_pair(bestCnt, -bestColor))
                tie(bestCnt, bestColor) = make_pair(candColorCnt, candColor);

            ++ans[bestColor];
        }
    }

    printVector(ans);
}


class Solver674ATest : public ProblemTest {};


TEST_F(Solver674ATest, Example1) {
    string input = R"(4
1 2 1 2
)";
    string output = R"(7 3 0 0
)";
    setInput(input);
    Solver674A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver674ATest, Example2) {
    string input = R"(3
1 1 1
)";
    string output = R"(6 0 0
)";
    setInput(input);
    Solver674A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

