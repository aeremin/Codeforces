#include <gtest/gtest.h>
#include "algo/number_theory/big_integer.h"

TEST(BigIntegerTest, CanConstruct) {
    BigInteger a = 123;
    EXPECT_EQ(3, a.at(0));
    EXPECT_EQ(2, a.at(1));
    EXPECT_EQ(1, a.at(2));
    EXPECT_EQ(0, a.at(3));
    EXPECT_EQ(3, a.len());
}

TEST(BigIntegerTest, Product) {
    uint64_t a = 164757346740;
    uint64_t b = 40195;
    EXPECT_EQ(BigInteger(a) * BigInteger(b), BigInteger(a * b));
}

TEST(BigIntegerTest, CopyConstructible) {
    BigInteger a = 164757346740;
    BigInteger b = a;
    EXPECT_EQ(a, b);
}

TEST(BigIntegerTest, SumOfDigits) {
    BigInteger a = 1234567890;
    EXPECT_EQ(45, a.DigitsSum());
}