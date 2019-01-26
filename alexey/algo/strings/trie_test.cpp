#include <gtest/gtest.h>
#include "algo/strings/trie.h"

TEST(TrieTest, OneWordTrie) {
    Trie tr;
    auto i1 = tr.AddWord("buzz");
    EXPECT_EQ(Trie::InvalidIndex, tr.traverse(0, 'a'));
    EXPECT_NE(Trie::InvalidIndex, tr.traverse(0, 'b'));
    EXPECT_EQ(i1,
              tr.traverse(
              tr.traverse(
              tr.traverse(
              tr.traverse(0, 'b'), 'u'), 'z'), 'z'));
}