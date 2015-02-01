#include "stdafx.h"
#include "CppUnitTest.h"

#include "../algo/QuickSort.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;

namespace AlgoUnitTest
{
    TEST_CLASS(QuickSortUT)
    {
    private:
        static const int cDataSetSize =  1e6;

    public:

        TEST_METHOD(SortsEmptyVector)
        {
            vector<int> empty;
            quickSort(begin(empty), end(empty));
        }

        TEST_METHOD(SortsOneEltVector)
        {
            const int elt = 27;
            vector<int> data;
            data.push_back(elt);
            quickSort(begin(data), end(data));
            Assert::AreEqual(elt, data.front());
        }

        TEST_METHOD(SortsReverseOrderedVector)
        {
            vector<int> data(cDataSetSize);
            std::iota(data.rbegin(), data.rend(), 0);
            quickSort(begin(data), end(data));
            for (auto iter = begin(data) + 1; iter != end(data); ++iter)
                Assert::IsTrue(*iter >= *(iter - 1));
        }

        TEST_METHOD(SortsOrderedVector)
        {
            vector<int> data(cDataSetSize);
            std::iota(data.begin(), data.end(), 0);
            quickSort(begin(data), end(data));
            for (auto iter = begin(data) + 1; iter != end(data); ++iter)
                Assert::IsTrue(*iter >= *(iter - 1));
        }

        TEST_METHOD(SortsSameEltVector)
        {
            const int testelt = 27;
            vector<int> data(cDataSetSize, testelt);
            quickSort(begin(data), end(data));
            for (auto iter = begin(data) + 1; iter != end(data); ++iter)
                Assert::IsTrue(*iter >= *(iter - 1));
        }

        TEST_METHOD(SortsRandomVector)
        {
            vector<int> data(cDataSetSize);
            srand(17);
            for (auto& elt : data)
                elt = rand();

            quickSort(begin(data), end(data));

            for (auto iter = begin(data) + 1; iter != end(data); ++iter)
                Assert::IsTrue(*iter >= *(iter - 1));
        }

    };
}