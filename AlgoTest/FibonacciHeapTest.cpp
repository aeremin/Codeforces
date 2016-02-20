#include <gtest/gtest.h>
#include "algo/FibonacciHeap.hpp"
#include <algorithm>

using std::vector;

namespace
{
template<typename T>
void checkIfSorted(FibonacciHeap<T>& heap)
{
    int prevElt = std::numeric_limits<T>::min();
    while (!heap.isEmpty())
    {
        auto elt = heap.getMin();
        EXPECT_GE(elt, prevElt);
        prevElt = elt;
        heap.popMin();
    }
}
}


TEST(FibonacciHeapTest, DefaultConstructedIsEmpty)
{
    FibonacciHeap<int> heap;
    EXPECT_TRUE(heap.isEmpty());
}

TEST(FibonacciHeapTest, IsSortedAfterPush)
{
    const int nElts = 100000;
    vector<int> eltToPush(nElts);
    std::generate(begin(eltToPush), end(eltToPush), rand);

    FibonacciHeap<int> heap;
    for (int elt : eltToPush)
        heap.push(elt);

    checkIfSorted(heap);
}

TEST(FibonacciHeapTest, WorksCorrectlyOnTwoElementsData)
{
    const int nActions = 10;
    FibonacciHeap<int> heap;
    int count[2] = { 0, 0 };
    for (int i = 0; i < nActions; ++i)
    {
        if (heap.isEmpty() || (rand() % 2 == 0))
        {
            int newElt = (rand() % 97 == 0) ? 0 : 1;
            count[newElt]++;
            heap.push(newElt);
        }
        else
        {
            int expectedElt = (count[0] > 0) ? 0 : 1;
            int realElt = heap.getMin();
            EXPECT_EQ(expectedElt, realElt);
            heap.popMin();
            count[expectedElt]--;
        }
    }
}

TEST(FibonacciHeapTest, IsSortedAfterPushAndDecrease)
{
    const int nElts = 100000;
    vector<int> eltToPush(nElts);
    generate(begin(eltToPush), end(eltToPush), rand);

    FibonacciHeap<int> heap;
    vector<Node<int>*> nodePtrs;
    for (int elt : eltToPush)
        nodePtrs.push_back(heap.push(elt));

    int decreaseIterations = nElts;
    for (int i = 0; i < decreaseIterations; ++i)
    {
        int indToDecrease = rand() % nElts;
        int decreaseAmount = rand() % 1000;
        int newAmount = nodePtrs[indToDecrease]->data - decreaseAmount;
        heap.decreaseValue(nodePtrs[indToDecrease], newAmount);
        EXPECT_EQ(newAmount, nodePtrs[indToDecrease]->data);
    }

    checkIfSorted(heap);
}
