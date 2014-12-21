#include "stdafx.h"
#include "CppUnitTest.h"

#include "../algo/SlidingWindowMinFinder.h"
using std::vector;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(SlidingWindowMinFinderUT)
	{
	public:
		
		TEST_METHOD(WorksOnConcreteExample)
		{
            vector<int> data = { 2, 3, 3, 3, 1, 5, -2, 2, 7 };

            SlidingWindowMinFinder<int> minFinder(data);
            minFinder.incRight(); // 2
            minFinder.incRight(); // 2 3
            Assert::AreEqual(2, minFinder.getMin());
            minFinder.incLeft(); // 3
            Assert::AreEqual(3, minFinder.getMin());
            minFinder.incRight(); // 3 3
            Assert::AreEqual(3, minFinder.getMin());
            minFinder.incRight(); // 3 3 3
            Assert::AreEqual(3, minFinder.getMin());
            minFinder.incLeft(); // 3 3
            Assert::AreEqual(3, minFinder.getMin());
            minFinder.incLeft(); // 3
            Assert::AreEqual(3, minFinder.getMin());
            minFinder.incRight(); // 3 1 
            minFinder.incRight(); // 3 1 5
            minFinder.incLeft(); // 1 5
            Assert::AreEqual(1, minFinder.getMin());
            minFinder.incLeft(); // 5
            Assert::AreEqual(5, minFinder.getMin());
            minFinder.incRight(); // 5 -2
            minFinder.incLeft(); // -2
            Assert::AreEqual(-2, minFinder.getMin());
            minFinder.incRight(); // -2 2
            minFinder.incRight(); // -2 2 7
            Assert::AreEqual(-2, minFinder.getMin());
            minFinder.incLeft(); // 2 7
            Assert::AreEqual(2, minFinder.getMin());
            minFinder.incLeft(); // 7
            Assert::AreEqual(7, minFinder.getMin());
		}

	};
}