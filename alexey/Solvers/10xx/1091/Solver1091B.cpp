#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/geometry/geomvector.hpp"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1091/problem/B
class Solver1091B {
public:
    void run();
};

void Solver1091B::run() {
    auto n = read<int>();
    auto offsets = readVector<GeomVector2I>(n);
    auto points = readVector<GeomVector2I>(n);

    auto p = *min_element(begin(points), end(points));
    auto o = *max_element(begin(offsets), end(offsets));
    cout << p + o;
}


class Solver1091BTest : public ProblemTest {};


TEST_F(Solver1091BTest, Example1) {
    string input = R"(
2
2 5
-6 4
7 -2
-1 -3

)";
    string output = R"(1 2
)";
    setInput(input);
    Solver1091B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1091BTest, Example2) {
    string input = R"(
4
2 2
8 2
-7 0
-2 6
1 -14
16 -12
11 -18
7 -14

)";
    string output = R"(9 -12
)";
    setInput(input);
    Solver1091B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

