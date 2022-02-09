#include <gtest/gtest.h>
#include "algo/sliding_window_min_finder.h"
using namespace std;

TEST(SlidingWindowMinFinderTest, WorksOnConcreteExample)
{
    vector<int> data = { 2, 3, 3, 3, 1, 5, -2, 2, 7 };

    SlidingWindowMinFinder<int> minFinder(data);
    minFinder.incRight(); // 2
    minFinder.incRight(); // 2 3
    EXPECT_EQ(2, minFinder.getMin());
    minFinder.incLeft(); // 3
    EXPECT_EQ(3, minFinder.getMin());
    minFinder.incRight(); // 3 3
    EXPECT_EQ(3, minFinder.getMin());
    minFinder.incRight(); // 3 3 3
    EXPECT_EQ(3, minFinder.getMin());
    minFinder.incLeft(); // 3 3
    EXPECT_EQ(3, minFinder.getMin());
    minFinder.incLeft(); // 3
    EXPECT_EQ(3, minFinder.getMin());
    minFinder.incRight(); // 3 1 
    minFinder.incRight(); // 3 1 5
    minFinder.incLeft(); // 1 5
    EXPECT_EQ(1, minFinder.getMin());
    minFinder.incLeft(); // 5
    EXPECT_EQ(5, minFinder.getMin());
    minFinder.incRight(); // 5 -2
    minFinder.incLeft(); // -2
    EXPECT_EQ(-2, minFinder.getMin());
    minFinder.incRight(); // -2 2
    minFinder.incRight(); // -2 2 7
    EXPECT_EQ(-2, minFinder.getMin());
    minFinder.incLeft(); // 2 7
    EXPECT_EQ(2, minFinder.getMin());
    minFinder.incLeft(); // 7
    EXPECT_EQ(7, minFinder.getMin());
}
