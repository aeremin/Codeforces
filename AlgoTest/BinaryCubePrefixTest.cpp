#include <gtest/gtest.h>
#include "algo/BinaryCubePrefix.h"

TEST(BinaryCubePrefixTest, ProperlyCalculatesPrefixSums)
{
    // v(0, 0) = 1    v(1, 0) = 100
    // v(0, 1) = 10   v(1, 1) = 1000
    std::array<int, 4> values = { 1, 10, 100, 1000 };

    auto prefixSums = calculatePrefixSums<int, 2>(values);

    // Expected prefix sums:
    // s(0, 0) = 1    s(1, 0) = 101
    // s(0, 1) = 11   s(1, 1) = 1111
    std::array<int, 4> expectedSums = { 1, 11, 101, 1111 };
    EXPECT_EQ(expectedSums, prefixSums);
}

TEST(BinaryCubePrefixTest, CanRestoreValuesByP)
{
    std::array<int, 1024> values;
    for (auto& elt : values)
        elt = rand() % 10000;

    auto prefixSums = calculatePrefixSums<int, 10>(values);
    auto valuesRestored = calculateValuesByPrefixSums<int, 10>(prefixSums);
    EXPECT_EQ(values, valuesRestored);
}
