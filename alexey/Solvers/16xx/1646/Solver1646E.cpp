
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1646/problem/E
      
class Solver1646E {
  public:
    void run();
};

void Solver1646E::run() {
    auto n = read<int>();
    auto l = read<int>();
    vector<int64_t> f(20, 0);
    vector<int> possible(20 * l, 0);
    for (auto k: range(1, 20)) {
        f[k] = f[k - 1];
        for (auto i: range(1, l + 1)) {
            if (possible[k * i] == 0) {
                f[k]++;
                possible[k * i] = 1;
            }
        }
    }
    int64_t answer = 1;
    vector<char> processed(n + 1, false);
    for (int a: range(2, n + 1)) {
        if (processed[a]) continue;
        int k = 0;
        int64_t a_power = a;
        while (a_power <= n) {
            processed[a_power] = true; 
            ++k;
            a_power *= a;
        }
        answer += f[k];
    }
    print(answer);
}


class Solver1646ETest : public ProblemTest {};
    
TEST_F(Solver1646ETest, Example1) {
    setInput(R"(
3 3

)");
    string output = R"(
7

)";
    Solver1646E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1646ETest, Example2) {
    setInput(R"(
2 4

)");
    string output = R"(
5

)";
    Solver1646E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1646ETest, Example3) {
    setInput(R"(
4 2

)");
    string output = R"(
6

)";
    Solver1646E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1646ETest, Example4) {
    setInput(R"(
1000000 1000000

)");
    string output = R"(
999439867182

)";
    Solver1646E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

