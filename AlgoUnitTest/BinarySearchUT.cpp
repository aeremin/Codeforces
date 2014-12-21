#include "stdafx.h"
#include "CppUnitTest.h"

#include "../algo/BinarySearch.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;

namespace AlgoUnitTest
{
	TEST_CLASS(BinarySearchUT)
	{
    private:
        const int cDataSetSize = 100;
    public:
		
		TEST_METHOD(ReturnsLastOnEmptyRange)
		{
            vector<int> empty;
            Assert::IsTrue(binarySearch(begin(empty), end(empty), [](int elt){ return true; }) == end(empty));
		}

        TEST_METHOD(ReturnsFirstOnSingleEltRange)
        {
            const int cTestElt = 15;
            vector<int> sameElt(cDataSetSize, cTestElt);
            Assert::IsTrue(binarySearch(begin(sameElt), end(sameElt), [&](int elt){ return elt == cTestElt; }) == begin(sameElt));
        }

        TEST_METHOD(CanFindElementInIotaArray)
        {
            vector<int> iotadata(cDataSetSize);
            std::iota(begin(iotadata), end(iotadata), 0);

            srand(12);
            int eltToFind = rand() % cDataSetSize;
            auto foundIter = binarySearch(begin(iotadata), end(iotadata), [&](int elt){ return elt >= eltToFind; });
            Assert::IsTrue(*foundIter = eltToFind);
        }

        TEST_METHOD(CanFindElementInRandomArray)
        {
            vector<int> randomdata(cDataSetSize);
            for (auto& elt : randomdata)
                elt = rand();

            std::sort(begin(randomdata), end(randomdata));

            srand(12);
            int indToFind = rand() % cDataSetSize;
            int eltToFind = randomdata[indToFind];
            auto foundIter = binarySearch(begin(randomdata), end(randomdata), [&](int elt){ return elt >= eltToFind; });
            Assert::IsTrue(*foundIter >= eltToFind);
            Assert::IsTrue(foundIter == begin(randomdata) || *(foundIter - 1) < eltToFind);
        }

        TEST_METHOD(WorksOnConcreteExample)
        {
            vector<int> concretedata = { 1, 2, 3, 3, 3, 5, 7 };
            int eltToFind = 3;
            auto foundIter = binarySearch(begin(concretedata), end(concretedata), [&](int elt){ return elt >= eltToFind; });
            Assert::IsTrue(foundIter - begin(concretedata) == 2);
        }

	};
}