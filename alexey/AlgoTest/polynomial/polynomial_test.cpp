#include <gtest/gtest.h>
#include "algo/polynomial/polynomial.h"

TEST( PolynomialTest, CanConstructSomePolynomial ) {
    Polynomial<int> p = { 1, 2, 1 };
    EXPECT_EQ( 2, p.formal_degree() );
}

TEST( PolynomialTest, CanAddHigherPowerToExistingPolynomial ) {
    Polynomial<int> p = { 1, 2, 1 };
    p.set_coefficient( 10, 5 );
    EXPECT_EQ( 10, p.formal_degree() );
}

TEST( PolynomialTest, TrailinZeroCoefficientDontAffectEquality ) {
    Polynomial<int> p = { 1, 2, 1 };
    Polynomial<int> q = { 1, 2, 1, 0, 0 };
    EXPECT_EQ( p, q );
}

TEST( PolynomialTest, DifferentPolynomialsAreNotEqual ) {
    Polynomial<int> p = { 1, 2, 1 };
    Polynomial<int> q = { 1, 2, 2 };
    EXPECT_NE( p, q );
}

TEST( PolynomialTest, CanAddToSelf ) {
    Polynomial<int> p = { 1, 2, 1 };
    Polynomial<int> q = { 1, 0, 0, 5 };
    p += q;
    Polynomial<int> expectedSum = { 2, 2, 1, 5 };
    EXPECT_EQ( expectedSum, p );
}

TEST( PolynomialTest, CanMultiplySelf ) {
    Polynomial<int> p = { 1, 2, 1 };
    int m = 3;
    p *= 3;
    Polynomial<int> expectedProduct = { 3, 6, 3 };
    EXPECT_EQ( expectedProduct, p );
}

TEST( PolynomialTest, CanAdd ) {
    Polynomial<int> p = { 1, 2, 1 };
    Polynomial<int> q = { 1, 0, 0, 5 };
    Polynomial<int> expectedSum = { 2, 2, 1, 5 };
    EXPECT_EQ( expectedSum, p + q );
}

TEST( PolynomialTest, CanSubstract ) {
    Polynomial<int> p = { 1, 2, 1 };
    Polynomial<int> q = { 1, 0, 0, 5 };
    Polynomial<int> expectedDiff = { 0, 2, 1, -5 };
    EXPECT_EQ( expectedDiff, p - q);
}

TEST( PolynomialTest, CanMultiplyOnScalar ) {
    Polynomial<int> p = { 1, 2, 1 };
    int m = 3;
    Polynomial<int> expectedProduct = { 3, 6, 3 };
    EXPECT_EQ( expectedProduct, m * p );
    EXPECT_EQ( expectedProduct, p * m );
}

TEST( PolynomialTest, CanMultiply ) {
    Polynomial<int> p = { 1, 1 };
    Polynomial<int> q = { 1, 2, 1 };
    Polynomial<int> product = { 1, 3, 3, 1 };
    EXPECT_EQ( product, p * q );
    EXPECT_EQ( product, q * p );
}

TEST( PolynomialTest, GetValue ) {
    Polynomial<int> p = {};
    EXPECT_EQ( 0, p.GetValue( 0 ) );
    EXPECT_EQ( 0, p.GetValue( 1 ) );
    EXPECT_EQ( 0, p.GetValue( 2 ) );
    
    Polynomial<int> q = { 2 };
    EXPECT_EQ( 2, q.GetValue( 0 ) );
    EXPECT_EQ( 2, q.GetValue( 1 ) );
    EXPECT_EQ( 2, q.GetValue( 2 ) );
    
    Polynomial<int> r = { 2, 3 };
    EXPECT_EQ( 2, r.GetValue( 0 ) );
    EXPECT_EQ( 5, r.GetValue( 1 ) );
    EXPECT_EQ( 8, r.GetValue( 2 ) );

    Polynomial<int> s = { 1, 0, 0, 1 };
    EXPECT_EQ( 1, s.GetValue( 0 ) );
    EXPECT_EQ( 2, s.GetValue( 1 ) );
    EXPECT_EQ( 9, s.GetValue( 2 ) );
}