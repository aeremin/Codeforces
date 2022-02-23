
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/printvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1644/problem/B
      
class Solver1644B {
  public:
    void run();
};

void Solver1644B::run() {
    for (int i: range(read<int>())) {
        auto n = read<int>();
        for (int i : range(n)) {
            vector<int> elts;
            for (int i: range(1, i + 1)) {
                elts.push_back(n + 1 - i);
            }
            elts.push_back(1);
            for (int i: range(i + 1, n)) {
                elts.push_back(n + 1 - i);
            }
            printVector(elts);
            print("\n");
        }
    }
}


class Solver1644BTest : public ProblemTest {};
    
TEST_F(Solver1644BTest, Example1) {
    setInput(R"(
2
4
3

)");
    string output = R"(
1 4 3 2
4 1 3 2
4 3 1 2
4 3 2 1
1 3 2
3 1 2
3 2 1
)";
    Solver1644B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


