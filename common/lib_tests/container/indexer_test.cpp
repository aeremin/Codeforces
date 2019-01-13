#include "container/indexer.h"

#include <gtest/gtest.h>


TEST(IndexerTest, Basic) {
    Indexer<std::string> indexer;
    EXPECT_FALSE(indexer.has_value("zero"));
    indexer.insert("zero");
    EXPECT_TRUE(indexer.has_value("zero"));
    EXPECT_EQ(0, indexer.index("zero"));
    EXPECT_EQ("zero", indexer.value(0));
    indexer.insert("one");
    indexer.insert_new("two");
    EXPECT_EQ(3, indexer.size());
    EXPECT_EQ(1, indexer.index("one"));
    EXPECT_EQ("two", indexer.value(2));
    EXPECT_FALSE(indexer.has_value("googol"));
}

TEST(IndexerDeathTest, Insert) {
    Indexer<int> indexer;
    ASSERT_EQ(std::make_pair(0, true), indexer.insert(5));
    ASSERT_EQ(std::make_pair(1, true), indexer.insert(6));
    ASSERT_EQ(std::make_pair(2, true), indexer.insert(7));
    ASSERT_EQ(std::make_pair(2, false), indexer.insert(7));
}

TEST(IndexerDeathTest, InsertNew) {
    Indexer<int> indexer;
    ASSERT_EQ(0, indexer.insert_new(10));
    ASSERT_EQ(1, indexer.insert_new(11));
    ASSERT_EQ(2, indexer.insert_new(12));
    ASSERT_EQ(3, indexer.insert_new(13));
    ASSERT_DEATH(indexer.insert_new(13), ".*");
}
