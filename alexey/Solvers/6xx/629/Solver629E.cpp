#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "graph/graph.h"
#include "algo/graph/TreePreprocessor.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/629/problem/E
class Solver629E
{
public:
    void run();
    
    struct VertexData
    {
        int subtreeSize;
        int64_t totalDistanceToSubtree;
        
        double mean() const
        {
            return double(totalDistanceToSubtree) / double(subtreeSize);
        }
    };
    
    struct EdgeData
    {
        int l = 0;
    };
    
    unique_ptr<UndirectedGraph<EdgeData, EdgeData>> g; 
    
    vector<VertexData> vdDn, vdUp;
    
    void dfsDn(int vInd, int pInd)
    {
        vdDn[vInd].subtreeSize = 1;
        vdDn[vInd].totalDistanceToSubtree = 0;
        for (auto p : g->out_nbrs(vInd))
        {
            if (p.first == pInd) continue;
            dfsDn(p.first, vInd);
            vdDn[vInd].subtreeSize += vdDn[p.first].subtreeSize;
            vdDn[vInd].totalDistanceToSubtree += vdDn[p.first].totalDistanceToSubtree + vdDn[p.first].subtreeSize;
        }
    }

    void dfsUp(int vInd, int pInd, VertexData up);
};

Solver629E::VertexData operator+(const Solver629E::VertexData& a, const Solver629E::VertexData& b)
{
    return {a.subtreeSize + b.subtreeSize, a.totalDistanceToSubtree + b.totalDistanceToSubtree};
}

Solver629E::VertexData operator-(const Solver629E::VertexData& a, const Solver629E::VertexData& b)
{
    return {a.subtreeSize - b.subtreeSize, a.totalDistanceToSubtree - b.totalDistanceToSubtree};
}


Solver629E::EdgeData concatenate(Solver629E::EdgeData a, Solver629E::EdgeData b)
{
    Solver629E::EdgeData r;
    r.l = a.l + b.l;
    return r;
}

void Solver629E::dfsUp(int vInd, int pInd, VertexData up)
{
    vdUp[vInd] = up;
    up.totalDistanceToSubtree += up.subtreeSize; 
    up.subtreeSize++;
    for (auto p : g->out_nbrs(vInd))
        if (p.first != pInd)
        {
            up.subtreeSize += vdDn[p.first].subtreeSize;
            up.totalDistanceToSubtree += vdDn[p.first].subtreeSize + vdDn[p.first].totalDistanceToSubtree;
        }

    for (auto p : g->out_nbrs(vInd))
        if (p.first != pInd)
        {
            auto upCopy = up;
            upCopy.subtreeSize -= vdDn[p.first].subtreeSize;
            upCopy.totalDistanceToSubtree -= vdDn[p.first].subtreeSize + vdDn[p.first].totalDistanceToSubtree;
            dfsUp(p.first, vInd, upCopy); 
        }
}

void Solver629E::run()
{
    int nVertices, nFriends;
    cin >> nVertices >> nFriends;
    vdDn = vector<VertexData>(nVertices);
    vdUp = vector<VertexData>(nVertices);

    g.reset(new UndirectedGraph<EdgeData, EdgeData>(nVertices));
    EdgeData ed;
    ed.l = 1;
    for (int i : range(nVertices - 1))
    {
        int a, b;
        cin >> a >> b;
        g->add_edge(a - 1, b - 1, ed); 
    }

    dfsDn(0, 0);
    
    VertexData vd;
    vd.subtreeSize = 0;
    vd.totalDistanceToSubtree = 0;
    dfsUp(0, 0, vd);
    
    cout << setprecision(8) << fixed;
    
    TreePreprocessor<EdgeData, EdgeData> tp(*g);
    for (int i : range(nFriends))
    {
        int a, b;
        cin >> a >> b;
        --a; --b;
        
        auto p = tp.leastCommonAncestor(a, b);
        auto dist = tp.valueOnPath(a, b).first.l;
        if (p != a && p != b)
        {
            auto ans = dist + 1.0 + vdDn[a].mean() + vdDn[b].mean();
            cout << ans << "\n";
        }
        else
        {
            if (p == b) swap(a, b);
            auto prev = tp.lift(b, dist - 1).parent;
            auto ans = dist + 1.0 + vdUp[prev].mean() + vdDn[b].mean();
            cout << ans << "\n";
        }
        
    }
}

class Solver629ETest : public ProblemTest {};


TEST_F(Solver629ETest, Example1)
{
    string input = R"(4 3
2 4
4 1
3 2
3 1
2 3
4 1
)";
    string output = R"(4.00000000
3.00000000
3.00000000
)";
    setInput(input);
    Solver629E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver629ETest, Example2)
{
    string input = R"(3 3
1 2
1 3
1 2
1 3
2 3
)";
    string output = R"(2.50000000
2.50000000
3.00000000
)";
    setInput(input);
    Solver629E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver629ETest, Example3)
{
    string input = R"(4 1
1 2
2 3
1 4
2 3
)";
    string output = R"(3.00000000
)";
    setInput(input);
    Solver629E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}




