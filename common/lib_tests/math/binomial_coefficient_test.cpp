#include <gtest/gtest.h>
#include "math/binomial_coefficients.h"

TEST(BinomialCoefficientTest, ProperResultsForNEqual4)
{
    std::vector<int> expected = { 1, 4, 6, 4, 1 };
    for (size_t i = 0; i < expected.size(); ++i)
        EXPECT_EQ(expected[i], BinomialCoefficient<int>(4, int64(i))) << i;
}

TEST(BinomialCoefficientTest, SumOfBinomialCoefficientsIsPowerOfTwo)
{
    for (int64_t n = 0; n < 62; ++n)
    {
        int64_t sum = 0;
        for (int64_t k = 0; k <= n; ++k)
            sum += BinomialCoefficient<int64_t>(n, k);
        EXPECT_EQ(int64_t(1) << n, sum);
    }
}

TEST(BinomialCoefficientTest, Double)
{
    EXPECT_DOUBLE_EQ(2.7028824094543656951561469362597527549615200844e299, BinomialCoefficient<double>(1000, 500));
}
