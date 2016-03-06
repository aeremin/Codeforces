#include <Solvers/pch.h>
#include "algo/graph/Graph.hpp"
#include "algo/graph/Dijkstra.hpp"

using namespace std;

class Solver507E
{
public:
    void run();

    using WeightedEdgeGraph = Graph<double, EmptyStruct>;
};

void Solver507E::run()
{
    const double fixRoadCost = 1e-10;
    size_t nCities, nRoads;
    cin >> nCities >> nRoads;
    WeightedEdgeGraph graph(nCities);
    for (int i = 0; i < nRoads; ++i)
    {
        int a, b, z;
        cin >> a >> b >> z;
        graph.addEdge(a - 1, b - 1, 1 + (1 - z) * fixRoadCost);
    }

    set<pair<int, int>> path;
    auto dijkstraResult = getMinimalPathsFrom(graph, 0, numeric_limits<double>::max());
    auto lastVertex = nCities - 1;
    while (lastVertex != 0)
    {
        auto predVertex = dijkstraResult.predecessors[lastVertex];
        path.insert({ min(lastVertex, predVertex), max(lastVertex, predVertex) });
        lastVertex = predVertex;
    }

    vector<tuple<int, int, int>> output;
    for (size_t i = 0; i < nCities; ++i)
        for (auto p : graph.vertexNeighbors(i))
        {
            if (p.first < i)
                continue;
            if (path.count({ i, p.first }) && p.second > 1.)
                output.push_back(make_tuple(i, p.first, 1));
            
            if (!path.count({ i, p.first }) && p.second == 1.)
                output.push_back(make_tuple(i, p.first, 0));
        }

    cout << output.size() << "\n";
    for (auto& t : output)
        cout << get<0>(t) + 1 << " " << get<1>(t) + 1 << " " << get<2>(t) << "\n";
}

class Solver507ETest : public ProblemTest
{
};

TEST_F( Solver507ETest, Example1 )
{
    setInput(R"(
2 1
1 2 0
)");
    Solver507E().run();
    EXPECT_EQ("1\n1 2 1\n", getOutput());
}

TEST_F(Solver507ETest, Example2)
{
    setInput(R"(
4 4
1 2 1
1 3 0
2 3 1
3 4 1
)");
    Solver507E().run();
    EXPECT_EQ("3\n1 2 0\n1 3 1\n2 3 0\n", getOutput());
}

TEST_F(Solver507ETest, Example3)
{
    setInput(R"(
8 9
1 2 0
8 3 0
2 3 1
1 4 1
8 7 0
1 5 1
4 6 1
5 7 0
6 8 0
)");
    Solver507E().run();
    EXPECT_EQ("3\n1 5 0\n2 3 0\n6 8 1\n", getOutput());
}
