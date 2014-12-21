#include "stdafx.h"
#include "CppUnitTest.h"

#include "../algo/KnuttMorrisPratt.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::vector;
using std::min;
using std::max;

namespace AlgoUnitTest
{
	TEST_CLASS(KnuttMorrisPrattUT)
	{
	public:
		TEST_METHOD(EmptyString)
		{
			auto res = calc_prefix_function("");
			Assert::IsTrue(res.empty());
		}

		TEST_METHOD(HasProperSize)
		{
			int cLength = 100;
			auto res = calc_prefix_function(multipliedString(cLength, "%"));
			Assert::AreEqual(cLength, (int)res.size());
		}

		TEST_METHOD(SameCharString)
		{
			int cLength = 200;
			auto res = calc_prefix_function(multipliedString(cLength, "$"));
			for (int i = 0; i < res.size(); ++i)
			{
				Assert::AreEqual(i, res[i]);
			}
		}

		TEST_METHOD(AlternatingCharString)
		{
			int cHalfLength = 400;
			auto evenString = multipliedString(cHalfLength, "12");
			auto res = calc_prefix_function(evenString);
			for (int i = 0; i < evenString.length(); ++i)
			{
				Assert::AreEqual(max(i - 1, 0), res[i]);
			}
		}

		TEST_METHOD(ConcreteString_abcabcd)
		{
			auto res = calc_prefix_function("abcabcd");
			vector<int> correctres = { 0, 0, 0, 1, 2, 3, 0};
			for (int i = 0; i < res.size(); ++i)
			{
				Assert::AreEqual(correctres[i], res[i]);
			}
		}

	private:
		string multipliedString(int len, string c)
		{
			string res = "";
			for (int i = 0; i < len; ++i)
			{
				res += c;
			}
			return res;
		}
	};
}