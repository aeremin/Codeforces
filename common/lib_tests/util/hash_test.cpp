#include "util/hash.h"

#include <string>

#include <gtest/gtest.h>

#include "util/mixed_hash.h"


struct MyStruct {
    int x;
    std::string s;

    bool operator==(const MyStruct& other) const { return x == other.x && s == other.s; }
};

DEFINE_HASH_2(MyStruct, x, s)


TEST(HashTest, HashSet) {
    hash_set<int> a;
    a.insert(10);
    EXPECT_FALSE(a.find(10) == a.end());
    EXPECT_TRUE(a.find(11) == a.end());
}

TEST(HashTest, HashMap) {
    hash_map<int, int> a;
    a.insert({10, 20});
    EXPECT_FALSE(a.find(10) == a.end());
    EXPECT_EQ(a.find(10)->second, 20);
    EXPECT_TRUE(a.find(11) == a.end());
}

TEST(HashTest, HashSetWithCustomType) {
    hash_set<MyStruct> a;
    a.insert({10, "ten"});
}
