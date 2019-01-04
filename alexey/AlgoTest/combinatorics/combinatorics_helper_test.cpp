#pragma once
#include <gtest/gtest.h>
#include "algo/combinatorics/combinatorics_helper.h"

class CombinatoricsHelperTest : public testing::Test
{
protected:
    using Helper = CombinatoricsHelper<int64_t, 11>;
    using Z11FieldElement = Helper::ValueType;
    Helper helper{ 4 };
};

TEST_F(CombinatoricsHelperTest, Factorial)
{
    EXPECT_EQ(helper.factorial(0), Z11FieldElement(1));
    EXPECT_EQ(helper.factorial(1), Z11FieldElement(1));
    EXPECT_EQ(helper.factorial(2), Z11FieldElement(2));
    EXPECT_EQ(helper.factorial(3), Z11FieldElement(6));
    EXPECT_EQ(helper.factorial(4), Z11FieldElement(2)); // 24 == 2 mod 11
}

TEST_F(CombinatoricsHelperTest, InvertedFactorial)
{
    EXPECT_EQ(helper.inverted_factorial(0), Z11FieldElement(1));
    EXPECT_EQ(helper.inverted_factorial(1), Z11FieldElement(1));
    EXPECT_EQ(helper.inverted_factorial(2), Z11FieldElement(6)); //  2 * 6 == 1 mod 11
    EXPECT_EQ(helper.inverted_factorial(3), Z11FieldElement(2)); //  6 * 2 == 1 mod 11
    EXPECT_EQ(helper.inverted_factorial(4), Z11FieldElement(6)); // 24 * 6 == 2 * 6 == 1 mod 11
}

TEST_F(CombinatoricsHelperTest, BinomialCoefficients)
{
    EXPECT_EQ(helper.binomial_coefficient(4, -1), Z11FieldElement(0));
    EXPECT_EQ(helper.binomial_coefficient(4, 0), Z11FieldElement(1));
    EXPECT_EQ(helper.binomial_coefficient(4, 1), Z11FieldElement(4));
    EXPECT_EQ(helper.binomial_coefficient(4, 2), Z11FieldElement(6));
    EXPECT_EQ(helper.binomial_coefficient(4, 3), Z11FieldElement(4));
    EXPECT_EQ(helper.binomial_coefficient(4, 4), Z11FieldElement(1));
    EXPECT_EQ(helper.binomial_coefficient(4, 5), Z11FieldElement(0));
}
