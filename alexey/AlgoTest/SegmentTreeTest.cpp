#include <gtest/gtest.h>
#include <numeric>
#include <algorithm>
#include "algo/updatetypes/SetTo.hpp"
#include "algo/updateappliers/SetToPlus.hpp"
#include "algo/SegmentTree.hpp"

using std::vector;

class SegmentTreeTest : public testing::Test
{
protected:
    const size_t dataSize = 10;
    const int dataElt = 17;
    vector<int> data = vector<int>(dataSize, dataElt);
};

TEST_F(SegmentTreeTest, WorksOnSameElementArray)
{
    auto segmentTree = makeSegmentTree(data, std::plus<int>(), updateTypes::SetTo<int>());
    for (size_t leftOffset = 0; leftOffset < dataSize - 1; ++leftOffset)
        for (size_t rightOffset = leftOffset + 1; rightOffset < dataSize; ++rightOffset)
        {
            int expected = dataElt * (rightOffset - leftOffset);
            int calculated = segmentTree.getValueOnSegment(leftOffset, rightOffset);
            EXPECT_EQ(expected, calculated);
        }
}


TEST_F(SegmentTreeTest, WorksAfterOneUpdate)
{
    auto segmentTree = makeSegmentTree(data, std::plus<int>(), updateTypes::SetTo<int>());
    const int changedEltInd = 4;
    segmentTree.updateElement(changedEltInd, updateTypes::SetTo<int>(dataElt + 1));
    for (size_t leftOffset = 0; leftOffset < dataSize - 1; ++leftOffset)
        for (size_t rightOffset = leftOffset + 1; rightOffset < dataSize; ++rightOffset)
        {
            int expected = dataElt * (rightOffset - leftOffset) + ((leftOffset <= changedEltInd && rightOffset > changedEltInd) ? 1 : 0);
            int calculated = segmentTree.getValueOnSegment(leftOffset, rightOffset);
            EXPECT_EQ(expected, calculated) << leftOffset << " " << rightOffset;
        }
}


TEST_F(SegmentTreeTest, WorksAfterOneRangeUpdate)
{
    auto segmentTree = makeSegmentTree(data, std::plus<int>(), updateTypes::SetTo<int>());
    segmentTree.updateRange(0, 3, updateTypes::SetTo<int>(dataElt + 1));
    for (size_t leftOffset = 0; leftOffset < dataSize - 1; ++leftOffset)
        for (size_t rightOffset = leftOffset + 1; rightOffset < dataSize; ++rightOffset)
        {
            int expected = dataElt * (rightOffset - leftOffset);
            if (leftOffset < 3) expected += (std::min(size_t(3), rightOffset) - leftOffset);
            int calculated = segmentTree.getValueOnSegment(leftOffset, rightOffset);
            EXPECT_EQ(expected, calculated) << leftOffset << " " << rightOffset;
        }
}

TEST_F(SegmentTreeTest, RandomTest)
{
    const size_t bigDataSize = 10000;
    const size_t nIterations = 10000;
    data = vector<int>(bigDataSize, 0);
    auto segmentTree = makeSegmentTree(data, std::plus<int>(), updateTypes::SetTo<int>());
    for (size_t i = 0; i < nIterations; ++i)
    {
        {
            // Update
            size_t l = rand() % bigDataSize;
            size_t r = rand() % bigDataSize;
            int value = (rand() % 1000) - 500;
            std::tie(l, r) = std::minmax(l, r);

            // Update SegmentTree
            segmentTree.updateRange(l, r, updateTypes::SetTo<int>(value));
            // Update plain array
            for (size_t j = l; j < r; ++j)
                data[j] = value;
        }
        {
            // Query
            size_t l = rand() % bigDataSize;
            size_t r = rand() % bigDataSize;
            int value = (rand() % 1000) - 500;
            std::tie(l, r) = std::minmax(l, r);
            if (l == r)
                continue;

            auto expected = std::accumulate(begin(data) + l, begin(data) + r, 0);
            auto calculated = segmentTree.getValueOnSegment(l, r);
            EXPECT_EQ(expected, calculated);
        }
    }
}

