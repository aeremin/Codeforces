#include <Solvers/pch.h>
#include "graph/graph.h"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/622/problem/E
class Solver622E
{
public:
    void run();

    vector<int> leavesDepths;
    unique_ptr<UndirectedGraph<>> g;
    int depth = 1;
    void dfs(int v, int p)
    {
        bool isLeaf = true;
        for (auto pNei : g->out_nbrs(v))
        {
            if (pNei.first == p) continue;
            isLeaf = false;
            ++depth;
            dfs(pNei.first, v);
            --depth;
        }

        if (isLeaf)
            leavesDepths.push_back(depth);
    }
};

void Solver622E::run()
{
    int nVertices;
    cin >> nVertices;
    g.reset(new UndirectedGraph<>(nVertices));
    for (int i = 0; i < nVertices - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        g->add_edge(a - 1, b - 1);
    }

    int ans = 0;
    
    for (auto pNei : g->out_nbrs(0))
    {
        leavesDepths.clear();
        dfs(pNei.first, 0);
        sort(begin(leavesDepths), end(leavesDepths));
        int subAns = 0;
        for (auto d : leavesDepths)
        {
            ++subAns;
            relax_max(subAns, d);
        }
        relax_max(ans, subAns);
    }

    cout << ans;
}

class Solver622ETest : public ProblemTest {};

TEST_F(Solver622ETest, Example1)
{
    string input = R"(12
1 2
1 3
1 4
2 5
2 6
3 7
3 8
3 9
8 10
8 11
8 12
)";
    string output = R"(6
)";
    setInput(input);
    Solver622E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622ETest, Example2)
{
    string input = R"(2
2 1
)";
    string output = R"(1
)";
    setInput(input);
    Solver622E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


