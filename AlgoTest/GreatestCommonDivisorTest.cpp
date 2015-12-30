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