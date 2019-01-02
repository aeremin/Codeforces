#include <Solvers/pch.h>
#include "algo/graph/Graph.hpp"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/592/problem/D
class Solver592D
{
public:
    void run();

    struct VertexData
    {
        int isAttacked;
        int attackedCountInSubtree;
        pair<int, int> minSubtreePath;
        pair<int, int> minSubtreePathPassing;
        int minSubtreeCyclicPathLength;
    };
    
    using ProblemGraph = Graph<EmptyStruct, VertexData>;
    unique_ptr<ProblemGraph> graph;

    void dfs(int vInd, int parentInd)
    {
        VertexData vData = graph->get_vertex_data(vInd);
        vData.attackedCountInSubtree = vData.isAttacked;
        vData.minSubtreeCyclicPathLength = 0;

        vector<pair<int, int>> childMinSubtreePaths;
        pair<int, int> minChildPassingPath = { numeric_limits<int>::max(), 0 };

        for (auto& p : graph->out_nbrs(vInd))
        {
            auto childInd = p.first;
            if (childInd == parentInd)
                continue;
            dfs(childInd, vInd);
            VertexData childData = graph->get_vertex_data(childInd);
            if (childData.attackedCountInSubtree > 0)
            {
                vData.attackedCountInSubtree += childData.attackedCountInSubtree;
                vData.minSubtreeCyclicPathLength += childData.minSubtreeCyclicPathLength + 2;
                childMinSubtreePaths.emplace_back(childData.minSubtreePath.first - childData.minSubtreeCyclicPathLength, childData.minSubtreePath.second);
                relax_min(minChildPassingPath, make_pair(childData.minSubtreePathPassing.first - childData.minSubtreeCyclicPathLength, childData.minSubtreePathPassing.second ));
            }
        }
        if (childMinSubtreePaths.size() == 0)
        {
            vData.minSubtreePath = { 0, vInd };
            vData.minSubtreePathPassing = vData.minSubtreePath;
        }
        else if (childMinSubtreePaths.size() == 1)
        {
            vData.minSubtreePath.first += vData.minSubtreeCyclicPathLength - 1 + childMinSubtreePaths[0].first;
            vData.minSubtreePath.second = childMinSubtreePaths[0].second;
            vData.minSubtreePathPassing = vData.minSubtreePath;
            
            minChildPassingPath.first += vData.minSubtreeCyclicPathLength;
            relax_min(vData.minSubtreePathPassing, minChildPassingPath);
        }
        else
        {
            partial_sort(begin(childMinSubtreePaths), begin(childMinSubtreePaths) + 2, end(childMinSubtreePaths));
            vData.minSubtreePath.first = vData.minSubtreeCyclicPathLength - 1 + childMinSubtreePaths[0].first;
            vData.minSubtreePath.second = childMinSubtreePaths[0].second;

            vData.minSubtreePathPassing.first = vData.minSubtreeCyclicPathLength - 2 + childMinSubtreePaths[0].first + childMinSubtreePaths[1].first;
            vData.minSubtreePathPassing.second = min(childMinSubtreePaths[0].second, childMinSubtreePaths[1].second);
            
            minChildPassingPath.first += vData.minSubtreeCyclicPathLength;
            relax_min(vData.minSubtreePathPassing, minChildPassingPath);
        }

        graph->get_vertex_data(vInd) = vData;
    }

};

void Solver592D::run()
{
    int nCities, nAttackedCities;
    cin >> nCities >> nAttackedCities;
    graph.reset(new ProblemGraph(nCities, vector<VertexData>(nCities, { 0, 0 })));
    for (int i = 0; i < nCities - 1; ++i)
    {
        int from, to;
        cin >> from >> to;
        graph->add_edge(from - 1, to - 1);
    }

    int maxAttackedCity = 0;
    for (int i = 0; i < nAttackedCities; ++i)
    {
        int c;
        cin >> c;
        --c;
        graph->get_vertex_data(c) = { 1 };
        relax_max(maxAttackedCity, c);
    }

    dfs(maxAttackedCity, maxAttackedCity);
    auto vData = graph->get_vertex_data(maxAttackedCity);
    cout << (vData.minSubtreePathPassing.second + 1) << " " << vData.minSubtreePathPassing.first;
}

class Solver592DTest : public ProblemTest
{
};

TEST_F( Solver592DTest, Example1 )
{
    setInput("6 4        1 2        2 3        2 4        4 5        4 6        2 4 5 6");
    Solver592D().run();
    EXPECT_EQ("2 4", getOutput());
}

TEST_F( Solver592DTest, Example2 )
{
    setInput("7 2        1 2        1 3        1 4        3 5        3 6        3 7        2 7");
    Solver592D().run();
    EXPECT_EQ("2 3", getOutput());
}

TEST_F(Solver592DTest, OneAttackedCity)
{
    setInput("1 1    1");
    Solver592D().run();
    EXPECT_EQ("1 0", getOutput());
}

TEST_F(Solver592DTest, FullBinaryTrie)
{
    setInput("7 7   1 2    1 3   2 4   2 5   3 6   3 7    1 2 3 4 5 6 7");
    Solver592D().run();
    EXPECT_EQ("4 8", getOutput());
}

TEST_F(Solver592DTest, StarGraph)
{
    setInput("7 7   1 2    1 3   1 4   1 5   1 6   1 7    1 2 3 4 5 6 7");
    Solver592D().run();
    EXPECT_EQ("2 10", getOutput());
}

TEST_F(Solver592DTest, TripodGraph)
{
    setInput("9 9   1 2    2 3   3 4   4 5   5 6   6 7    4 8   9 8   1 2 3 4 5 6 7 8 9");
    Solver592D().run();
    EXPECT_EQ("1 10", getOutput());
}