#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"
#include "util/relax.h"
#include "math/pi.h"

using namespace std;

class Solver613A
{
public:
    void run();
};

void Solver613A::run()
{
    int nVertices;
    GeomVector2D center;
    cin >> nVertices >> center[0] >> center[1];
    vector<GeomVector2D> vertices(nVertices);
    for (auto& elt : vertices)
        cin >> elt[0] >> elt[1];

    double minDist = numeric_limits<double>::max();
    double maxDist = numeric_limits<double>::min();
    for (int i = 0; i < nVertices; ++i)
    {
        auto currPt = vertices[i];
        auto nextPt = vertices[(i + 1) % nVertices];
        relax_max(maxDist, (currPt - center).lengthSquared());
        relax_min(minDist, (currPt - center).lengthSquared());
        double d = dot(center - currPt, nextPt - currPt) / dot(nextPt - currPt, nextPt - currPt);
        if (d >= 0 && d <= 1)
            relax_min(minDist, (currPt + d * (nextPt - currPt) - center).lengthSquared());
    }

    cout << setprecision(15) << fixed << kPi * (maxDist - minDist);
}

class Solver613ATest : public ProblemTest
{
};

TEST_F( Solver613ATest, Example1 )
{
    setInput("3 0 0             0 1             -1 2             1 2");
    Solver613A().run();
    EXPECT_EQ("12.566370614359172", getOutput());
}

TEST_F( Solver613ATest, Example2 )
{
    setInput("4 1 -1             0 0             1 2             2 0             1 1             ");
    Solver613A().run();
    EXPECT_EQ("21.991148575128552", getOutput());
}
