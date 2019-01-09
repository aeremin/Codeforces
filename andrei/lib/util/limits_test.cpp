#include "util/limits.h"

#include <gmock/gmock.h>


TEST(LimitsTest, LowestValue) {
  {
    int x = limit_lowest();
    EXPECT_EQ(x, -2147483648);
  }
  {
    unsigned int x = limit_lowest();
    EXPECT_EQ(x, 0u);
  }
  {
    double x = limit_lowest();
    EXPECT_DOUBLE_EQ(x, -1.7976931348623157e+308);
  }
}

TEST(LimitsTest, MaxValue) {
  {
    int x = limit_max();
    EXPECT_EQ(x, 2147483647);
  }
  {
    unsigned int x = limit_max();
    EXPECT_EQ(x, 4294967295u);
  }
  {
    double x = limit_max();
    EXPECT_DOUBLE_EQ(x, 1.7976931348623157e+308);
  }
}
