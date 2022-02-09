#include <gtest/gtest.h>
#include <algo/geometry/geomvector.h>
#include <algo/geometry/convexhull.h>

TEST(ConvexHullTest, ConvexHullOfEmptyPointSetIsEmpty)
{
    auto hull = convexHull<int>({});
    EXPECT_EQ(0, hull.size());
}

TEST(ConvexHullTest, ConvexHullOfOnePointIsThatPoint)
{
    auto pt = GeomVector2I({ 1, 2 });
    auto hull = convexHull<int>({ pt });
    ASSERT_EQ(1, hull.size());
    EXPECT_EQ(pt, hull[0]);
}

TEST(ConvexHullTest, ConvexHullOfSetOfTwoSamePoints)
{
    auto pt = GeomVector2I({ 1, 2 });
    auto hull = convexHull<int>({ pt, pt });
    ASSERT_EQ(1, hull.size());
    EXPECT_EQ(pt, hull[0]);
}

TEST(ConvexHullTest, ConvexHullOfTwoPointsIsThesePoints)
{
    auto pt1 = GeomVector2I({ 1, 2 });
    auto pt2 = GeomVector2I({ 3, 7 });
    auto hull = convexHull<int>({ pt1, pt2 });
    ASSERT_EQ(2, hull.size());
    EXPECT_EQ(pt1, hull[0]);
    EXPECT_EQ(pt2, hull[1]);
}

TEST(ConvexHullTest, ConvexHullOfPointsOnLine)
{
    auto pt1 = GeomVector2I({ 1, 3 });
    auto pt2 = GeomVector2I({ 10, 30 });
    auto pt3 = GeomVector2I({ 2, 6 });
    auto pt4 = GeomVector2I({ 5, 15 });

    auto hull = convexHull<int>({ pt1, pt2, pt3, pt4 });
    ASSERT_EQ(2, hull.size());
    EXPECT_EQ(pt1, hull[0]);
    EXPECT_EQ(pt2, hull[1]);
}

TEST(ConvexHullTest, ConvexHullOfConvex)
{
    auto pt1 = GeomVector2I({ 1, 0 });
    auto pt2 = GeomVector2I({ 0, 1 });
    auto pt3 = GeomVector2I({ 0, 0 });
    auto pt4 = GeomVector2I({ 1, 1 });

    auto hull = convexHull<int>({ pt1, pt2, pt3, pt4 });
    ASSERT_EQ(4, hull.size());
    ASSERT_EQ(pt3, hull[0]);
    ASSERT_EQ(pt2, hull[1]);
    ASSERT_EQ(pt4, hull[2]);
    ASSERT_EQ(pt1, hull[3]);
}

TEST(ConvexHullTest, ConvexHullOfTriangleWithPointInside)
{
    auto pt1 = GeomVector2I({ 10, 0 });
    auto pt2 = GeomVector2I({ 0, 10 });
    auto pt3 = GeomVector2I({ 0, 0 });
    auto pt4 = GeomVector2I({ 1, 1 });

    auto hull = convexHull<int>({ pt1, pt2, pt3, pt4 });
    ASSERT_EQ(3, hull.size());
    ASSERT_EQ(pt3, hull[0]);
    ASSERT_EQ(pt2, hull[1]);
    ASSERT_EQ(pt1, hull[2]);
}

TEST(ConvexHullTest, ConvexHullOfTriangleWithPointOnEdge)
{
    auto pt1 = GeomVector2I({ 10, 0 });
    auto pt2 = GeomVector2I({ 0, 10 });
    auto pt3 = GeomVector2I({ 0, 0 });
    auto pt4 = GeomVector2I({ 5, 5 });

    auto hull = convexHull<int>({ pt1, pt2, pt3, pt4 });
    ASSERT_EQ(3, hull.size());
    ASSERT_EQ(pt3, hull[0]);
    ASSERT_EQ(pt2, hull[1]);
    ASSERT_EQ(pt1, hull[2]);
}