#include <Solvers/pch.h>
#include "graph/graph.h"
#include "algo/graph/bipartition_checker.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/623/problem/A
class Solver623A
{
public:
    void run();
};

void Solver623A::run()
{
    int nVertices, nEdges;
    cin >> nVertices >> nEdges;
    vector<vector<bool>> connected(nVertices, vector<bool>(nVertices, false));
    for (int i = 0; i < nEdges; ++i)
    {
        int a, b;
        cin >> a >> b;
        connected[a - 1][b - 1] = true;
        connected[b - 1][a - 1] = true;
    }

    UndirectedGraph<> g(nVertices);
    for (int i = 0; i < nVertices; ++i)
        for (int j = 0; j < i; ++j)
            if (!connected[i][j])
                g.add_edge(i, j);

    auto bp = makeBipartitionChecker(g);
    if (!bp.isBipartite())
    {
        cout << "No";
    }
    else
    {
        auto isNotZeroDegree = [&](int i) { return !g.out_nbrs(i).empty(); };
        
        auto parts = bp.getSomePartitioning();
        string s(nVertices, 'b');
        bool res = true;
        for (auto i : parts.first)
            for (auto j : parts.second)
            {
                if (isNotZeroDegree(i) && isNotZeroDegree(j))
                    res = res && (connected[i][j] == false);
            }

        
        if (!res)
        {
            cout << "No";
        }
        else
        {
            for (auto i : parts.first)
                if (isNotZeroDegree(i))
                    s[i] = 'a';
            for (auto i : parts.second)
                if (isNotZeroDegree(i))
                    s[i] = 'c';
            cout << "Yes\n" << s;
        }
    }
}

class Solver623ATest : public ProblemTest {};

TEST_F(Solver623ATest, Example1)
{
    string input = R"(2 1
1 2
)";
    string output = R"(Yes
bb
)";
    setInput(input);
    Solver623A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver623ATest, Example2)
{
    string input = R"(4 3
1 2
1 3
1 4
)";
    string output = R"(No
)";
    setInput(input);
    Solver623A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver623ATest, Example3)
{
    string input = R"(3 2
1 2
2 3
)";
    string output = R"(Yes
abc)";
    setInput(input);
    Solver623A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
