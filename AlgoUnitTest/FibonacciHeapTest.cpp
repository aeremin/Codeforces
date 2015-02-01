#include "stdafx.h"
#include "CppUnitTest.h"
#include "../algo/FibonacciHeap.hpp"
#include <limits>
#include <iostream>

using std::vector;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(FibonacciHeapTest)
	{
	public:
		
		TEST_METHOD(DefaultConstructedIsEmpty)
		{
            FibonacciHeap<int> heap;
            Assert::IsTrue(heap.isEmpty());
		}
        
        TEST_METHOD(IsSortedAfterPush)
        {
            const int nElts = 100000;
            vector<int> eltToPush(nElts);
            generate(begin(eltToPush), end(eltToPush), rand);

            FibonacciHeap<int> heap;
            for (int elt : eltToPush)
                heap.push(elt);

            checkIfSorted_(heap);
        }

        TEST_METHOD(WorksCorrectlyOnTwoElementsData)
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
                    Assert::AreEqual(expectedElt, realElt);
                    heap.popMin();
                    count[expectedElt]--;
                }
            }
        }

        TEST_METHOD(IsSortedAfterPushAndDecrease)
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
                Assert::AreEqual(newAmount, nodePtrs[indToDecrease]->data);
            }

            checkIfSorted_(heap);
        }

    private:
        template<typename T>
        void checkIfSorted_(FibonacciHeap<T>& heap)
        {
            int prevElt = std::numeric_limits<T>::min();
            while (!heap.isEmpty())
            {
                auto elt = heap.getMin();
                Assert::IsTrue(elt >= prevElt);
                prevElt = elt;
                heap.popMin();
            }
        }
	};
}