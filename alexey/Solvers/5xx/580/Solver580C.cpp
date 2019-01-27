#include <Solvers/pch.h>
#include "graph/graph.h"
#include "algo/graph/DepthFirstSearch.hpp"
#include "algo/graph/rooted_graph.h"
#include "iter/range.h"

// Solution for Codeforces problem http://codeforces.com/contest/580/problem/C
class Solver580C
{
public:
    void run();
};

void Solver580C::run()
{
    size_t nVertices, maxCatsAllowed;
    cin >> nVertices >> maxCatsAllowed;

    vector<int> hasCat(nVertices);
    for (auto& h : hasCat)
        cin >> h;

    UndirectedGraph<> g(nVertices);
    for (size_t i = 0; i < nVertices - 1; ++i)
    {
        size_t a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1);
    }

    RootedGraph rooted(g, 0);
    
    int currentCats = 0;
    vector<size_t> nCatsInARow(nVertices);

    for (int depth = 0; rooted.vertices_with_depth(depth).size() > 0; ++depth) {
        for (int vInd : rooted.vertices_with_depth(depth)) {
            auto parentCatsInARow = (vInd == 0) ? 0 : nCatsInARow[*rooted.parent(vInd)];
            nCatsInARow[vInd] = (hasCat[vInd] == 1) ? parentCatsInARow + 1 :
                (parentCatsInARow > maxCatsAllowed ? parentCatsInARow : 0);
        }
    }

    int canVisit = 0;
    for (size_t i = 1; i < nVertices; ++i)
    {
        bool isLeaf = g.out_nbrs(i).size() == 1;
        bool notToManyCats = nCatsInARow[i] <= maxCatsAllowed;
        if (isLeaf && notToManyCats)
            canVisit++;
    }

    cout << canVisit;
}

class Solver580CTest : public ProblemTest {};

TEST_F(Solver580CTest, Example1)
{
    setInput("4 1        1 1 0 0        1 2        1 3        1 4");
    Solver580C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver580CTest, Example2)
{
    setInput("7 1        1 0 1 1 0 0 0        1 2        1 3        2 4        2 5        3 6        3 7");
    Solver580C().run();
    EXPECT_EQ("2", getOutput());
}
