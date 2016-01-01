#include <gtest/gtest.h>
#include "algo/Primes.hpp"

namespace
{
const uint64_t cSomeRelativelyBigPrime = 867701;
}

TEST( PrimesTest, IsPrime )
{
    EXPECT_TRUE( isPrime( 2 ) );
    EXPECT_TRUE( isPrime( 3 ) );
    EXPECT_TRUE( isPrime( 5 ) );
    EXPECT_TRUE( isPrime( 7 ) );
    EXPECT_TRUE( isPrime( 2011 ) );
    EXPECT_TRUE( isPrime( cSomeRelativelyBigPrime ) );

    EXPECT_FALSE( isPrime( 1 ) );
    EXPECT_FALSE( isPrime( 4 ) );
    EXPECT_FALSE( isPrime( 15 ) );
    EXPECT_FALSE( isPrime( cSomeRelativelyBigPrime * cSomeRelativelyBigPrime ) );
    EXPECT_FALSE( isPrime( cSomeRelativelyBigPrime * cSomeRelativelyBigPrime - 1) );
}

TEST( PrimesTest, GeneratePrimesUntil30 )
{
    auto primesUpTo30Calculated = generatePrimesUntil( 30 );
    std::vector<uint64_t> primesUpTo30Expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    EXPECT_EQ( primesUpTo30Expected, primesUpTo30Calculated );
}

// Test to check computation speed
TEST( PrimesTest, GeneratePrimesUntilMillion )
{
    auto primesUpToMillion = generatePrimesUntil( 1000000 );
    EXPECT_EQ( 78498, primesUpToMillion.size() ); // Exact number from the web
}

TEST(PrimesTest, DecomposeToPrimePowers)
{
    auto res = decomposeToPrimePowers(32 * 19 * 19 * cSomeRelativelyBigPrime);
    EXPECT_EQ(3, res.size());
    auto p1 = std::pair<uint64_t, uint64_t>(2, 5);                        EXPECT_EQ(p1, res[0]);
    auto p2 = std::pair<uint64_t, uint64_t>(19, 2);                       EXPECT_EQ(p2, res[1]);
    auto p3 = std::pair<uint64_t, uint64_t>(cSomeRelativelyBigPrime, 1);  EXPECT_EQ(p3, res[2]);
}