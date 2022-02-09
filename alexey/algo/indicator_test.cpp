#include <gtest/gtest.h>
#include "algo/indicator.h"

TEST(IndicatorTest, ReturnsOneForTrue)
{
    EXPECT_EQ(1, indicator<int>(true));
}

TEST(IndicatorTest, ReturnsZeroForFalse)
{
    EXPECT_EQ(0, indicator<int>(false));
}