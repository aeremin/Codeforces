#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include "algo/strings/find_occurences.h"

using std::string;
using std::vector;
using namespace testing;

TEST( FindOccurencesTest, SomeStringExample ) {
    string text = "abcaab";
    string pattern = "ab";
    auto occurences = FindOccurences( text, pattern );
    EXPECT_THAT( occurences, ElementsAre( 0, 4 ) );
}

TEST( FindOccurencesTest, WorksForEmptyPattern ) {
    string text = "abcaab";
    string pattern = "";
    auto occurences = FindOccurences( text, pattern );
    EXPECT_THAT( occurences, ElementsAre( 0, 1, 2, 3, 4, 5 ) );
}