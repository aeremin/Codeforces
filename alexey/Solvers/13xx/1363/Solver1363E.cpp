
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "graph/graph.h"
#include "graph/dfs.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1363/problem/E
      
class Solver1363E {
  public:
    void run();
};

struct VertexInfo {
    int64_t cost, diff;
};

void Solver1363E::run() {
    auto n = read<int>();
    UndirectedGraph<EmptyStruct, VertexInfo> g(n);
    for (int i : range(n)) {
        auto cost = read<int64_t>();
        auto diff = read<int64_t>() - read<int64_t>();
        g.get_vertex_data(i) = {cost, diff};
    }

    for (int i : range(n - 1)) {
        g.add_edge(read<int>() - 1, read<int>() - 1);
    }

    int64_t accumulated_diff = 0;
    vector<int64_t> accumulated_diff_before_enter(n, 0);
    vector<int64_t> subtree_diff(n, 0);
    vector<int64_t> real_cost(n, 0);
    vector<vector<int>> children(n);

    auto on_vertice_enter = [&](const GraphTraversalState& state, int v) {
        auto vertex_data = g.get_vertex_data(v);

        accumulated_diff_before_enter[v] = accumulated_diff;
        accumulated_diff += vertex_data.diff;

        if (state.previous_vertex == kInvalidGraphVertex) {
            real_cost[v] = vertex_data.cost;
        } else {
            real_cost[v] = std::min(vertex_data.cost, real_cost[state.previous_vertex]);
            children[state.previous_vertex].push_back(v);
        }

        return IterationControl::Proceed;
    };

    auto on_vertice_leave = [&](const GraphTraversalState& state, int v) {
        subtree_diff[v] = accumulated_diff - accumulated_diff_before_enter[v];
        return IterationControl::Proceed;
    };

    auto on_vertice_see = [&](const GraphTraversalState& state, int v) {
        return IterationControl::Proceed;
    };

    dfs(g, {0}, on_vertice_see, on_vertice_enter, on_vertice_leave);

    if (accumulated_diff != 0) {
        print(-1);
        return;
    }

    int64_t answer = 0;
    for (int i: range(n)) {
        vector<int64_t> diffs = {g.get_vertex_data(i).diff};
        for (auto child: children[i]) {
            diffs.push_back(subtree_diff[child]);
        }

        int64_t total_positive = 0;
        int64_t total_negative = 0;
        for (auto diff: diffs) {
            if (diff > 0) {
                total_positive += diff;
            } else {
                total_negative -= diff;
            }
        }

        answer += 2 * std::min(total_positive, total_negative) * real_cost[i];
    }

    print(answer);
}


class Solver1363ETest : public ProblemTest {};
    
TEST_F(Solver1363ETest, Example1) {
    setInput(R"(
5
1 0 1
20 1 0
300 0 1
4000 0 0
50000 1 0
1 2
2 3
2 4
1 5

)");
    string output = R"(
4
)";
    Solver1363E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1363ETest, Example2) {
    setInput(R"(
5
10000 0 1
2000 1 0
300 0 1
40 0 0
1 1 0
1 2
2 3
2 4
1 5

)");
    string output = R"(
24000
)";
    Solver1363E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1363ETest, Example3) {
    setInput(R"(
2
109 0 1
205 0 1
1 2

)");
    string output = R"(
-1
)";
    Solver1363E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


