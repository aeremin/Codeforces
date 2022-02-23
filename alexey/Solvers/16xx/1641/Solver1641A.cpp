
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1641/problem/A
      
class Solver1641A {
  public:
    void run();
};

void Solver1641A::run() {
    for (auto t: range(read<int>())) {
        auto n = read<int>();
        auto x = read<int64_t>();
        auto a = readVector<int64_t>(n);
        multiset<int64_t> s(a.begin(), a.end());
        int answer = 0;
        while (!s.empty()) {
            auto smallest = *s.begin();
            s.erase(s.begin());
            if (auto it = s.find(smallest * x); it != s.end()) {
                s.erase(it);
            } else {
                ++answer;
            }
        }
        print(answer);
        print("\n");
    }
}


class Solver1641ATest : public ProblemTest {};
    
TEST_F(Solver1641ATest, Example1) {
    setInput(R"(
4
4 4
1 16 4 4
6 2
1 2 2 2 4 7
5 3
5 2 3 5 15
9 10
10 10 10 20 1 100 200 2000 3

)");
    string output = R"(
0
2
3
3

)";
    Solver1641A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


