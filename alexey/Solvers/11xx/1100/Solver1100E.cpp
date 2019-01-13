#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "graph/Graph.h"
#include "algo/io/printvector.h"
#include "graph/topological_sort_optimistic.h"
#include "graph/topological_sort_checked.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1100/problem/E
class Solver1100E {
public:
    struct Road {
        int from;
        int to;
        int price;
    };

    void run();

    bool CanFix(int price);

    DirectedGraph<> LimitToPrice(int price);

    int v;
    int e;
    vector<Road> roads;
};

void Solver1100E::run() {
    v = read<int>();
    e = read<int>();
    {
        auto r = readVector<int>(3 * e);
        for (int i : range(e)) {
            roads.push_back({ r[3 * i] - 1, r[3 * i + 1] - 1, r[3 * i + 2] });
        }
    }

    int l = -1;
    int r = 1000000000 + 1;
    while (r - l > 1) {
        int m = (r + l) / 2;
        if (CanFix(m)) r = m; else l = m;
    }

    const auto minPrice = r;

    cout << minPrice << " ";

    auto g = LimitToPrice(minPrice);
    auto order = topological_sort_optimistic(g);
    vector<int> index_to_order(v);
    for (int i : range(v)) {
        index_to_order[order[i]] = i;
    }
    vector<int> changes;
    for (auto i : range(e)) {
        if (index_to_order[roads[i].from] < index_to_order[roads[i].to]) changes.push_back(i + 1);
    }

    cout << changes.size() << "\n";
    printVector(changes);
}

bool Solver1100E::CanFix(int price) {
    auto r = topological_sort_checked(LimitToPrice(price));
    return r.status() == TopologicalSortResult::Ok;
}

DirectedGraph<> Solver1100E::LimitToPrice(int price)
{
    DirectedGraph<> g(v);
    for (auto edge: roads) {
        if (edge.price > price) {
            g.add_directed_edge(edge.from, edge.to);
        }
    }
    return g;
}

class Solver1100ETest : public ProblemTest {};


TEST_F(Solver1100ETest, Example1) {
    setInput(R"(5 6
2 1 1
5 2 6
2 3 2
3 4 3
4 5 5
1 5 4
)");
    string output = R"(2 2
1 3 
)";
    Solver1100E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1100ETest, Example2) {
    setInput(R"(5 7
2 1 5
3 2 3
1 3 3
2 4 1
4 3 5
5 4 1
1 5 3
)");
    string output = R"(3 3
3 4 7 
)";
    Solver1100E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

