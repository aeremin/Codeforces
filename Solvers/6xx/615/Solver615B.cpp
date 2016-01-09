#include <Solvers/pch.h>
#include "algo/graph/Graph.hpp"
#include "algo/Relax.hpp"

using namespace std;

class Solver615B
{
public:
    void run();
};

void Solver615B::run()
{
    int nVertices, nEdges;
    cin >> nVertices >> nEdges;
    SimpleGraph g(nVertices);
    for (int i = 0; i < nEdges; ++i)
    {
        int a, b;
        cin >> a >> b;
        g.addEdge(a - 1, b - 1);
    }

    vector<int64_t> maxLen(nVertices, -1);
    int64_t ans = 0;
    for (int i = 0; i < nVertices; ++i)
    {
        maxLen[i] = 0;
        for (auto& p : g.vertexNeighbors(i))
            relaxMax(maxLen[i], 1 + maxLen[p.first]);
        relaxMax(ans, (maxLen[i] + 1) * g.vertexNeighbors(i).size());
    }

    cout << ans;
}

class Solver615BTest : public ProblemTest
{
};

TEST_F( Solver615BTest, Example1 )
{
    setInput("8 6        4 5        3 5        2 5        1 2        2 8        6 7");
    Solver615B().run();
    EXPECT_EQ("9", getOutput());
}

TEST_F( Solver615BTest, Example2 )
{
    setInput("4 6        1 2        1 3        1 4        2 3        2 4        3 4");
    Solver615B().run();
    EXPECT_EQ("12", getOutput());
}
