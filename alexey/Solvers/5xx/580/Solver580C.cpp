#include "Solvers/pch.h"
#include "Solver580C.h"
#include "algo/graph/Graph.hpp"
#include "algo/graph/DepthFirstSearch.hpp"

void Solver580C::run()
{
    size_t nVertices, maxCatsAllowed;
    cin >> nVertices >> maxCatsAllowed;

    vector<int> hasCat(nVertices);
    for (auto& h : hasCat)
        cin >> h;

    SimpleGraph g(nVertices);
    for (size_t i = 0; i < nVertices - 1; ++i)
    {
        size_t a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1);
    }

    DepthFirstSearcher searcher(g);
    
    int currentCats = 0;
    vector<size_t> nCatsInARow(nVertices);

    searcher.setVertexPreprocessCallback([&](int vInd)->bool
    {
        auto parentCatsInARow = (vInd == 0) ? 0 : nCatsInARow[searcher.getParent(vInd)];
        nCatsInARow[vInd] = (hasCat[vInd] == 1) ? parentCatsInARow + 1 :
            (parentCatsInARow > maxCatsAllowed ? parentCatsInARow : 0);
        return false;
    });

    searcher.search(0);

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
