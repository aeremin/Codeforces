#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/617/problem/C
class Solver617C
{
public:
    void run();
};

void Solver617C::run()
{
    int n;
    cin >> n;
    GeomVector2I64 f1, f2;
    cin >> f1[0] >> f1[1] >> f2[0] >> f2[1];
    vector<GeomVector2I64> flowers(n);
    for (auto& f : flowers)
        cin >> f[0] >> f[1];

    vector<pair<int64_t, int64_t>> distances(n);
    for (int i = 0; i < n; ++i)
        distances[i] = { (flowers[i] - f1).lengthSquared(),
                        (flowers[i] - f2).lengthSquared() };

    sort(begin(distances), end(distances));

    int64_t bestDistance = numeric_limits<int64_t>::max();
    for (int i = -1; i < n; ++i)
    {
        auto dist1 = (i == -1) ? 0 : distances[i].first;
        int64_t dist2 = 0;
        for (int j = i + 1; j < n; ++j)
            relax_max(dist2, distances[j].second);
        relax_min(bestDistance, dist1 + dist2);
    }

    cout << bestDistance;
}

class Solver617CTest : public ProblemTest
{
};

TEST_F( Solver617CTest, Example1 )
{
    setInput("2 -1 0 5 3             0 2             5 2");
    Solver617C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F( Solver617CTest, Example2 )
{
    setInput("4 0 0 5 0             9 4             8 3             -1 0             1 4");
    Solver617C().run();
    EXPECT_EQ("33", getOutput());
}
