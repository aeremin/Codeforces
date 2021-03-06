#include <Solvers/pch.h>
#include "graph/graph.h"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/538/problem/E
class Solver538E
{
public:
    void run();

    struct VertexData
    {
        int perPlayerAnswers[2];
        int distanceToRoot;
    };
    
    using ProblemGraph = UndirectedGraph<EmptyStruct, VertexData>;
    unique_ptr<ProblemGraph> graph;
    int leafCount = 0;

    void dfs(int vInd, int parentInd)
    {
        VertexData vData;
        vData.distanceToRoot = (vInd == parentInd) ? 0 : graph->get_vertex_data(parentInd).distanceToRoot + 1;
        graph->get_vertex_data(vInd) = vData;

        int countsSumInd = (vData.distanceToRoot + 1) % 2;
        int countsMinInd = 1 - countsSumInd;

        int childSum = 0;
        int childMin = numeric_limits<int>::max();
        
        for (auto& p : graph->out_nbrs(vInd))
        {
            auto childInd = p.first;
            if (childInd == parentInd)
                continue;
            dfs(childInd, vInd);

            auto childData = graph->get_vertex_data(childInd);
            childSum += childData.perPlayerAnswers[countsSumInd];
            relax_min(childMin, childData.perPlayerAnswers[countsMinInd]);
        }

        if (childSum == 0) // childSum == 0  ==> no childs ==> leaf
        {
            childSum = 1;
            childMin = 1;
            leafCount++;
        }

        vData.perPlayerAnswers[countsMinInd] = childMin;
        vData.perPlayerAnswers[countsSumInd] = childSum;
        graph->get_vertex_data(vInd) = vData;
    }
};

void Solver538E::run()
{
    size_t nVertices;
    cin >> nVertices;
    graph.reset(new ProblemGraph(nVertices));
    for (size_t i = 0; i < nVertices - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph->add_edge(a - 1, b - 1);
    }

    dfs(0, 0);
    auto rootData = graph->get_vertex_data(0);
    cout << (leafCount - rootData.perPlayerAnswers[0] + 1) << " " << (rootData.perPlayerAnswers[1]);
}

class Solver538ETest : public ProblemTest
{
};

TEST_F(Solver538ETest, Example1)
{
    setInput("5        1 2        1 3        2 4        2 5");
    Solver538E().run();
    EXPECT_EQ("3 2", getOutput());
}

TEST_F( Solver538ETest, Example2 )
{
    setInput("6        1 2        1 3        3 4        1 5        5 6");
    Solver538E().run();
    EXPECT_EQ("3 3", getOutput());
}

TEST_F(Solver538ETest, Example3)
{
    setInput("7        1 2        1 3        2 4        2 5    5 6    5 7");
    Solver538E().run();
    EXPECT_EQ("4 2", getOutput());
}

TEST_F(Solver538ETest, StarGraph)
{
    setInput("7        1 2        1 3        1 4        1 5    1 6    1 7");
    Solver538E().run();
    EXPECT_EQ("6 6", getOutput());
}

TEST_F(Solver538ETest, Example4)
{
    setInput("8   1 2   1 3   2 4   2 5   2 6    3 7   3 8");
    Solver538E().run();
    EXPECT_EQ("4 2", getOutput());
}
