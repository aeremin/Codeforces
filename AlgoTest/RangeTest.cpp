#include <gtest/gtest.h>
#include "algo/Range.hpp"

TEST( RangeTest, CanIterateSomeRange )
{
    std::vector<int> expected = { 5, 6, 7, 8, 9 };
    std::vector<int> actual;
    for ( auto i : range( 5, 10 ) )
        actual.push_back( i );

    EXPECT_EQ( expected, actual );
}


TEST( RangeTest, CanIterateSomeZeroBasedRange )
{
    std::vector<int> expected = { 0, 1, 2, 3, 4 };
    std::vector<int> actual;
    for ( auto i : range( 5 ) )
        actual.push_back( i );

    EXPECT_EQ( expected, actual );
}
