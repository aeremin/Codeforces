#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/graph/Graph.hpp"
#include "algo/graph/Dijkstra.hpp"
#include "util/relax.h"
using namespace std;

class Solver567E
{
public:
    void run();

    struct EdgeInfo {
        int from, to;
        int64_t w;
    };

};

void Solver567E::run()
{
    int nVertices, nEdges, startVertice, endVertice;
    cin >> nVertices >> nEdges >> startVertice >> endVertice;
    --startVertice;
    --endVertice;
    Graph<int64_t, EmptyStruct> gForward(nVertices), gBackward(nVertices);
    vector<EdgeInfo> edgeInfos;
    for (int i : range(nEdges)) {
        int a, b;
        int64_t w;
        cin >> a >> b >> w;
        gForward.add_directed_edge(a - 1, b - 1, w);
        gBackward.add_directed_edge(b - 1, a - 1, w);
        edgeInfos.push_back({ a - 1, b - 1, w });
    }
    
    auto forwardDists = getMinimalPathsFrom(gForward, startVertice, int64_t(-1));
    auto backwardDists = getMinimalPathsFrom(gBackward, endVertice, int64_t(-1));
    auto totalDistance = forwardDists.minimalDistances[endVertice];

    vector<tuple<int64_t, int64_t, int>> minPathEdges;
    for (int i : range(nEdges)) {
        auto edgeInfo = edgeInfos[i];
        auto ld = forwardDists.minimalDistances[edgeInfo.from];
        auto rd = backwardDists.minimalDistances[edgeInfo.to];
        if (ld >= 0 && rd >= 0 && ld + edgeInfo.w + rd == totalDistance)
            minPathEdges.push_back(make_tuple(ld, ld + edgeInfo.w, i));
    }
    sort(begin(minPathEdges), end(minPathEdges));
    minPathEdges.push_back(make_tuple(totalDistance, totalDistance, -1));
    vector<int64_t> ans(nEdges, numeric_limits<int>::max());
    int64_t maxRight = 0;
    for (int i : range(minPathEdges.size() - 1)) {
        const auto& currRef = minPathEdges[i];
        const auto& nextRef = minPathEdges[i + 1];
        bool isUniqueMinEdge = get<0>(currRef) >= maxRight && get<1>(currRef) <= get<0>(nextRef);
        if (isUniqueMinEdge)
            ans[get<2>(currRef)] = 0;
        relax_max(maxRight, get<1>(currRef));
    }

    for (int i : range(nEdges)) {
        if (ans[i] == 0)
            continue;
        auto edgeInfo = edgeInfos[i];
        auto ld = forwardDists.minimalDistances[edgeInfo.from];
        auto rd = backwardDists.minimalDistances[edgeInfo.to];
        auto neededW = totalDistance - ld - rd - 1;
        if (ld >= 0 && rd >= 0 && neededW > 0)
            ans[i] = edgeInfo.w - neededW;
    }

    for (auto elt : ans) {
        if (elt == 0)
            cout << "YES\n";
        else if (elt == numeric_limits<int>::max())
            cout << "NO\n";
        else
            cout << "CAN " << elt << "\n";
    }

}

class Solver567ETest : public ProblemTest {};

TEST_F(Solver567ETest, Example1)
{
    string input = R"(6 7 1 6
1 2 2
1 3 10
2 3 7
2 4 8
3 5 3
4 5 2
5 6 1
)";
    string output = R"(YES
CAN 2
CAN 1
CAN 1
CAN 1
CAN 1
YES
)";
    setInput(input);
    Solver567E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver567ETest, Example2) {
    string input = R"(3 3 1 3
1 2 10
2 3 10
1 3 100
)";
    string output = R"(YES
YES
CAN 81
)";
    setInput(input);
    Solver567E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver567ETest, Example3)
{
    string input = R"(2 2 1 2
1 2 1
1 2 2
)";
    string output = R"(YES
NO
)";
    setInput(input);
    Solver567E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


