#include <gtest/gtest.h>
#include "algo/borrower.h"
#include <set>
#include <unordered_set>

TEST( BorrowerTest, MultiSet )
{
    std::multiset<int> s = { 1, 2, 3, 3, 4 };
    {
        auto b1 = make_borrower( s, begin( s ) );
        std::multiset<int> expected1 = { 2, 3, 3, 4 };
        EXPECT_EQ( expected1, s );
        {
            auto b2 = make_borrower( s, 3 );
            std::multiset<int> expected2 = { 2, 3, 4 };
            EXPECT_EQ( expected2, s );
        }
        EXPECT_EQ( expected1, s );
    }
    std::multiset<int> expected = { 1, 2, 3, 3, 4 };
    EXPECT_EQ( expected, s );
}

TEST( BorrowerTest, UnorderedMultiSet )
{
    std::unordered_multiset<int> s = { 1, 2, 3, 3, 4 };
    {
        auto b1 = make_borrower( s, s.find(1));
        std::unordered_multiset<int> expected1 = { 2, 3, 3, 4 };
        EXPECT_EQ( expected1, s );
        {
            auto b2 = make_borrower( s, 3 );
            std::unordered_multiset<int> expected2 = { 2, 3, 4 };
            EXPECT_EQ( expected2, s );
        }
        EXPECT_EQ( expected1, s );
    }
    std::unordered_multiset<int> expected = { 1, 2, 3, 3, 4 };
    EXPECT_EQ( expected, s );
}