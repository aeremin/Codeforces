#include <gtest/gtest.h>
#include "algo/Heap.hpp"
#include <algorithm>

using namespace std;

TEST(HeapTest, DefaultConstructedIsEmpty)
{
    Heap<int> heap;
    EXPECT_TRUE(heap.isEmpty());
}

TEST(HeapTest, AddAndRemoveOneElement)
{
    Heap<int> heap;
    const int elt = 17;
    heap.push(elt);
    EXPECT_FALSE(heap.isEmpty());
    EXPECT_EQ(elt, heap.getMinElt());
    EXPECT_TRUE(heap.popMin());
    EXPECT_TRUE(heap.isEmpty());
}

TEST(HeapTest, IsSorted)
{
    const int nElts = 5000;
    vector<int> eltToPush(nElts);
    generate(begin(eltToPush), end(eltToPush), rand);

    Heap<int> heap;
    for (int elt : eltToPush)
        heap.push(elt);
    int prevElt = numeric_limits<int>::min();
    int totalElts = 0;
    while (!heap.isEmpty())
    {
        int elt = heap.getMinElt();
        EXPECT_TRUE(elt >= prevElt);
        prevElt = elt;
        EXPECT_TRUE(heap.popMin());
        totalElts++;
    }

    EXPECT_EQ((int)eltToPush.size(), totalElts);
}