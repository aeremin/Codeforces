#include <gtest/gtest.h>
#include "algo/strings/KnuttMorrisPratt.hpp"

using namespace std;


namespace
{
string multipliedString(int len, string c)
{
    string res = "";
    for (int i = 0; i < len; ++i)
    {
        res += c;
    }
    return res;
}
}

TEST(KnuttMorrisPrattTest, EmptyString)
{
    auto res = calc_prefix_function("");
    EXPECT_TRUE(res.empty());
}

TEST(KnuttMorrisPrattTest, HasProperSize)
{
    int cLength = 100;
    auto res = calc_prefix_function(multipliedString(cLength, "%"));
    EXPECT_EQ(cLength, (int)res.size());
}

TEST(KnuttMorrisPrattTest, SameCharString)
{
    int cLength = 200;
    auto res = calc_prefix_function(multipliedString(cLength, "$"));
    for (int i = 0; i < res.size(); ++i)
    {
        EXPECT_EQ(i, res[i]);
    }
}

TEST(KnuttMorrisPrattTest, AlternatingCharString)
{
    int cHalfLength = 400;
    auto evenString = multipliedString(cHalfLength, "12");
    auto res = calc_prefix_function(evenString);
    for (int i = 0; i < evenString.length(); ++i)
    {
        EXPECT_EQ(max(i - 1, 0), res[i]);
    }
}

TEST(KnuttMorrisPrattTest, ConcreteString_abcabcd)
{
    auto res = calc_prefix_function("abcabcd");
    vector<int> correctres = { 0, 0, 0, 1, 2, 3, 0 };
    for (int i = 0; i < res.size(); ++i)
    {
        EXPECT_EQ(correctres[i], res[i]);
    }
}

    