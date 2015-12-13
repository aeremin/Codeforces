#include <gtest/gtest.h>
#include <numeric>
#include "algo/MergeSort.hpp"

using namespace std;

namespace
{
static const int cDataSetSize = 10000;
}

TEST(MergeSortTest, SortsEmptyVector)
{
    vector<int> empty;
    mergeSort(begin(empty), end(empty));
}

TEST(MergeSortTest, SortsOneEltVector)
{
    const int elt = 27;
    vector<int> data;
    data.push_back(elt);
    mergeSort(begin(data), end(data));
    EXPECT_EQ(elt, data.front());
}

TEST(MergeSortTest, SortsReverseOrderedVector)
{
    vector<int> data(cDataSetSize);
    std::iota(data.rbegin(), data.rend(), 0);
    mergeSort(begin(data), end(data));
    for (auto iter = begin(data); iter != end(data); ++iter)
        EXPECT_EQ(iter - begin(data), *iter);
}

TEST(MergeSortTest, SortsOrderedVector)
{
    vector<int> data(cDataSetSize);
    std::iota(data.begin(), data.end(), 0);
    mergeSort(begin(data), end(data));
    for (auto iter = begin(data); iter != end(data); ++iter)
        EXPECT_EQ(iter - begin(data), *iter);
}

TEST(MergeSortTest, SortsSameEltVector)
{
    const int testelt = 27;
    vector<int> data(cDataSetSize, testelt);
    mergeSort(begin(data), end(data));
    for (auto elt : data)
        EXPECT_EQ(testelt, elt);

}

TEST(MergeSortTest, SortsRandomVector)
{
    vector<int> data(cDataSetSize);
    srand(17);
    for (auto& elt : data)
        elt = rand();

    mergeSort(begin(data), end(data));

    for (auto iter = begin(data) + 1; iter != end(data); ++iter)
        EXPECT_TRUE(*iter >= *(iter - 1));
}
