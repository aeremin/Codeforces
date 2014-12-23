#include "stdafx.h"
#include "CppUnitTest.h"
#include "GraphHelper.h"
#include "../algo/DepthFirstSearch.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(HasCycleUT)
	{
	public:
		
		TEST_METHOD(WorksOnLinearGraph)
		{
            const int nVertices = 10;
            Graph g = GraphHelper::createLinearGraph(nVertices);
            Assert::IsFalse(hasCycle(g));
		}

        TEST_METHOD(WorksOnSimpleCycle)
        {
            const int nVertices = 10;
            Graph g = GraphHelper::createSimpleCycleGraph(nVertices);
            vector<int> cycle;
            Assert::IsTrue(hasCycle(g, &cycle));           
            Assert::AreEqual(nVertices, (int) cycle.size());
        }

	};
}