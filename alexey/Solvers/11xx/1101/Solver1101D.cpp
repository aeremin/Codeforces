#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/number_theory/primes.h"
#include "algo/io/readvector.h"
#include "graph/graph.h"
#include "util/relax.h"
#include "algo/graph/rooted_graph.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1101/problem/D
class Solver1101D {
public:
    void run();
};

void Solver1101D::run() {
    auto n = read<int>();
    auto nums = readVector<int>(n);
    UndirectedGraph<> g(n);
    for (int i : range(n - 1)) {
        int x = read<int>() - 1;
        int y = read<int>() - 1;
        g.add_edge(x, y);
    }

    RootedGraph rooted(g, 0);
    
    map<int, set<int>> primeToVertices;
    for (int i : range(n)) {
        auto dec = decomposeToPrimePowers(nums[i]);
        for (auto[prime, alpha] : dec)
            primeToVertices[prime].insert(i);
    }

    int ans = 0;
    for (const auto&[p, vertices] : primeToVertices) {
        set<int> skip;
        vector<pair<int, int>> depthAndVertice;
        for (auto v : vertices) depthAndVertice.emplace_back(rooted.depth(v), v);
        sort(rbegin(depthAndVertice), rend(depthAndVertice));
        map<int, int> verticeToMaxChildDistance;
        for (auto [d, v]: depthAndVertice) {
            if (skip.count(v)) continue;
            int steps = 0;
            skip.insert(v);
            relax_max(ans, steps + verticeToMaxChildDistance[v] + 1);
            verticeToMaxChildDistance[v] = steps;
            while (v != 0 && vertices.count(*rooted.parent(v))) {
                ++steps;
                v = *rooted.parent(v);
                if (skip.count(v)) {
                    relax_max(ans, steps + verticeToMaxChildDistance[v] + 1);
                    break;
                }
                else {
                    skip.insert(v);
                    relax_max(ans, steps + verticeToMaxChildDistance[v] + 1);
                    verticeToMaxChildDistance[v] = steps;
                }
            }
        }
    }

    cout << ans;
}


class Solver1101DTest : public ProblemTest {};


TEST_F(Solver1101DTest, Example1) {
    setInput(R"(3
2 3 4
1 2
2 3
)");
    string output = R"(1
)";
    Solver1101D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1101DTest, Example2) {
    setInput(R"(3
2 3 4
1 3
2 3
)");
    string output = R"(2
)";
    Solver1101D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1101DTest, Example3) {
    setInput(R"(3
1 1 1
1 2
2 3
)");
    string output = R"(0
)";
    Solver1101D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1101DTest, Example4) {
    setInput(R"(6
3 2 2 2 2 2
1 2
2 3
2 4
4 5
4 6
)");
    string output = R"(4
)";
    Solver1101D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

