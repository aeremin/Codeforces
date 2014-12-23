#include "stdafx.h"
#include "CppUnitTest.h"
#include "GraphHelper.h"
#include "../algo/ConnectedComponentsDecomposer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(ConnectedComponentsDecomposerUT)
	{
	public:
		
		TEST_METHOD(WorksOnSimpleCycle)
		{
            const int nVertices = 10;
            Graph g = GraphHelper::createSimpleCycleGraph(nVertices);
            ConnectedComponentsDecomposer decomposer(g);
            decomposer.run();

            for (int elt : decomposer.getVertexToComponentMap())
                Assert::AreEqual(0, elt);

            auto components = decomposer.getComponents();
            Assert::AreEqual(1, (int) components.size());
            Assert::AreEqual(nVertices, (int)components[0].size());
		}

        TEST_METHOD(WorksOnConcreteTwoComponentsGraph)
        {
            // 0 - 1  2
            //  \ /   |
            //   3    4
            Graph g;
            g.addEdge(0, 1);
            g.addEdge(3, 1);
            g.addEdge(3, 0);

            g.addEdge(2, 4);

            ConnectedComponentsDecomposer decomposer(g);
            decomposer.run();

            vector<int> expectedComponent = { 0, 0, 1, 0, 1 };
            for (int i = 0; i < 5; ++i)
                Assert::AreEqual(expectedComponent[i], decomposer.getVertexToComponentMap()[i]);

            auto components = decomposer.getComponents();
            Assert::AreEqual(2, (int)components.size());
            Assert::AreEqual(3, (int)components[0].size());
            Assert::AreEqual(2, (int)components[1].size());
        }

	};
}