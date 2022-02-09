
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1107/problem/A
      
class Solver1107A {
  public:
    void run();
};

void Solver1107A::run() {
    int n = read<int>();
    for (int i : range(n)) {
        int l = read<int>();
        auto s = read<string>();
        if (s.length() > 2 || s[1] > s[0]) {
            cout << "YES\n2\n";
            cout << s[0] << " " << s.substr(1, s.length() - 1) << "\n";
        }
        else {
            cout << "NO\n";
        }
    }
}


class Solver1107ATest : public ProblemTest {};
    
TEST_F(Solver1107ATest, Example1) {
    setInput(R"(
6
6
654321
4
1337
2
33
4
2122
2
23
2
32
)");
    string output = R"(
YES
2
6 54321
YES
2
1 337
NO
YES
2
2 122
YES
2
2 3
NO
)";
    Solver1107A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


