#include "Solvers/pch.h"

using namespace std;

class Solver590A
{
public:
	void run();
};

void Solver590A::run()
{
	int n;
	cin >> n;
	vector<int> nums(n + 2);
	for (int i = 1; i <= n; ++i)
		cin >> nums[i];
	nums[0] = nums[1];
	nums[n + 1] = nums[n];

	int lastStableEnd = 1;
	int lastStableVal = nums[1];
	int prev = lastStableVal;
	vector<int> result = {};
	int nIterations = 0;
	for (int i = 2; i <= n + 1; ++i)
	{
		auto curr = nums[i];
		if (curr != prev)
		{
			prev = curr;
			continue;
		}
		auto currStableStart = i - 1;
		auto currStableVal = curr;
		auto nChangingBetween = (currStableStart - lastStableEnd - 1);
		if (nChangingBetween % 2 == 0)
		{
			nIterations = max(nIterations, nChangingBetween / 2);
			for (int j = lastStableEnd ; j < i; ++j) result.push_back( (j - lastStableEnd) <= nChangingBetween / 2 ? lastStableVal : currStableVal);
		}
		else
		{
			nIterations = max(nIterations, (nChangingBetween + 1) / 2);
			for (int j = lastStableEnd ; j < i; ++j) result.push_back(currStableVal);
		}
		lastStableEnd = i;
		lastStableVal = currStableVal;
	}
	cout << nIterations << endl;
	for (auto& r : result) cout << r << " ";
}

class Solver590ATest : public ProblemTest {};

TEST_F(Solver590ATest, Example1)
{
	setInput("4		0 0 1 1");
	Solver590A().run();
	EXPECT_EQ("0\n0 0 1 1 ", getOutput());
}

TEST_F(Solver590ATest, Example2)
{
	setInput("5		0 1 0 1 0");
	Solver590A().run();
	EXPECT_EQ("2\n0 0 0 0 0 ", getOutput());
}

TEST_F(Solver590ATest, Example3)
{
	setInput("7		0 0 1 0 1 0 0");
	Solver590A().run();
	EXPECT_EQ("2\n0 0 0 0 0 0 0 ", getOutput());
}

TEST_F(Solver590ATest, Example4)
{
	setInput("8		1 0 1 0 1 0 1 0");
	Solver590A().run();
	EXPECT_EQ("3\n1 1 1 1 0 0 0 0 ", getOutput());
}