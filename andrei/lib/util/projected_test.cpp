#include "util/projected.h"

#include <algorithm>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>


using testing::ElementsAre;

TEST(ProjectedTest, NoComparator) {
    std::vector<int> v = {10, 30, 24, 90, 77, 54};
    std::sort(v.begin(), v.end(), projected([](int a) { return a / 10; }));
    EXPECT_THAT(v, ElementsAre(10, 24, 30, 54, 77, 90));
}

TEST(ProjectedTest, WithComparator) {
    std::vector<int> v = {10, 30, 24, 90, 77, 54};
    std::sort(v.begin(), v.end(), projected([](int a) { return a / 10; },
                                            [](int a, int b) { return a > b; }));
    EXPECT_THAT(v, ElementsAre(90, 77, 54, 30, 24, 10));
}

TEST(ProjectedTest, OtherType) {
    std::vector<std::string> v = {"aaa", "b", "ccccc", "dd"};
    std::sort(v.begin(), v.end(), projected([](const std::string& s) { return s.size(); }));
    EXPECT_THAT(v, ElementsAre("b", "dd", "aaa", "ccccc"));
}
