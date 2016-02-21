#include <gmock/gmock.h>
#include "iter/range.h"

using namespace testing;

TEST( RangeTest, CanIterateSomeRange )
{
    std::vector<int> actual;
    for ( auto i : range( 5, 10 ) )
        actual.push_back( i );

    EXPECT_THAT( actual, ElementsAre( 5, 6, 7, 8, 9 ) );
}


TEST( RangeTest, CanIterateSomeZeroBasedRange )
{
    std::vector<int> actual;
    for ( auto i : range( 5 ) )
        actual.push_back( i );

    EXPECT_THAT( actual, ElementsAre( 0, 1, 2, 3, 4 ) );
}


TEST( RangeTest, InversedRange )
{
    for ( auto i : range( 10, 5 ) ) {
        (void)i;
        FAIL();
    }
}
