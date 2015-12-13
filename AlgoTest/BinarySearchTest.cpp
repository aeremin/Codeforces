#include <gtest/gtest.h>
#include <numeric>
#include "algo/BinarySearch.hpp"
using namespace std;

namespace
{
    const int cDataSetSize = 100;
}

TEST(BinarySearchTest, ReturnsLastOnEmptyRange)
{
    vector<int> empty;
    auto searchRes = binarySearch(begin(empty), end(empty), [](int elt){ return true; });
    EXPECT_EQ(end(empty), searchRes);
}

TEST(BinarySearchTest, ReturnsFirstOnSingleEltRange)
{
    const int cTestElt = 15;
    vector<int> sameElt(cDataSetSize, cTestElt);
    auto searchRes = binarySearch(begin(sameElt), end(sameElt), [&](int elt){ return elt == cTestElt; });
    EXPECT_EQ(begin(sameElt), searchRes);
}

TEST(BinarySearchTest, CanFindElementInIotaArray)
{
    vector<int> iotadata(cDataSetSize);
    std::iota(begin(iotadata), end(iotadata), 0);

    srand(12);
    int eltToFind = rand() % cDataSetSize;
    auto foundIter = binarySearch(begin(iotadata), end(iotadata), [&](int elt){ return elt >= eltToFind; });
    EXPECT_EQ(*foundIter, eltToFind);
}

TEST(BinarySearchTest, CanFindElementInRandomArray)
{
    vector<int> randomdata(cDataSetSize);
    for (auto& elt : randomdata)
        elt = rand();

    std::sort(begin(randomdata), end(randomdata));

    srand(12);
    int indToFind = rand() % cDataSetSize;
    int eltToFind = randomdata[indToFind];
    auto foundIter = binarySearch(begin(randomdata), end(randomdata), [&](int elt){ return elt >= eltToFind; });
    EXPECT_GE(*foundIter, eltToFind);
    EXPECT_TRUE(foundIter == begin(randomdata) || *(foundIter - 1) < eltToFind);
}

TEST(BinarySearchTest, WorksOnConcreteExample)
{
    vector<int> concretedata = { 1, 2, 3, 3, 3, 5, 7 };
    int eltToFind = 3;
    auto foundIter = binarySearch(begin(concretedata), end(concretedata), [&](int elt){ return elt >= eltToFind; });
    EXPECT_EQ(2, foundIter - begin(concretedata));
}
