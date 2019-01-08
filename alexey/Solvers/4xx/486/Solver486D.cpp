#include <Solvers/pch.h>
#include "algo/graph/Graph.hpp"
#include "algo/numbertheory/Residue.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/486/problem/D
class Solver486D
{
public:
    void run();

    unique_ptr<UndirectedGraph<EmptyStruct, int>> graph;

    int currentAllowedMaximum = 0;

    CodeforcesResidue64 calc(int vInd, int vParentInd)
    {
        if (graph->get_vertex_data(vInd) > currentAllowedMaximum)
            return 0;

        CodeforcesResidue64 res = 1;
        for (auto& nei : graph->out_nbrs(vInd))
        {
            if (nei.first == vParentInd)
                continue;
            res *= calc(nei.first, vInd) + int64_t(1);
        }
        return res;
    }
};

void Solver486D::run()
{
    int maxAllowedDiff, nVertices;
    cin >> maxAllowedDiff >> nVertices;
    vector<int> verticesValues(nVertices);
    for (auto& v : verticesValues)
        cin >> v;

    vector<pair<int, int>> sortedVertices(nVertices);
    for (int i = 0; i < nVertices; ++i)
        sortedVertices[i] = { verticesValues[i], i };
    sort(begin(sortedVertices), end(sortedVertices));
    
    graph.reset(new UndirectedGraph<EmptyStruct, int>(verticesValues));
    for (int i = 0; i < nVertices - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph->add_edge(a - 1, b - 1);
    }

    CodeforcesResidue64 ans = 0;
    for (auto& p : sortedVertices)
    {
        int vInd = p.second;
        currentAllowedMaximum = p.first + maxAllowedDiff;
        ans += calc(vInd, -1);
        graph->get_vertex_data(vInd) = numeric_limits<int>::max();
    }

    cout << ans;
}

class Solver486DTest : public ProblemTest
{
};

TEST_F( Solver486DTest, Example1 )
{
    setInput("1 4        2 1 3 2        1 2        1 3        3 4");
    Solver486D().run();
    EXPECT_EQ("8", getOutput());
}

TEST_F( Solver486DTest, Example2 )
{
    setInput("0 3        1 2 3        1 2        2 3");
    Solver486D().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver486DTest, Example3)
{
    setInput("4 8        7 8 7 5 4 6 4 10        1 6        1 2        5 8        1 3        3 5        6 7        3 4");
    Solver486D().run();
    EXPECT_EQ("41", getOutput());
}
