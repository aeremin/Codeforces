#include <Solvers/pch.h>
#include "algo/graph/Graph.hpp"

using namespace std;

class Solver014D
{
public:
    void run();

    unique_ptr<SimpleGraph> graph;

    vector<int> vertexDepths;
    vector<int> halfTreeDiameters;
    int currentHalfTree;

    void dfs(int vInd, int parentInd)
    {
        vector<int> childDepth = { -1 };
        
        for (auto p : graph->vertexNeighbors(vInd))
        {
            int nei = p.first;
            if (nei == parentInd)
                continue;

            dfs(nei, vInd);
            childDepth.push_back(vertexDepths[nei]);
        }

        sort(begin(childDepth), end(childDepth));
        vertexDepths[vInd] = childDepth.back() + 1;

        int diam = childDepth.back() + 1;
        if (childDepth.size() >= 2)
            diam += childDepth[childDepth.size() - 2] + 1;

        halfTreeDiameters[currentHalfTree] = max(halfTreeDiameters[currentHalfTree], diam);
    }
};

void Solver014D::run()
{
    int nCities;
    cin >> nCities;
    graph.reset(new SimpleGraph(nCities));
    for (int i = 0; i < nCities - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph->addEdge(a - 1, b - 1);
    }

    int ans = 0;
    
    for (int firstVertex = 0; firstVertex < nCities; ++firstVertex)
        for (auto p : graph->vertexNeighbors(firstVertex))
        {
            int secondVertex = p.first;
            if (secondVertex < firstVertex)
                continue;

            vertexDepths = vector<int>(nCities);
            halfTreeDiameters = vector<int>(2);
            currentHalfTree = 0;
            dfs(firstVertex, secondVertex);
            currentHalfTree = 1;
            dfs(secondVertex, firstVertex);
            ans = max(ans, halfTreeDiameters[0] * halfTreeDiameters[1]);
        }
    
    cout << ans;
}

class Solver014DTest : public ProblemTest
{
};

TEST_F( Solver014DTest, Example1 )
{
    setInput("4        1 2        2 3        3 4");
    Solver014D().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver014DTest, Example2 )
{
    setInput("7        1 2        1 3        1 4        1 5        1 6        1 7");
    Solver014D().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver014DTest, Example3)
{
    setInput("6        1 2        2 3        2 4        5 4        6 4");
    Solver014D().run();
    EXPECT_EQ("4", getOutput());
}
