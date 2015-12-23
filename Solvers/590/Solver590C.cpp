#include "Solvers/pch.h"

class Solver590C
{
public:
	void run();

	vector<string> countryMap;
	vector<vector<int>> distanceTo[3];
	vector<pair<int, int>> toProceed[3];
};

int sentinelValue = numeric_limits<int>::max() / 4;

void Solver590C::run()
{
	int height, width;
	cin >> height >> width;
	countryMap = vector<string>(height);
	for (auto& row : countryMap)
		cin >> row;

	for (int i = 0; i < 3; ++i)
		distanceTo[i] = vector<vector<int>>(width, vector<int>(height, sentinelValue));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			auto c = countryMap[y][x];
			switch (c)
			{
			case '1':
				distanceTo[0][x][y] = 0;
				toProceed[0].push_back({ x, y });
				break;
			case '2':
				distanceTo[1][x][y] = 0;
				toProceed[1].push_back({ x, y });
				break;
			case '3':
				distanceTo[2][x][y] = 0;
				toProceed[2].push_back({ x, y });
				break;
			}
		}
	}

	pair<int, int> offsets[] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

	for (int i = 0; i < 3; ++i)
	{
		while (toProceed[i].size() > 0)
		{
			vector<pair<int, int>> toProceedNext;
			for (auto& p : toProceed[i])
			{
				for (auto& offs : offsets)
				{
					pair<int, int> nei = { p.first + offs.first, p.second + offs.second };
					if (nei.first >= 0 && nei.first < width && nei.second >= 0 && nei.second < height 
						&& distanceTo[i][nei.first][nei.second] == sentinelValue
						&& countryMap[nei.second][nei.first] != '#')
					{
						toProceedNext.push_back(nei);
						distanceTo[i][nei.first][nei.second] = distanceTo[i][p.first][p.second] + 1;
					}
				}
			}
			toProceed[i] = move(toProceedNext);
		}
	}

	int ans = sentinelValue;

	int dist01 = sentinelValue;
	int dist12 = sentinelValue;
	int dist20 = sentinelValue;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			auto c = countryMap[y][x];
			int dist[3];
			for (int i = 0; i < 3; ++i) dist[i] = distanceTo[i][x][y];
			int len = dist[0] + dist[1] + dist[2];
			if (len < sentinelValue)
			{
				ans = min(ans, len - 2);
			}

			if (c == '1')
			{
				dist20 = min(dist20, dist[2]);
				dist01 = min(dist01, dist[1]);
			}
			else if (c == '2')
			{
				dist01 = min(dist01, dist[0]);
				dist12 = min(dist12, dist[2]);
			}
			else if (c == '3')
			{
				dist12 = min(dist12, dist[1]);
				dist20 = min(dist20, dist[0]);
			}
		}
	}

	for (auto* d : { &dist01, &dist12, &dist20 })
		if (*d != sentinelValue) --(*d);

	ans = min(ans, min(dist01 + dist12, min(dist01 + dist20, dist12 + dist20)));
	
	cout << (ans == sentinelValue ? -1 : ans);
}

class Solver590CTest : public ProblemTest {};

TEST_F(Solver590CTest, Example1)
{
	setInput("4 5		11..2  #..22  #.323  .#333");
	Solver590C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver590CTest, Example2)
{
	setInput("1 5		1#2#3");
	Solver590C().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver590CTest, Example3)
{
	setInput("1 5		1.2.3");
	Solver590C().run();
	EXPECT_EQ("2", getOutput());
}

TEST_F(Solver590CTest, Example4)
{
	setInput("1 5		11223");
	Solver590C().run();
	EXPECT_EQ("0", getOutput());
}

TEST_F(Solver590CTest, Example5)
{
	setInput("2 2		11 23");
	Solver590C().run();
	EXPECT_EQ("0", getOutput());
}

TEST_F(Solver590CTest, Example6)
{
	setInput("1 4		12#3");
	Solver590C().run();
	EXPECT_EQ("-1", getOutput());
}