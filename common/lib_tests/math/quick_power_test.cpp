#include <gtest/gtest.h>
#include "math/quick_power.h"


TEST(QuickPowerTest, ZeroPower)
{
    for (int i = 1; i < 10; ++i)
    {
        EXPECT_EQ(1, quick_power(i, 0));
        EXPECT_DOUBLE_EQ(1.0, quick_power(double(i), 0));
    }
}

TEST(QuickPowerTest, FirstPower)
{
    for (int i = 1; i < 10; ++i)
    {
        EXPECT_EQ(i, quick_power(i, 1));
        EXPECT_DOUBLE_EQ(double(i), quick_power(double(i), 1));
    }
}

TEST(QuickPowerTest, SameAsSlowForConcreteA)
{
    double a = 3.5;
    double a_powered = 1.0;
    for (int d = 0; d < 10; ++d)
    {
        EXPECT_EQ(a_powered, quick_power(a, d));
        a_powered *= a;
    }
}
