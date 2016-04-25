#include <gtest/gtest.h>
#include "algo/ordered_set.h"

TEST(OrderedSetTest, SomeExample) {
    ordered_set<int> x;
    x.insert(1);
    x.insert(2);
    x.insert(4);
    x.insert(8);
    x.insert(16);

    EXPECT_EQ(5, x.size());
    x.erase(4);
    EXPECT_EQ(4, x.size());
    x.insert(4);

    EXPECT_EQ(2, *x.find_by_order(1));
    EXPECT_EQ(4, *x.find_by_order(2));
    EXPECT_EQ(16, *x.find_by_order(4));
    EXPECT_EQ(end(x), x.find_by_order(5));

    EXPECT_EQ(0, x.order_of_key(-5));
    EXPECT_EQ(0, x.order_of_key(1));
    EXPECT_EQ(2, x.order_of_key(3));
    EXPECT_EQ(2, x.order_of_key(4));
    EXPECT_EQ(5, x.order_of_key(400));
}