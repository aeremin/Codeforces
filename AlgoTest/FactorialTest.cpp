#include <gtest/gtest.h>
#include "algo/algebra/Factorial.hpp"
#include <vector>
#include "algo/numbertheory/Residue.hpp"

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

TEST(FactorialTest, FactorialPerModulo)
{
	typedef Residue<int, 1000> TestResidue;
	EXPECT_EQ(TestResidue(40), factorial(TestResidue(1), 7));
}