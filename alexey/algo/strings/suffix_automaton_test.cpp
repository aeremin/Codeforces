#include <gtest/gtest.h>
#include "algo/strings/suffix_automaton.h"

TEST(SuffixAutomatonTest, Traverse) {
    SuffixAutomaton sa("abcbc");
    EXPECT_NE(-1, sa.traverse("ab"));
    EXPECT_NE(-1, sa.traverse("bc"));
    EXPECT_NE(-1, sa.traverse("bcb"));

    EXPECT_EQ(-1, sa.traverse("ba"));
    EXPECT_EQ(-1, sa.traverse("ac"));
}

TEST(SuffixAutomatonTest, IsSubstring) {
    SuffixAutomaton sa("abcbc");
    EXPECT_TRUE(sa.isSubstring("cbc"));
    EXPECT_TRUE(sa.isSubstring("abcbc"));

    EXPECT_FALSE(sa.isSubstring("bb"));
}

TEST(SuffixAutomatonTest, IsSuffix) {
    SuffixAutomaton sa("abcbc");
    EXPECT_TRUE(sa.isSuffix("bc"));
    EXPECT_FALSE(sa.isSuffix("ba"));
    EXPECT_FALSE(sa.isSuffix("cb"));
}

TEST(SuffixAutomatonTest, EncountersCount) {
    SuffixAutomaton sa("abcbcbcd");
    EXPECT_EQ(1, sa.getSize(sa.traverse("ab")));
    EXPECT_EQ(3, sa.getSize(sa.traverse("bc")));
    EXPECT_EQ(2, sa.getSize(sa.traverse("cb")));
    EXPECT_EQ(2, sa.getSize(sa.traverse("bcb")));
    EXPECT_EQ(1, sa.getSize(sa.traverse("bcd")));
    EXPECT_EQ(1, sa.getSize(sa.traverse("cd")));
}