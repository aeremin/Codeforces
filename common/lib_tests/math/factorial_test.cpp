#include <gtest/gtest.h>
#include "math/factorial.h"
#include <vector>

TEST(FactorialTest, FactorialOfZeroIsOne)
{
    EXPECT_EQ(1, factorial(1, 0));
}

TEST(FactorialTest, FactorialsOfFistIntsAreCorrect)
{
    std::vector<int> expected = { 1, 1, 2, 6, 24, 120, 720, 5040 };
    for (size_t i = 0; i < expected.size(); ++i)
        EXPECT_EQ(expected[i], factorial(1, i));
}
