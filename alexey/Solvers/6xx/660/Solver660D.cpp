#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/geometry/geomvector.hpp"
using namespace std;

class Solver660D
{
public:
    void run();
};

void Solver660D::run()
{
    int64_t n;
    cin >> n;
    vector<GeomVector2I> pts(n);
    for (auto& pt : pts)
        cin >> pt[0] >> pt[1];
    
    map<GeomVector2I, int64_t> cnt;
    for (auto p1 : pts)
        for (auto p2 : pts)
            cnt[p1 - p2]++;

    int64_t ans = 0;
    for (auto p : cnt)
        ans += (p.second - 1) * p.second / 2;

    ans -= n * (n - 1) / 2;
    ans /= 4;
    cout << ans;
}

class Solver660DTest : public ProblemTest {};

TEST_F(Solver660DTest, Example1)
{
    string input = R"(4
0 1
1 0
1 1
2 0
)";
    string output = R"(1
)";
    setInput(input);
    Solver660D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


