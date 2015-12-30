#include <gtest/gtest.h>
#include "algo/GreatestCommonDivisor.hpp"

TEST( GreatestCommonDivisorTest, ConcreteExamples )
{
    EXPECT_EQ( 1, greatestCommonDivisor( 15, 8 ) );
    EXPECT_EQ( 1, greatestCommonDivisor( -15, 8 ) );
    EXPECT_EQ( 1, greatestCommonDivisor( -15, -8 ) );
    EXPECT_EQ( 1, greatestCommonDivisor( 15, -8 ) );

    EXPECT_EQ( 10, greatestCommonDivisor( 20, -110 ) );

    EXPECT_EQ( 25, greatestCommonDivisor( 25, 0 ) );
    EXPECT_EQ( 25, greatestCommonDivisor( 0, 25 ) );

    EXPECT_EQ( 2, greatestCommonDivisor( 104, 82 ) );
}

TEST( GreatestCommonDivisorTest, Decomposition )
{
    int64_t maxN = 100;
    for ( int64_t p = -maxN; p <= maxN; ++p )
    {
        for ( int64_t q = -maxN; q <= maxN; ++q )
        {
            int64_t x, y;
            auto gcd = gcdDecomposition( p, q, x, y );
            EXPECT_EQ( gcd, p * x + q * y );
            EXPECT_EQ( gcd, greatestCommonDivisor( p, q ) );
        }
    }
}