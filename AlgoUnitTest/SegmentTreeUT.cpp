#include "stdafx.h"
#include "CppUnitTest.h"
#include "../algo/SegmentTree.hpp"

using std::vector;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(SegmentTreeUT)
	{
	public:
		
		TEST_METHOD(WorksOnSameElementArray)
		{
            const int dataSize = 10;
            const int dataElt = 17;
            vector<int> data(dataSize);
            for (auto& elt : data)
                elt = dataElt;

            auto sumFunctor = [](int a, int b) -> int {return a + b; };
            SegmentTree<decltype(begin(data)), decltype(sumFunctor)> segmentTree(begin(data), end(data), sumFunctor);
            
            for (size_t leftOffset = 0; leftOffset < dataSize - 1; ++leftOffset)
                for (size_t rightOffset = leftOffset + 1; rightOffset < dataSize; ++rightOffset)
                {
                    int expected = dataElt * (rightOffset - leftOffset);
                    int calculated = segmentTree.getValueOnSegment(begin(data) + leftOffset, begin(data) + rightOffset);
                    Assert::AreEqual(expected, calculated);
                }
		}
           

        TEST_METHOD(WorksAfterOneUpdate)
        {
            const int dataSize = 10;
            const int changedEltInd = 4;
            const int dataElt = 17;
            vector<int> data(dataSize);
            for (auto& elt : data)
                elt = dataElt;
            auto sumFunctor = [](int a, int b) -> int {return a + b; };
            SegmentTree<decltype(begin(data)), decltype(sumFunctor)> segmentTree(begin(data), end(data), sumFunctor);

            data[changedEltInd]++;
            segmentTree.update(begin(data) + changedEltInd);
            for (size_t leftOffset = 0; leftOffset < dataSize - 1; ++leftOffset)
                for (size_t rightOffset = leftOffset + 1; rightOffset < dataSize; ++rightOffset)
                {
                    int expected = dataElt * (rightOffset - leftOffset) + ((leftOffset <= changedEltInd && rightOffset > changedEltInd) ? 1 : 0);
                    int calculated = segmentTree.getValueOnSegment(begin(data) + leftOffset, begin(data) + rightOffset);
                    Assert::AreEqual(expected, calculated);
                }
        }

	};
}