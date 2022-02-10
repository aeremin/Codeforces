
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "graph/graph.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1363/problem/C
      
class Solver1363C {
  public:
    void run();
};

void Solver1363C::run() {
    auto t = read<int>();
    for (auto i: range(t)) {
        auto n = read<int>();
        auto x = read<int>() - 1;
        UndirectedGraph<> g(n);
        for (auto j: range(n - 1)) {
            g.add_edge(read<int>() - 1, read<int>() - 1);
        }
        if (g.out_nbrs(x).size() <= 1) {
            print("Ayush\n");
        } else {
            if (n % 2 == 1) {
                print("Ashish\n");
            } else {
                print("Ayush\n");
            }
        }
    }
}


class Solver1363CTest : public ProblemTest {};
    
TEST_F(Solver1363CTest, Example1) {
    setInput(R"(
1
3 1
2 1
3 1

)");
    string output = R"(
Ashish

)";
    Solver1363C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1363CTest, Example2) {
    setInput(R"(
1
3 2
1 2
1 3

)");
    string output = R"(
Ayush

)";
    Solver1363C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


