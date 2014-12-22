#include "stdafx.h"
#include "CppUnitTest.h"
#include <utility>
#include "../algo/DepthFirstSearch.hpp"

using std::min;
using std::max;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(DepthFirstSearchUT)
	{
	public:
		
		TEST_METHOD(WorksOnSingleVertex)
		{
            Graph graph(1);
            DepthFirstSearcher searcher(graph);
            int verticesCount = 0;
            auto increaseVerticesCount = [&](int)
            {
                verticesCount++;
                return false;
            };

            int edgesCount = 0;
            auto increaseEdgesCount = [&](int,int,bool)
            {
                edgesCount++;
                return false;
            };

            searcher.setVertexPreprocessCallback(increaseVerticesCount);
            searcher.setEdgePostprocessCallback(increaseEdgesCount);

            Assert::IsFalse(searcher.search(0));
            Assert::AreEqual(0, edgesCount);
            Assert::AreEqual(1, verticesCount);
		}

        TEST_METHOD(WorksOnLinearGraph)
        {
            int nVertices = 10;
            Graph graph(10);
            for (int i = 0; i < nVertices - 1; ++i)
                graph.addEdge(i, i + 1);

            DepthFirstSearcher searcher(graph);
            int verticesCount = 0;
            auto increaseVerticesCount = [&](int vertex)
            {
                Assert::AreEqual(verticesCount++, vertex);
                return false;
            };

            int edgesCount = 0;
            auto increaseEdgesCount = [&](int from, int to, bool discovery)
            {
                if (discovery)
                {
                    Assert::AreEqual(edgesCount++, from);
                    Assert::AreEqual(edgesCount, to);
                }
                return false;
            };

            searcher.setVertexPreprocessCallback(increaseVerticesCount);
            searcher.setEdgePostprocessCallback(increaseEdgesCount);

            Assert::IsFalse(searcher.search(0));
        }

        TEST_METHOD(WorksOnSimpleCycle)
        {
            int nVertices = 20;
            Graph graph(10);
            for (int i = 0; i < nVertices - 1; ++i)
                graph.addEdge(i, i + 1);
            
            graph.addEdge(nVertices - 1, 0);

            DepthFirstSearcher searcher(graph);
            int verticesCount = 0;
            auto increaseVerticesCount = [&](int vertex)
            {
                Assert::AreEqual(verticesCount++, vertex);
                return false;
            };

            int discoveryEdgesCount = 0;
            auto processEdge = [&](int from, int to, bool discovery)
            {
                if (discovery)
                {
                    Assert::AreEqual(discoveryEdgesCount++, from);
                    Assert::AreEqual(discoveryEdgesCount, to);
                }
                return false;
            };

            searcher.setVertexPreprocessCallback(increaseVerticesCount);
            searcher.setEdgePostprocessCallback(processEdge);

            Assert::IsFalse(searcher.search(0));
        }

	};
}