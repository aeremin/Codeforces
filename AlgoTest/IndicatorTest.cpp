#include <gtest/gtest.h>
#include "algo/Indicator.hpp"

TEST(IndicatorTest, ReturnsOneForTrue)
{
    EXPECT_EQ(1, indicator<int>(true));
}

TEST(IndicatorTest, ReturnsZeroForFalse)
{
    EXPECT_EQ(0, indicator<int>(false));
}