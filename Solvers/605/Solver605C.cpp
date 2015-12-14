#include "Solvers/pch.h"
#include "Solver605C.h"
#include "algo/geometry/geomvector.hpp"
#include "algo/geometry/convexhull.hpp"

using Point = GeomVector2<int64_t>;

void Solver605C::run()
{
    int64_t n, p, q;
    cin >> n >> p >> q;
    std::vector<Point> points;
    for (int i = 0; i < n; ++i)
    {
        int64_t a, b;
        cin >> a >> b;
        points.push_back(Point({ a, b }));
        points.push_back(Point({ a, 0 }));
        points.push_back(Point({ 0, b }));
    }

    auto hullPoints = convexHull(points);
    
    Point target({ p, q });
    for (size_t i = 0; i < hullPoints.size() - 1; ++i)
    {
        auto ptCurr = hullPoints[i];
        auto ptNext = hullPoints[i + 1];
        if (det(ptCurr, target) < 0 && det(ptNext, target) >= 0)
        {
            double diff = double(det(ptNext, target) - det(ptCurr, target));
            double t = (0.0 - det(ptCurr, target)) / diff;
            double pp = (1 - t) * ptCurr[0] + t * ptNext[0];
            std::cout << std::setprecision(15) << std::fixed << p / pp;
            return;
        }
    }
}

class Solver605CTest : public ProblemTest {};

TEST_F(Solver605CTest, Example1)
{
    setInput("3 20 20        6 2        1 3        2 6");
    Solver605C().run();
    EXPECT_EQ("5.000000000000000", getOutput());
}

TEST_F(Solver605CTest, Example2)
{
    setInput("4 1 1        2 3        3 2        2 3        3 2");
    Solver605C().run();
    EXPECT_EQ("0.400000000000000", getOutput());
}