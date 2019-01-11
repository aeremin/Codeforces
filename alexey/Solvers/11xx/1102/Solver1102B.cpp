#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/io/readvector.hpp"
#include "algo/io/printvector.h"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1102/problem/B
class Solver1102B {
public:
    void run();
};

void Solver1102B::run() {
    auto n = read<int>();
    auto k = read<int>();
    auto arr = readVector<int>(n);
    if (n < k) {
        cout << "NO";
        return;
    }
    vector<int> colors(n);
    int maxColorUsed = 0;
    unordered_map<int, int> maxColorUsedPerValue;
    for (int i: range(n)) {
        auto v = arr[i];
        auto color = maxColorUsedPerValue[v] + 1;
        if (color > k) {
            cout << "NO";
            return;
        }
        colors[i] = color;
        maxColorUsedPerValue[v] = color;
        relax_max(maxColorUsed, color);
    }

    map<int, int> colorCount;
    for (int i : range(n)) {
        colorCount[colors[i]]++;
        if (maxColorUsed < k && colorCount[colors[i]] > 1) {
            --colorCount[colors[i]];
            colors[i] = ++maxColorUsed;
        }
    }

    cout << "YES\n";
    printVector(colors);
}


class Solver1102BTest : public ProblemTest {};


TEST_F(Solver1102BTest, Example1) {
    setInput(R"(
4 2
1 2 2 3

)");
    string output = R"(
YES
1 1 2 1

)";
    Solver1102B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102BTest, Example2) {
    setInput(R"(
5 2
3 2 1 2 3

)");
    string output = R"(
YES
1 1 1 2 2

)";
    Solver1102B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102BTest, Example3) {
    setInput(R"(
5 2
2 1 1 2 1

)");
    string output = R"(
NO

)";
    Solver1102B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver1102BTest, Example4) {
    setInput(R"(
6 6
1 1 1 1 2 3

)");
    string output = R"(
YES
1 2 3 4 5 6
)";
    Solver1102B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
