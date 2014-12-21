#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <numeric>

#include "../algo/MergeSort.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;

namespace AlgoUnitTest
{
	TEST_CLASS(MergeSortUT)
	{
    private:
        static const int cDataSetSize = 1e4;

    public:
		
        TEST_METHOD(SortsEmptyVector)
        {
            vector<int> empty;
            mergeSort(begin(empty), end(empty));
        }

        TEST_METHOD(SortsOneEltVector)
        {
            const int elt = 27;
            vector<int> data;
            data.push_back(elt);
            mergeSort(begin(data), end(data));
            Assert::AreEqual(elt, data.front());
        }

        TEST_METHOD(SortsReverseOrderedVector)
        {
            vector<int> data(cDataSetSize);
            std::iota(data.rbegin(), data.rend(), 0);
            mergeSort(begin(data), end(data));
            for (auto iter = begin(data); iter != end(data); ++iter)
                Assert::AreEqual(iter - begin(data), *iter);
        }

        TEST_METHOD(SortsOrderedVector)
        {
            vector<int> data(cDataSetSize);
            std::iota(data.begin(), data.end(), 0);
            mergeSort(begin(data), end(data));
            for (auto iter = begin(data); iter != end(data); ++iter)
                Assert::AreEqual(iter - begin(data), *iter);
        }

        TEST_METHOD(SortsSameEltVector)
        {
            const int testelt = 27;
            vector<int> data(cDataSetSize, testelt);
            mergeSort(begin(data), end(data));
            for (auto elt : data)
                Assert::AreEqual(testelt, elt);

        }
        
        TEST_METHOD(SortsRandomVector)
		{
            vector<int> data(cDataSetSize);
            srand(17);
            for (auto& elt : data)
                elt = rand();

            mergeSort(begin(data), end(data));

            for (auto iter = begin(data) + 1; iter != end(data); ++iter)
                Assert::IsTrue(*iter >= *(iter - 1));
		}

	};
}