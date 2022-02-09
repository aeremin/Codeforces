#include <gtest/gtest.h>

#include "algo/bits/full_binary_trie.h"

TEST(FullBinaryTreeTest, SomeTest)
{
    FullBinaryTrie<16> trie;
    trie.insert(10);
    trie.insert(16);
    EXPECT_TRUE(trie.has(10));
    EXPECT_TRUE(trie.has(16));
    EXPECT_FALSE(trie.has(11));
    trie.erase(10);
    EXPECT_FALSE(trie.has(10));
}

TEST(FullBinaryTreeTest, CanFindMaximumByTraversing)
{
    FullBinaryTrie<16> trie;
    trie.insert(10);
    trie.insert(200);
    trie.insert(221);
    trie.insert(15);
    trie.insert(201);
    trie.insert(16);
    trie.erase(221);

    auto maxTraversor = [&](bool has0, bool has1) -> std::pair<bool, int>
    {
        int child = has1 ? 1 : 0;
        return{ true, child };
    };

    auto traverseResult = trie.traverse(maxTraversor);

    EXPECT_TRUE(traverseResult.first);
    EXPECT_EQ(201, traverseResult.second);
}