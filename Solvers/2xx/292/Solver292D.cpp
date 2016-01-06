#include <Solvers/pch.h>
#include "algo/DisjointSet.hpp"

using namespace std;

class Solver292D
{
public:
    void run();
};

void Solver292D::run()
{
    int nComputers, nWires;
    cin >> nComputers >> nWires;
    vector<pair<int, int>> wires(nWires);
    for (auto& p : wires)
    {
        cin >> p.first >> p.second;
        --p.first;
        --p.second;
    }

    int nQueries;
    cin >> nQueries;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < nQueries; ++i)
    {
        int l, r;
        cin >> l >> r;
        queries.emplace_back(l - 1, nWires - r, i);
    }

    sort(begin(queries), end(queries));

    vector<int> nComponentsForQuery(nQueries);

    DisjointSet components(nComputers);
    DisjointSet componentsCopy = components;
    int currL = 0, currR = 0;
    for (auto q : queries)
    {
        int l, r, i;
        tie(l, r, i) = q;
        if (l > currL)
        {
            while (l > currL)
            {
                components.unionSets(wires[currL].first, wires[currL].second);
                ++currL;
            }
            componentsCopy = components;
            currR = 0;
        }

        while (r > currR)
        {
            componentsCopy.unionSets(wires[nWires - 1 - currR].first, wires[nWires - 1 - currR].second);
            ++currR;
        }

        nComponentsForQuery[i] = componentsCopy.getComponentsCount();
    }

    for (auto c : nComponentsForQuery)
        cout << c << "\n";
}

class Solver292DTest : public ProblemTest
{
};

TEST_F( Solver292DTest, Example1 )
{
    setInput("6 5        1 2        5 4        2 3        3 1        3 6        6        1 3        2 5        1 5        5 5        2 4        3 3");
    Solver292D().run();
    EXPECT_EQ("4\n5\n6\n3\n4\n2\n", getOutput());
}
