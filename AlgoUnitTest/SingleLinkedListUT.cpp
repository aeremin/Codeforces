#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../algo/SingleLinkedList.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;

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
            list.for_each([&](int elt)
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
            list.for_each([&](int elt)
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
            list.for_each([&](int elt){ orderBefore.push_back(elt); });

            list.reverse();

            vector<int> orderAfter;
            list.for_each([&](int elt){ orderAfter.push_back(elt); });

            int size = orderBefore.size();
            Assert::AreEqual(size, (int) orderAfter.size());
            for (int i = 0; i < size; ++i)
            {
                Assert::AreEqual(orderBefore[i], orderAfter[size - i - 1]);
            }

        }
	};
}