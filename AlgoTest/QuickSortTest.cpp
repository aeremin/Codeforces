#include <gtest/gtest.h>
#include <numeric>
#include "algo/QuickSort.hpp"

using namespace std;
namespace
{
    static const int cDataSetSize = 100000;
}

TEST(QuickSortTest, SortsEmptyVector)
{
    vector<int> empty;
    quickSort(begin(empty), end(empty));
}

TEST(QuickSortTest, SortsOneEltVector)
{
    const int elt = 27;
    vector<int> data;
    data.push_back(elt);
    quickSort(begin(data), end(data));
    EXPECT_EQ(elt, data.front());
}

TEST(QuickSortTest, SortsReverseOrderedVector)
{
    vector<int> data(cDataSetSize);
    std::iota(data.rbegin(), data.rend(), 0);
    quickSort(begin(data), end(data));
    for (auto iter = begin(data) + 1; iter != end(data); ++iter)
        EXPECT_TRUE(*iter >= *(iter - 1));
}

TEST(QuickSortTest, SortsOrderedVector)
{
    vector<int> data(cDataSetSize);
    std::iota(data.begin(), data.end(), 0);
    quickSort(begin(data), end(data));
    for (auto iter = begin(data) + 1; iter != end(data); ++iter)
        EXPECT_TRUE(*iter >= *(iter - 1));
}

TEST(QuickSortTest, SortsSameEltVector)
{
    const int testelt = 27;
    vector<int> data(cDataSetSize, testelt);
    quickSort(begin(data), end(data));
    for (auto iter = begin(data) + 1; iter != end(data); ++iter)
        EXPECT_TRUE(*iter >= *(iter - 1));
}

TEST(QuickSortTest, SortsRandomVector)
{
    vector<int> data(cDataSetSize);
    srand(17);
    for (auto& elt : data)
        elt = rand();

    quickSort(begin(data), end(data));

    for (auto iter = begin(data) + 1; iter != end(data); ++iter)
        EXPECT_TRUE(*iter >= *(iter - 1));
}
