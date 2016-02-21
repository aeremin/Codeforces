#include <Solvers/pch.h>
#include "algo/graph/Graph.hpp"

using namespace std;

class Solver618D
{
public:
    void run();

    unique_ptr<SimpleGraph> graph;

    vector<pair<int, int>> maxToTake;

    void dfs(size_t vInd, size_t pInd)
    {
        vector<pair<int, int>> childData;
        for (auto& pNei : graph->vertexNeighbors(vInd))
        {
            if (pNei.first == pInd)
                continue;
            dfs(pNei.first, vInd);
            childData.push_back(maxToTake[pNei.first]);
        }

        if (childData.empty())
            maxToTake[vInd] = { 0, 0 };
        else if (childData.size() == 1)
            maxToTake[vInd] = { max(childData[0].first, childData[0].second + 1), max(childData[0].first, childData[0].second + 1) };
        else
        {
            auto comp = [](pair<int, int> a, pair<int, int> b) { return (a.first - a.second) < (b.first - b.second); };
            sort(begin(childData), end(childData), comp);
            auto sum = accumulate(begin(childData), end(childData), int64_t(0), [](int64_t r, pair<int, int> a) { return r + a.first; });
            maxToTake[vInd].first = max({ sum, 1 + sum + childData[0].second - childData[0].first,
                                              2 + sum + childData[0].second - childData[0].first + childData[1].second - childData[1].first });
            maxToTake[vInd].second = max(sum, 1 + sum + childData[0].second - childData[0].first);
        }
    }
};

void Solver618D::run()
{
    size_t n;
    int64_t x, y;
    cin >> n >> x >> y;

    graph.reset(new SimpleGraph(n));
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        graph->addEdge(a - 1, b - 1);
    }

    if (y > x)
    {
        maxToTake = vector<pair<int, int>>(n);
        dfs(0, 0);

        auto maxEdges = maxToTake[0].first;
        cout << x * maxEdges + y * (n - 1 - maxEdges);
    }
    else
    {
        bool isStar = false;
        for (int i = 0; i < n; ++i)
            isStar = isStar || (graph->vertexNeighbors(i).size() == n - 1);

        if (isStar)
            cout << x + (n - 2) * y;
        else
            cout << (n - 1) * y;
    }
}

class Solver618DTest : public ProblemTest {};


TEST_F(Solver618DTest, Example1)
{
    setInput("5 2 3             1 2             1 3             3 4             5 3");
    Solver618D().run();
    EXPECT_EQ("9", getOutput());
}

TEST_F(Solver618DTest, Example2)
{
    setInput("5 3 2             1 2             1 3             3 4             5 3");
    Solver618D().run();
    EXPECT_EQ("8", getOutput());
}