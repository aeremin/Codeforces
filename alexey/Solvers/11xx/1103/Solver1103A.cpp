#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1103/problem/A
class Solver1103A {
public:
    void run();
};

void Solver1103A::run() {
    auto seq = read<string>();
    int i = 0;
    int j = 0;
    for (auto c : seq) {
        if (c == '1') {
            cout << (1 + i) << " " << 3 << "\n";
            i = (i + 1) % 4;
        }
        else {
            cout << (1 + 2 * j) << " " << 1 << "\n";
            j = (j + 1) % 2;
        }
    }
}


class Solver1103ATest : public ProblemTest {};


TEST_F(Solver1103ATest, Example1) {
    setInput(R"(
010

)");
    string output = R"(
1 1
1 3
3 1
)";
    Solver1103A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

