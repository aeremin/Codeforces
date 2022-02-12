
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1632/problem/A
      
class Solver1632A {
  public:
    void run();
};

void Solver1632A::run() {
    for (auto i: range(read<int>())) {
        read<int>();
        auto s = read<string>();
        bool can = true;
        if (s.length() > 2 || (s.length() == 2 && s[0] == s[1])) can = false;
        print(can ? "YES\n" : "NO\n");
    }
}


class Solver1632ATest : public ProblemTest {};
    
TEST_F(Solver1632ATest, Example1) {
    setInput(R"(
4
1
1
2
10
2
01
4
1010
)");
    string output = R"(
YES
YES
YES
NO
)";
    Solver1632A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


