#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>

#include "../algo/Heap.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;
using std::generate;
using std::numeric_limits;
using std::rand;

namespace AlgoUnitTest
{
	TEST_CLASS(HeapUT)
	{
	public:
		
		TEST_METHOD(DefaultConstructedIsEmpty)
		{
            Heap<int> heap;
            Assert::IsTrue(heap.isEmpty());
		}

        TEST_METHOD(AddAndRemoveOneElement)
        {
            Heap<int> heap;
            const int elt = 17;
            heap.push(elt);
            Assert::IsFalse(heap.isEmpty());
            Assert::AreEqual(elt, heap.getMinElt());
            Assert::IsTrue(heap.popMin());
            Assert::IsTrue(heap.isEmpty());
        }

        TEST_METHOD(IsSorted)
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
                Assert::IsTrue(elt >= prevElt);
                prevElt = elt;
                Assert::IsTrue(heap.popMin());
                totalElts++;
            }

            Assert::AreEqual((int) eltToPush.size(), totalElts);
        }

	};
}