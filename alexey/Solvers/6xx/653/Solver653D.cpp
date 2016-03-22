#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "util/relax.h"
#include "algo/graph/Graph.hpp"
#include "algo/graph/max_flow_push_relabel.h"
using namespace std;


using namespace std;

class Solver653D
{
public:
    void run();
};

void Solver653D::run()
{
    int64_t nVertices, nEdges, nBears;
    cin >> nVertices >> nEdges >> nBears;
    struct Edge { int64_t from, to, w; };
    vector<Edge> edges(nEdges);
    for (auto& e : edges)
        cin >> e.from >> e.to >>  e.w;

    double l = 0.0;
    double r = 1e18;
    while (r - l > 1e-8) {
        auto m = (r + l) / 2.0;
        auto perBear = m / nBears;
        
        Graph<int64_t, EmptyStruct> g(nVertices);
        for (auto& e : edges)
            g.add_undirected_edge(e.from - 1, e.to - 1, e.w / perBear);

        MaxFlowPushRelabel<int64_t, EmptyStruct> calc( g );
        auto fl = calc.GetMaxFlow(0, nVertices - 1).totalFlow;
        if (fl >= nBears)
            l = m;
        else
            r = m;
    }

    cout << setprecision(7) << fixed << r;
}

class Solver653DTest : public ProblemTest {};

TEST_F(Solver653DTest, Example1)
{
    string input = R"(4 4 3
1 2 2
2 4 1
1 3 1
3 4 2
)";
    string output = R"(1.5000000
)";
    output.pop_back();
    setInput(input);
    Solver653D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver653DTest, Example2)
{
    string input = R"(5 11 23
1 2 3
2 3 4
3 4 5
4 5 6
1 3 4
2 4 5
3 5 6
1 4 2
2 5 3
1 5 2
3 2 30
)";
    string output = R"(10.2222222
)";
    output.pop_back();
    setInput(input);
    Solver653D().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver653DTest, Example3) {
    string input = R"(3 2 1
1 3 1
2 3 1
)";
    string output = R"(1.0000000
)";
    output.pop_back();
    setInput(input);
    Solver653D().run();
    EXPECT_EQ(output, getOutput());
}

