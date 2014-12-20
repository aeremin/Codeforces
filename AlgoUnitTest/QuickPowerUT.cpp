#include "stdafx.h"
#include "CppUnitTest.h"
#include "../algo/quickpower.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgoUnitTest
{
	TEST_CLASS(QuickPowerUT)
	{
	public:
		
		TEST_METHOD(ZeroPower)
		{
            for (int i = 1; i < 10; ++i)
            {
                Assert::AreEqual(1, quick_power(i, 0));
                Assert::AreEqual(1.0, quick_power((double) i, 0), 1e-6);
            }
		}

        TEST_METHOD(FirstPower)
        {
            for (int i = 1; i < 10; ++i)
            {
                Assert::AreEqual(i, quick_power(i, 1));
                Assert::AreEqual((double) i, quick_power((double)i, 1), 1e-6);
            }
        }

        TEST_METHOD(SameAsSlowForConcreteA)
        {
            double a = 3.5;
            double a_powered = 1.0;
            for (int d = 0; d < 10; ++d)
            {
                Assert::AreEqual(a_powered, quick_power(a, d));
                a_powered *= a;
            }
        }
	};
}