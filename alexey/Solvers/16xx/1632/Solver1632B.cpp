
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/printvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1632/problem/B
      
class Solver1632B {
  public:
    void run();
};

void Solver1632B::run() {
    for (auto i: range(read<int>())) {
        auto n = read<int>();
        int max_power_of_2 = 1;
        while (max_power_of_2 * 2 < n) max_power_of_2 *= 2;
        vector<int> answer;
        for (auto l: range(max_power_of_2 + 1, n)) {
            answer.push_back(l);
        }
        answer.push_back(max_power_of_2);
        for (auto l: range(max_power_of_2)) {
            answer.push_back(l);
        }
        printVector(answer);
        print("\n");
    }
}


class Solver1632BTest : public ProblemTest {};
    
TEST_F(Solver1632BTest, Example1) {
    setInput(R"(
4
2
3
5
10

)");
    string output = R"(
1 0
2 0 1
4 0 1 2 3
9 8 0 1 2 3 4 5 6 7

)";
    Solver1632B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


