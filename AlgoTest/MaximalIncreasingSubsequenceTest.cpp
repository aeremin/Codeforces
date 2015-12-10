#include <gtest/gtest.h>
#include <algo/MaximaIncreasingSubsequence.hpp>

TEST(MaximalIncreasingSubsequenceTest, LengthIsZeroForEmptySequence)
{
    std::vector<int> data;
    EXPECT_EQ(0, lenOfMaximalIncreasingSubsequence(begin(data), end(data)));
}

TEST(MaximalIncreasingSubsequenceTest, IncreasingSequence)
{
    std::vector<int> data = { 1, 2, 4, 6, 12, 69 };
    EXPECT_EQ(data.size(), lenOfMaximalIncreasingSubsequence(begin(data), end(data)));
}

TEST(MaximalIncreasingSubsequenceTest, DecreasingSequence)
{
    std::vector<int> data = { 100, 13, 6, 5, -1 };
    EXPECT_EQ(1, lenOfMaximalIncreasingSubsequence(begin(data), end(data)));
}

TEST(MaximalIncreasingSubsequenceTest, SomeSpecialSequence)
{
    std::vector<double> data = {1.0, 4.0, 3.0, 2.0, 5.0, 7.0, 2.1, 2.2, 2.3};
    EXPECT_EQ(5, lenOfMaximalIncreasingSubsequence(begin(data), end(data)));
}