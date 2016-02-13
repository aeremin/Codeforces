#include <gtest/gtest.h>
#include <algo/geometry/geomvector.hpp>

TEST(GeomVector, Constructor)
{
    GeomVector2I v = GeomVector2I({ 1, 3 });
}

TEST(GeomVector, IndexAccess)
{
    GeomVector2I v = GeomVector2I({ 1, 3 });
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(3, v[1]);
}

TEST(GeomVector, LengthSquared)
{
    GeomVector2I v = GeomVector2I({ 1, 3 });
    EXPECT_EQ(10, v.lengthSquared());
}

TEST(GeomVector, OperatorSumInner)
{
    GeomVector2I a = GeomVector2I({ 1, 3 });
    GeomVector2I b = GeomVector2I({ 3, 5 });
    GeomVector2I c = GeomVector2I({ 4, 8 });
    a += b;
    EXPECT_EQ(c, a);
}

TEST(GeomVector, OperatorSubstractInner)
{
    GeomVector2I a = GeomVector2I({ 1, 3 });
    GeomVector2I b = GeomVector2I({ 3, 5 });
    GeomVector2I c = GeomVector2I({ -2, -2 });
    a -= b;
    EXPECT_EQ(c, a);
}

TEST(GeomVector, OperatorSumOuter)
{
    GeomVector2I a = GeomVector2I({ 1, 3 });
    GeomVector2I b = GeomVector2I({ 3, 5 });
    GeomVector2I c = GeomVector2I({ 4, 8 });
    EXPECT_EQ(c, a + b);
}

TEST(GeomVector, OperatorSubstractOuter)
{
    GeomVector2I a = GeomVector2I({ 1, 3 });
    GeomVector2I b = GeomVector2I({ 3, 5 });
    GeomVector2I c = GeomVector2I({ -2, -2 });
    EXPECT_EQ(c, a - b);
}

TEST(GeomVector, OperatorMultiplicationInner)
{
    GeomVector2I a = GeomVector2I({ 1, 3 });
    a *= 5;
    GeomVector2I b = GeomVector2I({ 5, 15 });
    EXPECT_EQ(b, a);
}

TEST(GeomVector, OperatorMultiplicationOuter)
{
    GeomVector2I a = GeomVector2I({ 1, 3 });
    GeomVector2I b = 5 * a;
    GeomVector2I c = a * 5;
    GeomVector2I d = GeomVector2I({ 5, 15 });
    EXPECT_EQ(d, b);
    EXPECT_EQ(d, c);
}

TEST(GeomVector, DetOfCollinearIsZero)
{
    GeomVector2I a = GeomVector2I({ 1, 3 });
    GeomVector2I b = GeomVector2I({ 2, 6 });
    EXPECT_EQ(0, det(a, b));
}

TEST(GeomVector, DetConcreteExample)
{
    GeomVector2I a = GeomVector2I({ 1, 2 });
    GeomVector2I b = GeomVector2I({ 3, 4 });
    EXPECT_EQ(-2, det(a, b));
    EXPECT_EQ( 2, det(b, a));
}

TEST(GeomVector, VariadicConstructor)
{
    GeomVector2I64 a = GeomVector2I64(1, 2);
    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
}

