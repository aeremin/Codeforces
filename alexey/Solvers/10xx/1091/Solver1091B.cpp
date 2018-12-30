#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/geometry/geomvector.hpp"
using namespace std;

class Solver1091B {
public:
    void run();

    int n;
    vector<GeomVector2I> offsets, points;
};

void Solver1091B::run() {
    cin >> n;
    offsets.resize(n);
    points.resize(n);
    for (auto& p : points)
        cin >> p;

    for (auto& p : offsets) {
        GeomVector2I t;
        cin >> t;
        p = -1 * t;
    }

    sort(begin(points), end(points));
    sort(begin(offsets), end(offsets));
    auto ans = points[0] - offsets[0];
    cout << ans[0] << ' ' << ans[1];
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
    output.pop_back();
    setInput(input);
    Solver1091B().run();
    EXPECT_EQ(output, getOutput());
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
    output.pop_back();
    setInput(input);
    Solver1091B().run();
    EXPECT_EQ(output, getOutput());
}

