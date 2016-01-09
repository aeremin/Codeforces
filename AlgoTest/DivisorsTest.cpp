#include <gtest/gtest.h>
#include "algo/numbertheory/Divisors.hpp"

TEST(DivisorsTest, DivisorsOfOne)
{
    auto divisors = getDivisorsOf(1);
    EXPECT_EQ(std::vector<int64_t>({ 1 }), divisors);
}

TEST(DivisorsTest, DivisorsOfPrime)
{
    auto divisors = getDivisorsOf(17);
    EXPECT_EQ(std::vector<int64_t>({ 1, 17 }), divisors);
}

TEST(DivisorsTest, DivisorsOfNonPrime)
{
    auto divisors = getDivisorsOf(12);
    EXPECT_EQ(std::vector<int64_t>({ 1, 2, 3, 4, 6, 12 }), divisors);
}

TEST(DivisorsTest, DivisorsOfPerfectSquare)
{
    auto divisors = getDivisorsOf(36);
    EXPECT_EQ(std::vector<int64_t>({ 1, 2, 3, 4, 6, 9, 12, 18, 36 }), divisors);
}