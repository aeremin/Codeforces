#include <gtest/gtest.h>
#include "algo/functor_iterator.h"
#include <algorithm>

namespace
{
auto squareFunctor = [](int a) { return a * a; };
}

TEST(FunctorIteratorTest, CanDereference)
{
    auto iter = makeFunctorIterator(5, squareFunctor);
    EXPECT_EQ(25, *iter);
}

TEST(FunctorIteratorTest, CanIncrement)
{
    auto iter = makeFunctorIterator(5, squareFunctor);
    ++iter;
    EXPECT_EQ(36, *iter);
}

TEST(FunctorIteratorTest, CanDecrement)
{
    auto iter = makeFunctorIterator(5, squareFunctor);
    --iter;
    EXPECT_EQ(16, *iter);
}

TEST(FunctorIteratorTest, CanUseWithLowerBound)
{
    auto l = makeFunctorIterator(0, squareFunctor);
    auto r = makeFunctorIterator(1000, squareFunctor);
    auto squareRootIterExact = std::lower_bound(l, r, 144);
    EXPECT_EQ(12, squareRootIterExact.getParameter());

    auto squareRootIterNotExact = std::lower_bound(l, r, 170);
    EXPECT_EQ(14, squareRootIterNotExact.getParameter());
}