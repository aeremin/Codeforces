#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/numbertheory/Residue.hpp"
#include "util/relax.h"
using namespace std;

class Solver427C
{
public:
    void run();

    vector<vector<int>> g, gr;
    vector<char> used;
    vector<int> order, component;

    void dfs1(int v) {
        used[v] = true;
        for (size_t i = 0; i < g[v].size(); ++i)
            if (!used[g[v][i]])
                dfs1(g[v][i]);
        order.push_back(v);
    }

    void dfs2(int v) {
        used[v] = true;
        component.push_back(v);
        for (size_t i = 0; i < gr[v].size(); ++i)
            if (!used[gr[v][i]])
                dfs2(gr[v][i]);
    }
};



void Solver427C::run()
{
    int n;
    cin >> n;
    auto prices = readVector<int>(n);

    g.resize(n);
    gr.resize(n);

    int nEdges;
    cin >> nEdges;
    
    auto edges = readVector<int>(2 * nEdges);

    for (int i : range(nEdges)) {
        g[edges[2 * i] - 1].push_back(edges[2 * i + 1] - 1);
        gr[edges[2 * i + 1] - 1].push_back(edges[2 * i] - 1);
    }

    used.assign(n, false);
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs1(i);
    
    vector<vector<int>> comps;
    
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!used[v]) {
            dfs2(v);
            comps.push_back(move(component));
            component.clear();
        }
    }

    int64_t totalPrice = 0;
    CodeforcesResidue64 cnt = 1;

    for (auto& comp : comps) {
        int minPrice = numeric_limits<int>::max();
        for (auto ind : comp)
            relax_min(minPrice, prices[ind]);

        totalPrice += minPrice;
        int cntPerComp = 0;
        for (auto ind : comp)
            if (prices[ind] == minPrice) cntPerComp += 1;
        cnt *= cntPerComp;
    }

    cout << totalPrice << " " << cnt;
}

class Solver427CTest : public ProblemTest {};

TEST_F(Solver427CTest, Example1)
{
    string input = R"(3
1 2 3
3
1 2
2 3
3 2
)";
    string output = R"(3 1
)";
    setInput(input);
    Solver427C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver427CTest, Example2)
{
    string input = R"(5
2 8 0 6 0
6
1 4
1 3
2 4
3 4
4 5
5 1
)";
    string output = R"(8 2
)";
    setInput(input);
    Solver427C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver427CTest, Example3)
{
    string input = R"(10
1 3 2 2 1 3 1 4 10 10
12
1 2
2 3
3 1
3 4
4 5
5 6
5 7
6 4
7 3
8 9
9 10
10 9
)";
    string output = R"(15 6
)";
    setInput(input);
    Solver427C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver427CTest, Example4)
{
    string input = R"(2
7 91
2
1 2
2 1
)";
    string output = R"(7 1
)";
    setInput(input);
    Solver427C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

