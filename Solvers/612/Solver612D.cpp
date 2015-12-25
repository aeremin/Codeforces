#include "Solvers/pch.h"
#include <stack>

using namespace std;

class Solver612D
{
public:
	void run();
};


void Solver612D::run()
{
	std::ios::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;
	std::unordered_map<int, int> startpoints(n), endpoints(n);
	std::vector<int> points;
	points.reserve(n);
	for (int i = 0; i < n; ++i)
	{
		int from, to;
		cin >> from >> to;
		endpoints[to]++;
		startpoints[from]++;
		points.push_back(from);
		points.push_back(to);
	}

	sort(begin(points), end(points));

	vector<int> points2 = { points[0] };
	for (int i = 1; i < points.size(); ++i)
		if (points2.back() != points[i]) points2.push_back(points[i]);


	vector<pair<int, int>> result;
	int64_t currCoverage = 0;
	for (auto p : points2)
	{
		if (startpoints[p] != 0)
		{
			currCoverage += startpoints[p];
			if (currCoverage >= k && (result.empty() || result.back().second != -1))
				result.push_back({ p, -1 });
		}

		if (endpoints[p] != 0)
		{
			currCoverage -= endpoints[p];
			if (currCoverage < k && !result.empty() && result.back().second == -1)
				result.back().second = p;
		}
	}

	cout << result.size() << endl;
	for (auto p : result)
		cout << p.first << " " << p.second << "\n";
};

class Solver612DTest : public ProblemTest {};

TEST_F(Solver612DTest, Example1)
{
	setInput("3 2		0 5		-3 2		3 8");
	Solver612D().run();
	EXPECT_EQ("2\n0 2\n3 5\n", getOutput());
}

TEST_F(Solver612DTest, Example2)
{
	setInput("3 2		0 5		-3 3		3 8");
	Solver612D().run();
	EXPECT_EQ("1\n0 5\n", getOutput());
}

TEST_F(Solver612DTest, Example3)
{
	setInput("1 1 6 6");
	Solver612D().run();
	EXPECT_EQ("1\n6 6\n", getOutput());
}
