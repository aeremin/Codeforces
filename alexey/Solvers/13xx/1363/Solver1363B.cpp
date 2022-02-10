
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1363/problem/B
      
class Solver1363B {
  public:
    void run();
};

void Solver1363B::run() {
    auto t = read<int>();
    for (auto i: range(t)) {
        auto s = read<string>();
        vector<int> minimal_operations_01(s.length() + 1, 0);
        vector<int> minimal_operations_10(s.length() + 1, 0);

        int total_1 = 0;
        for (auto j: range(s.length())) {
            if (s[j] == '1') ++total_1;
            minimal_operations_01[j + 1] += total_1;
            minimal_operations_10[j + 1] += j + 1  - total_1;
        }

        total_1 = 0;
        for (auto jj: range(s.length())) {
            int j = s.length() - jj - 1;
            if (s[j] == '1') ++total_1;
            minimal_operations_01[j] += jj + 1 - total_1;
            minimal_operations_10[j] += total_1;
        }

        print(std::min(*std::min_element(minimal_operations_01.begin(), minimal_operations_01.end()),
                    *std::min_element(minimal_operations_10.begin(), minimal_operations_10.end())));
        print("\n");
    }
}


class Solver1363BTest : public ProblemTest {};
    
TEST_F(Solver1363BTest, Example1) {
    setInput(R"(
7
001
100
101
010
0
1
001100

)");
    string output = R"(
0
0
1
1
0
0
2

)";
    Solver1363B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


