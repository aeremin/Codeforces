#include "Solvers/pch.h"

using namespace std;

class Solver612B
{
public:
	void run();
};


void Solver612B::run()
{
	int n;
	cin >> n;
	vector<pair<int, int>> pos(n);
	for (int i = 0; i < n; ++i)
	{
		pos[i].second = i;
		cin >> pos[i].first;
	}

	sort(begin(pos), end(pos));

	int64_t ans = 0;
	for (int i = 1; i < n; ++i)
		ans += abs(pos[i].second - pos[i - 1].second);

	cout << ans;
}

class Solver612BTest : public ProblemTest {};

TEST_F(Solver612BTest, Example1)
{
	setInput("3		3 1 2");
	Solver612B().run();
	EXPECT_EQ("3", getOutput());
}

TEST_F(Solver612BTest, Example2)
{
	setInput("5		1 3 5 4 2");
	Solver612B().run();
	EXPECT_EQ("10", getOutput());
}

