#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/graph/Graph.hpp"
#include "algo/graph/TopologicalSorter.hpp"
#include "util/relax.h"
#include "algo/DisjointSet.hpp"
using namespace std;

class Solver650C
{
public:
    void run();
    int h, w;

    int pack(int x, int y) {
        return x + w * y;
    }

    vector<vector<int>> divideToBuckets(vector<pair<int, int>> rowData) const {
        sort(begin(rowData), end(rowData));
        vector<vector<int>> res(1);
        int currV = rowData[0].first;
        for (const auto& p : rowData) {
            if (p.first != currV) {
                res.push_back({});
                currV = p.first;
            }
            res.back().push_back(p.second);
        }
        return res;
    }
};

void Solver650C::run() {
    cin >> h >> w;
    vector<int> m = readVector<int>(h * w);

    vector<vector<vector<int>>> perColumnBuckets(w), perRowbuckets(h);
    for (int y : range(h)) {
        vector<pair<int, int>> vp(w);
        for (int x : range(w)) {
            auto ind = pack(x, y);
            vp[x] = make_pair(m[ind], ind);
        }
        perRowbuckets[y] = divideToBuckets(move(vp));
    }

    for (int x : range(w)) {
        vector<pair<int, int>> vp(h);
        for (int y : range(h)) {
            auto ind = pack(x, y);
            vp[y] = make_pair(m[ind], ind);
        }
        perColumnBuckets[x] = divideToBuckets(move(vp));
    }

    DisjointSet ds(h * w);
    for (auto perDirectionBuckets : { &perColumnBuckets, &perRowbuckets })
        for (const auto& buckets : *perDirectionBuckets)
            for (const auto& bucket : buckets)
                for (auto elt : bucket)
                    ds.unionSets(bucket.front(), elt);

    SimpleGraph g(h * w);

    for (auto perDirectionBuckets : { &perColumnBuckets, &perRowbuckets })
        for (const auto& buckets : *perDirectionBuckets)
            for (int i : range<int>(1, buckets.size()))
                g.add_undirected_edge(ds.rep(buckets[i].front()), ds.rep(buckets[i - 1].front()));

    auto topsortorder = makeTopologicalSorter(g).getSortedOrder();
    reverse(begin(topsortorder), end(topsortorder));
    vector<int> mArchived(m.size(), 1);
    for (auto ind : topsortorder)
        for (auto pNei : g.out_nbrs(ind))
            relax_max(mArchived[ind], mArchived[pNei.first] + 1);

    for (int y : range(h)) {
        for (int x : range(w)) {
            print(mArchived[ds.rep(pack(x, y))]);
            print(' ');
        }
        print('\n');
    }
}

class Solver650CTest : public ProblemTest {};

TEST_F(Solver650CTest, Example1)
{
    string input = R"(2 2
1 2 
3 4 
)";
    string output = R"(1 2 
2 3 
)";
    setInput(input);
    Solver650C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver650CTest, Example2)
{
    string input = R"(4 3
20 10 30
50 40 30
50 60 70
90 80 70
)";
    string output = R"(2 1 3 
5 4 3 
5 6 7 
9 8 7 
)";
    setInput(input);
    Solver650C().run();
    EXPECT_EQ(output, getOutput());
}


