
#include <Solvers/pch.h>

#include "graph/graph.h"
#include "util/relax.h"
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1830/problem/A
  
class Solver1830A {
  public:
    void run();
};


void Solver1830A::run() {
    for (int inp: range(read<int>())) {
        auto n = read<int>();
        UndirectedGraph<int, pair<int, int>> g(n);
        for (int i : range(n - 1)) {
          auto from = read<int>() - 1;
          auto to = read<int>() - 1;
          g.add_edge(to, from, i + 1);
        }

        g.get_vertex_data(0) = {1, 0};
        for (int i : range(1, n)) {
          g.get_vertex_data(i) = {0, -1};
        }

        stack<int> to_visit;
        to_visit.push(0);

        int answer = 0;
        while (!to_visit.empty()) {
            auto current = to_visit.top();
            to_visit.pop();

            for (auto& [nei, ord]  : g.out_nbrs(current)) {
                if (g.get_vertex_data(nei).second >= 0) continue;

                auto ord_parent = g.get_vertex_data(current).second;
                auto iter = g.get_vertex_data(current).first + (ord_parent > ord ? 1 : 0);
                g.get_vertex_data(nei) = {iter , ord};

                relax_max(answer, iter);

                to_visit.push(nei);
            }
        }
        print(answer);
        print("\n");
    }
}


class Solver1830ATest : public ProblemTest {};
    
TEST_F(Solver1830ATest, Example1) {
    setInput(R"(2
6
4 5
1 3
1 2
3 4
1 6
7
5 6
2 4
2 7
1 3
1 2
4 5
)");
    string output = R"(2
3

)";
    Solver1830A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


