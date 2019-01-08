#include <Solvers/pch.h>
#include "graph/graph.h"
#include "algo/updatetypes/SetTo.hpp"
#include "algo/updateappliers/SetToIdempotent.h"
#include "algo/SegmentTree.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/620/problem/E
class Solver620E
{
public:
    void run();

    unique_ptr<UndirectedGraph<>> graph;

    vector<uint64_t> colors;
    vector<uint64_t> orderedColors;
    vector<pair<size_t, size_t>> vertexToInterval;

    void dfs(size_t vInd, size_t parentInd)
    {
        vertexToInterval[vInd].first = orderedColors.size();

        for (auto p : graph->out_nbrs(vInd))
            if (p.first != parentInd)
                dfs(p.first, vInd);

        orderedColors.push_back(colors[vInd]);
        vertexToInterval[vInd].second = orderedColors.size();
    }

    int getBitsSet(uint64_t v) { return (v == 0) ? 0 : 1 + getBitsSet(v ^ (v & ~(v - 1))); }

};

void Solver620E::run()
{
    int nVertices, nQueries;
    cin >> nVertices >> nQueries;
    colors.resize(nVertices);
    vertexToInterval.resize(nVertices);
    for (auto& elt : colors)
    {
        int a;
        cin >> a;
        elt = uint64_t(1) << a;
    }

    graph.reset(new UndirectedGraph<>(nVertices));
    for (int i = 1; i < nVertices; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph->add_edge(a - 1, b - 1);
    }

    dfs(0, 0);

    auto segTree = makeSegmentTree(orderedColors, bit_or<uint64_t>(), updateTypes::SetTo<uint64_t>());
    for (int i = 0; i < nQueries; ++i)
    {
        int queryType;
        cin >> queryType;
        if (queryType == 1)
        {
            int vInd, color;
            cin >> vInd >> color;
            segTree.updateRange(vertexToInterval[vInd - 1].first, vertexToInterval[vInd - 1].second, updateTypes::SetTo<uint64_t>(uint64_t(1) << color));
        }
        else
        {
            int vInd;
            cin >> vInd;
            auto colorMask = segTree.getValueOnSegment(vertexToInterval[vInd - 1].first, vertexToInterval[vInd - 1].second);
            cout << getBitsSet(colorMask) << " ";
        }
    }
}

class Solver620ETest : public ProblemTest
{
};

TEST_F( Solver620ETest, Example1 )
{
    setInput("7 10 1 1 1 1 1 1 1 1 2 1 3 1 4 3 5 3 6 3 7 1 3 2 2 1 1 4 3 2 1 1 2 5 2 1 1 6 4 2 1 2 2 2 3");
    Solver620E().run();
    EXPECT_EQ("2 3 4 5 1 2 ", getOutput());
}

TEST_F( Solver620ETest, Example2 )
{
    setInput(R"(
23 30
1 2 2 6 5 3 2 1 1 1 2 4 5 3 4 4 3 3 3 3 3 4 6
1 2
1 3
1 4
2 5
2 6
3 7
3 8
4 9
4 10
4 11
6 12
6 13
7 14
7 15
7 16
8 17
8 18
10 19
10 20
10 21
11 22
11 23
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
1 12 1
1 13 1
1 14 1
1 15 1
1 16 1
1 17 1
1 18 1
1 19 1
1 20 1
1 21 1
1 22 1
1 23 1
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4)");
    Solver620E().run();
    EXPECT_EQ("6 1 3 3 2 1 2 3 5 5 1 2 2 1 1 1 2 3 ", getOutput());
}
