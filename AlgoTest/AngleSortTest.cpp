#include <gtest/gtest.h>
#include "algo/geometry/AngleSort.hpp"

TEST(AngleSortTest, Sorts8MainDirections)
{
    std::vector<GeomVector2I> data = {
        {-1, 1}, {1, 1}, {0, 1}, {-1, 0}, {1, -1}, {0, -1}, {-1, -1}, {1, 0}
    };

    std::vector<GeomVector2I> angleSortedData = {
        { 1, 0 },{ 1, 1 },{ 0, 1 },{ -1, 1 },{ -1, 0 },{ -1, -1 },{ 0, -1 },{ 1, -1 }
    };

    std::vector<size_t> expectedForwardMappings = { 3, 1, 2, 4, 7, 6, 5, 0 };

    std::vector<size_t> forwardMappings;
    angleSort(data, &forwardMappings, nullptr);
    EXPECT_EQ(angleSortedData, data);
    EXPECT_EQ(expectedForwardMappings, forwardMappings);
}