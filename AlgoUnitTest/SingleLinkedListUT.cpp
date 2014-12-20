#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include "../algo/SingleLinkedList.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;
using std::random_shuffle;

namespace AlgoUnitTest
{
	TEST_CLASS(SingleLinkedListUT)
	{
	public:
		
		TEST_METHOD(DefaultConstructedIsEmpty)
		{
            SingleLinkedList<int> list;
            Assert::IsTrue(list.isEmpty());
		}

        TEST_METHOD(AfterInsertNotEmpty)
        {
            SingleLinkedList<int> list;
            list.insert(1);
            Assert::IsFalse(list.isEmpty());
        }

        TEST_METHOD(InsertsInBeginning)
        {
            SingleLinkedList<int> list;
            vector<int> a = { 1, 2, 5, -3 };
            for (auto elt : a)
                list.insert(elt);

            int checkInd = a.size() - 1;
            list.forEach([&](int elt)
            {
                Assert::AreEqual(a[checkInd], elt);
                checkInd--;
            });

        }

        TEST_METHOD(ReversesEmpty)
        {
            SingleLinkedList<int> list;
            list.reverse();
            Assert::IsTrue(list.isEmpty());
        }

        TEST_METHOD(ReversesSingleElt)
        {
            SingleLinkedList<int> list;
            const int testElt = 17;
            list.insert(testElt);
            list.reverse();
            int totalElts = 0;
            list.forEach([&](int elt)
            {
                totalElts++;
                Assert::AreEqual(testElt, elt);
            });
            Assert::AreEqual(1, totalElts);
        }

        TEST_METHOD(ReversesConcreteList12345)
        {
            vector<int> toInsert = { 1, 2, 3, 4, 7 };
            SingleLinkedList<int> list;
            for (auto elt : toInsert)
                list.insert(elt);
            
            vector<int> orderBefore;
            list.forEach([&](int elt){ orderBefore.push_back(elt); });

            list.reverse();

            vector<int> orderAfter;
            list.forEach([&](int elt){ orderAfter.push_back(elt); });

            int size = orderBefore.size();
            Assert::AreEqual(size, (int) orderAfter.size());
            for (int i = 0; i < size; ++i)
            {
                Assert::AreEqual(orderBefore[i], orderAfter[size - i - 1]);
            }

        }

        TEST_METHOD(InsertAndDeleteOneElement)
        {
            SingleLinkedList<int> list;
            auto node = list.insert(17);
            list.deleteNode(node);
            Assert::IsTrue(list.isEmpty());
        }

        TEST_METHOD(InsertThenDeleteInRandomOrder)
        {
            SingleLinkedList<int> list;
            vector<int> eltsToInsert = { 1, 2, 3, -1, 0, 176, 95 };
            vector<SingleLinkedList<int>::NodePtr> nodePtrs;
            for (auto elt : eltsToInsert)
                nodePtrs.push_back(list.insert(elt));

            random_shuffle(begin(nodePtrs), end(nodePtrs));

            for (auto nodePtr : nodePtrs)
                Assert::IsTrue( list.deleteNode(nodePtr) );

            Assert::IsTrue(list.isEmpty());
        }
	};
}