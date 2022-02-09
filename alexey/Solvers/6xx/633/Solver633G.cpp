#include <bitset>

#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/printvector.h"
#include "algo/io/readvector.h"
#include "algo/number_theory/primes.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/update_applier.h"
#include "algo/segment_tree/update_types/increase_by.h"
#include "graph/graph.h"
#include "iter/range.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/633/problem/G
class Solver633G
{
public:
    void run();

    vector<pair<int, int>> subtreeRange;
    int counter = 0;

    unique_ptr<UndirectedGraph<>> graph;

    void dfs(int v, int p)
    {
        subtreeRange[v].first = counter;
        ++counter;
        for (auto nei : graph->out_nbrs(v))
            if (nei.first != p)
                dfs(nei.first, v);
        subtreeRange[v].second = counter;
    }
};

namespace
{
    int m;
    const int cMaxM = 1000;
}

class BitSetConcat
{
public:
    bitset<cMaxM> operator()(const bitset<cMaxM>& a, const bitset<cMaxM>& b) const
    {
        return a | b;
    }
};

template<>
class UpdateApplier<update_types::IncreaseBy<int64_t>, BitSetConcat>
{
public:
    static bitset<cMaxM> apply(bitset<cMaxM> bs, const update_types::IncreaseBy<int64_t>& updmod, size_t)
    {
        auto upd = updmod.value_ % m;
        auto res = ((bs << (cMaxM - (m - upd))) >> (cMaxM - m)) | (bs >> (m - upd));
        return res;
    }
};

void Solver633G::run()
{
    int n;
    cin >> n >> m;
    auto vals = readVector<int>(n);
    graph.reset(new UndirectedGraph<>(n));
    for (int i : range(1, n))
    {
        int a, b;
        cin >> a >> b;
        graph->add_edge(a - 1, b - 1);
    }

    subtreeRange.resize(n);
    dfs(0, 0);

    vector<bitset<cMaxM>> data(n);
    for (int i : range(n))
        data[subtreeRange[i].first].set(vals[i] % m);

    auto stree = makeSegmentTree(data, BitSetConcat(), update_types::IncreaseBy<int64_t>());

    vector<int> results;
    int q;
    cin >> q;

    bitset<cMaxM> primesSet;
    auto primes = generatePrimesUntil(m);
    for (auto p : primes)
        primesSet.set(p);

    for (int i : range(q))
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int v, x;
            cin >> v >> x;
            --v;
            stree.updateRange(subtreeRange[v].first, subtreeRange[v].second, update_types::IncreaseBy<int64_t>(x));
        }
        else
        {
            int v;
            cin >> v;
            --v;
            auto mask = stree.getValueOnSegment(subtreeRange[v].first, subtreeRange[v].second);
            results.push_back((primesSet & mask).count());
        }
    }

    printVector(results, "\n");
}

class Solver633GTest : public ProblemTest {};

TEST_F(Solver633GTest, Example1)
{
    string input = R"(8 20
3 7 9 8 4 11 7 3
1 2
1 3
3 4
4 5
4 6
4 7
5 8
4
2 1
1 1 1
2 5
2 4
)";
    string output = R"(3
1
1
)";
    setInput(input);
    Solver633G().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver633GTest, Example2)
{
    string input = R"(5 10
8 7 5 1 0
1 2
2 3
1 5
2 4
3
1 1 0
1 1 2
2 2
)";
    string output = R"(2
)";
    setInput(input);
    Solver633G().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


