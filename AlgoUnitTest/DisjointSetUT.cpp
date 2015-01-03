#include "stdafx.h"
#include "CppUnitTest.h"

#include "../algo/DisjointSet.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(DisjointSetUT)
	{
	public:
		
		TEST_METHOD(EverythingDisjointOnConstruction)
		{
            const int setSize = 10;
            DisjointSet ds(setSize);
            for (int i = 0; i < setSize; ++i)
                for (int j = 0; j < setSize; ++j)
                    Assert::AreEqual(i == j, ds.inSameSet(i, j));
		}
        
        TEST_METHOD(WorksOnStarShape)
        {
            const int setSize = 10;
            const int starCenter = 7;
            DisjointSet ds(setSize);
            for (int i = 0; i < setSize; ++i)
                ds.unionSets(starCenter, i);

            for (int i = 0; i < setSize; ++i)
                for (int j = 0; j < setSize; ++j)
                    Assert::IsTrue(ds.inSameSet(i, j));
        }

        TEST_METHOD(WorksOnLinearShape)
        {
            const int setSize = 10;
            DisjointSet ds(setSize);
            for (int i = 1; i < setSize; ++i)
                ds.unionSets(i - 1, i);

            for (int i = 0; i < setSize; ++i)
                for (int j = 0; j < setSize; ++j)
                    Assert::IsTrue(ds.inSameSet(i, j));
        }

        TEST_METHOD(WorksOnTwoLinearComponentGraph)
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
                    Assert::AreEqual(i % 2 == j % 2, ds.inSameSet(i, j));
        }
	};
}