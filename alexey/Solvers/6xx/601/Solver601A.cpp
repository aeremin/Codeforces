#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver601A
{
public:
    void run();

    int mindist(const vector<vector<int>> m, int filterValue)
    {
        int n = m.size();
        vector<bool> visited(n, false);
        int dist = 0;
        vector<int> currLevel = { 0 };
        visited[0] = true;
        while (!currLevel.empty())
        {
            vector<int> nextLevel;
            for (auto v : currLevel)
            {
                if (v == n - 1)
                    return dist;
                for (int i = 0; i < n; ++i)
                    if (!visited[i] && m[v][i] == filterValue)
                    {
                        nextLevel.push_back(i);
                        visited[i] = true;
                    }
            }
            currLevel = move(nextLevel);
            ++dist;
        }
        return -1;
    }
};

void Solver601A::run()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> incidency(n, vector<int>(n, 0));
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        incidency[a - 1][b - 1] = incidency[b - 1][a - 1] = 1;
    }

    int d1 = mindist(incidency, 0);
    int d2 = mindist(incidency, 1);
    if (d1 < 0 || d2 < 0) cout << -1;
    else cout << max(d1, d2);
}

class Solver601ATest : public ProblemTest {};

TEST_F(Solver601ATest, Example1)
{
    string input = R"(4 2
1 3
3 4
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver601A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver601ATest, Example2)
{
    string input = R"(4 6
1 2
1 3
1 4
2 3
2 4
3 4
)";
    string output = R"(-1
)";
    output.pop_back();
    setInput(input);
    Solver601A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver601ATest, Example3)
{
    string input = R"(5 5
4 2
3 5
4 5
5 1
1 2
)";
    string output = R"(3
)";
    output.pop_back();
    setInput(input);
    Solver601A().run();
    EXPECT_EQ(output, getOutput());
}


