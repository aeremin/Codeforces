
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "graph/graph.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1106/problem/D

class Solver1106D {
  public:
    void run();
};

void Solver1106D::run() {
    auto n = read<int>();
    auto m = read<int>();
    UndirectedGraph<> g(n);
    for (int i : range(m)) {
        g.add_edge(read<int>() - 1, read<int>() - 1);
    }

    set<int> available;
    set<int> visited = { 0 };
    vector<int> ans;
    auto push_vertex = [&](int v){
        ans.push_back(v + 1);
        available.erase(v);
        visited.insert(v);
        for (const auto& nei : g.out_nbrs(v)) {
            if (visited.count(nei.first) == 0) {
                available.insert(nei.first);
            }
        }
    };

    push_vertex(0);
    while (!available.empty()) {
        push_vertex(*available.begin());
    }

    printVector(ans);
}


class Solver1106DTest : public ProblemTest {};
    
TEST_F(Solver1106DTest, Example1) {
    setInput(R"(
3 2
1 2
1 3

)");
    string output = R"(
1 2 3 

)";
    Solver1106D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106DTest, Example2) {
    setInput(R"(
5 5
1 4
3 4
5 4
3 2
1 5

)");
    string output = R"(
1 4 3 2 5 

)";
    Solver1106D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106DTest, Example3) {
    setInput(R"(
10 10
1 4
6 8
2 5
3 7
9 4
5 6
3 4
8 10
8 9
1 10

)");
    string output = R"(
1 4 3 7 9 8 6 5 2 10 

)";
    Solver1106D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


