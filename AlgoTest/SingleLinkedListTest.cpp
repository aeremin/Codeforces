#include <gtest/gtest.h>
#include "algo/SingleLinkedList.hpp"
#include <algorithm>

using namespace std;

TEST(SingleLinkedListTest, DefaultConstructedIsEmpty)
{
    SingleLinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
}

TEST(SingleLinkedListTest, AfterInsertNotEmpty)
{
    SingleLinkedList<int> list;
    list.insert(1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(SingleLinkedListTest, InsertsInBeginning)
{
    SingleLinkedList<int> list;
    vector<int> a = { 1, 2, 5, -3 };
    for (auto elt : a)
        list.insert(elt);

    int checkInd = a.size() - 1;
    list.forEach([&](int elt)
    {
        EXPECT_EQ(a[checkInd], elt);
        checkInd--;
    });

}

TEST(SingleLinkedListTest, ReversesEmpty)
{
    SingleLinkedList<int> list;
    list.reverse();
    EXPECT_TRUE(list.isEmpty());
}

TEST(SingleLinkedListTest, ReversesSingleElt)
{
    SingleLinkedList<int> list;
    const int testElt = 17;
    list.insert(testElt);
    list.reverse();
    int totalElts = 0;
    list.forEach([&](int elt)
    {
        totalElts++;
        EXPECT_EQ(testElt, elt);
    });
    EXPECT_EQ(1, totalElts);
}

TEST(SingleLinkedListTest, ReversesConcreteList12345)
{
    vector<int> toInsert = { 1, 2, 3, 4, 5 };
    SingleLinkedList<int> list;
    for (auto elt : toInsert)
        list.insert(elt);

    vector<int> orderBefore;
    list.forEach([&](int elt){ orderBefore.push_back(elt); });

    list.reverse();

    vector<int> orderAfter;
    list.forEach([&](int elt){ orderAfter.push_back(elt); });

    int size = orderBefore.size();
    EXPECT_EQ(size, (int)orderAfter.size());
    for (int i = 0; i < size; ++i)
    {
        EXPECT_EQ(orderBefore[i], orderAfter[size - i - 1]);
    }

}

TEST(SingleLinkedListTest, InsertAndDeleteOneElement)
{
    SingleLinkedList<int> list;
    auto node = list.insert(17);
    list.deleteNode(node);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SingleLinkedListTest, InsertThenDeleteInRandomOrder)
{
    SingleLinkedList<int> list;
    vector<int> eltsToInsert = { 1, 2, 3, -1, 0, 176, 95 };
    vector<SingleLinkedList<int>::NodePtr> nodePtrs;
    for (auto elt : eltsToInsert)
        nodePtrs.push_back(list.insert(elt));

    random_shuffle(begin(nodePtrs), end(nodePtrs));

    for (auto nodePtr : nodePtrs)
        EXPECT_TRUE(list.deleteNode(nodePtr));

    EXPECT_TRUE(list.isEmpty());
}
