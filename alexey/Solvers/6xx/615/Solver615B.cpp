#include <Solvers/pch.h>
#include "graph/graph.h"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/615/problem/B
class Solver615B
{
public:
    void run();
};

void Solver615B::run()
{
    int nVertices, nEdges;
    cin >> nVertices >> nEdges;
    UndirectedGraph<> g(nVertices);
    for (int i = 0; i < nEdges; ++i)
    {
        int a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1);
    }

    vector<int64_t> maxLen(nVertices, -1);
    int64_t ans = 0;
    for (int i = 0; i < nVertices; ++i)
    {
        maxLen[i] = 0;
        for (auto& p : g.out_nbrs(i))
            relax_max(maxLen[i], 1 + maxLen[p.first]);
        relax_max<int64_t>(ans, (maxLen[i] + 1) * g.out_nbrs(i).size());
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
