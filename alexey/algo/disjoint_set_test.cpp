#include <gtest/gtest.h>
#include "algo/disjoint_set.h"

TEST(DisjointSetTest, EverythingDisjointOnConstruction)
{
    const int setSize = 10;
    DisjointSet ds(setSize);
    for (int i = 0; i < setSize; ++i)
        for (int j = 0; j < setSize; ++j)
            EXPECT_EQ(i == j, ds.inSameSet(i, j));
}

TEST(DisjointSetTest, WorksOnStarShape)
{
    const int setSize = 10;
    const int starCenter = 7;
    DisjointSet ds(setSize);
    for (int i = 0; i < setSize; ++i)
        ds.unionSets(starCenter, i);

    for (int i = 0; i < setSize; ++i)
        for (int j = 0; j < setSize; ++j)
            EXPECT_TRUE(ds.inSameSet(i, j));
}

TEST(DisjointSetTest, WorksOnLinearShape)
{
    const int setSize = 10;
    DisjointSet ds(setSize);
    for (int i = 1; i < setSize; ++i)
        ds.unionSets(i - 1, i);

    for (int i = 0; i < setSize; ++i)
        for (int j = 0; j < setSize; ++j)
            EXPECT_TRUE(ds.inSameSet(i, j));
}

TEST(DisjointSetTest, WorksOnTwoLinearComponentGraph)
{
    const int halfSetSize = 10;
    DisjointSet ds(2 * halfSetSize);
    for (int i = 1; i < halfSetSize; ++i)
    {
        ds.unionSets(2 * (i - 1), 2 * i);
        ds.unionSets(2 * (i - 1) + 1, 2 * i + 1);
    }

    for (int i = 0; i < halfSetSize; ++i)
        for (int j = 0; j < halfSetSize; ++j)
            EXPECT_EQ(i % 2 == j % 2, ds.inSameSet(i, j));
}
