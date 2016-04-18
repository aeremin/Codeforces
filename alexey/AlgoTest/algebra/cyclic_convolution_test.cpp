#include <gtest/gtest.h>
#include "algo/algebra/cyclic_convolution.h"
#include "algo/numbertheory/Residue.hpp"

TEST(CyclicConvolutionTest, WorksForDoubles) {
    std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
    std::vector<double> b = { 2.0, 3.0, -5.0, 0.0 };
    std::vector<double> expectedConvolution = { -1.0, -13.0, 7.0, 7.0 };
    auto convolution = CyclicConvolution(a, b);
    ASSERT_EQ(expectedConvolution.size(), convolution.size());
    for (auto i : range(expectedConvolution.size()))
        EXPECT_NEAR(expectedConvolution[i], convolution[i], 1e-12);
}

TEST(CyclicConvolutionTest, WorksForIntegers) {
    std::vector<int> a = { 1, 2, 3, 4 };
    std::vector<int> b = { 2, 3, -5, 0 };
    std::vector<int> expectedConvolution = { -1, -13, 7, 7 };
    auto convolution = CyclicConvolution(a, b);
    ASSERT_EQ(expectedConvolution.size(), convolution.size());
    for (auto i : range(expectedConvolution.size()))
        EXPECT_EQ(expectedConvolution[i], convolution[i]);
}

TEST(CyclicConvolutionTest, WorksForResidues) {
    using TestResidue = Residue<int, 13>;
    std::vector<TestResidue> a = { 1, 2, 3, 4 };
    std::vector<TestResidue> b = { 2, 3, 8, 0 };
    std::vector<TestResidue> expectedConvolution = { 12, 0, 7, 7 };
    auto convolution = CyclicConvolution(a, b);
    ASSERT_EQ(expectedConvolution.size(), convolution.size());
    for (auto i : range(expectedConvolution.size()))
        EXPECT_EQ(expectedConvolution[i], convolution[i]);
}

TEST(CyclicConvolutionTest, SpeedTest) {
    const int nElements = 100000;
    std::vector<double> a(nElements);
    std::vector<double> b(nElements);
    for (int i : range(nElements))
        a[i] = b[i] = i;
    auto convolution = CyclicConvolution(a, b);
}