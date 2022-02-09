#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/geometry/geomvector.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/671/problem/A
class Solver671A {
public:
    void run();
};

void Solver671A::run() {
    GeomVector2D p1, p2, t;
    cin >> p1 >> p2 >> t;
    int n = read<int>();
    vector<GeomVector2D> bottles(n);
    for (auto& b : bottles)
        cin >> b;

    double s = 0;
    for (auto b : bottles)
        s += 2 * sqrt((b - t).lengthSquared());

    vector<pair<double, int>> v1(n), v2(n);
    for (int i : range(n)) {
        auto b = bottles[i];
        v1[i] = { sqrt((p1 - b).lengthSquared()) - sqrt((t - b).lengthSquared()), i };
        v2[i] = { sqrt((p2 - b).lengthSquared()) - sqrt((t - b).lengthSquared()), i };
    }

    sort(begin(v1), end(v1));
    sort(begin(v2), end(v2));

    double ans = numeric_limits<double>::max();
    relax_min(ans, v1[0].first);
    relax_min(ans, v2[0].first);
    if (v1[0].second != v2[0].second) {
        relax_min(ans, v1[0].first + v2[0].first);
    }
    else if (n > 1) {
        relax_min(ans, v1[0].first + v2[1].first);
        relax_min(ans, v1[1].first + v2[0].first);
    }

    ans += s;

    cout << setprecision(12) << fixed << ans;
}


class Solver671ATest : public ProblemTest {};


TEST_F(Solver671ATest, Example1) {
    string input = R"(3 1 1 2 0 0
3
1 1
2 1
2 3
)";
    string output = R"(11.084259940083
)";
    setInput(input);
    Solver671A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver671ATest, Example2) {
    string input = R"(5 0 4 2 2 0
5
5 2
3 0
5 5
3 5
3 3
)";
    string output = R"(33.121375178000
)";
    setInput(input);
    Solver671A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver671ATest, Example3) {
    string input = R"(5 0 5 0 0 0
1
0 0
)";
    string output = R"(5.000000000000
)";
    setInput(input);
    Solver671A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
