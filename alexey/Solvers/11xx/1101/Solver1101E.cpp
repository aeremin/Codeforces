#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1101/problem/E
class Solver1101E {
public:
    void run();
};

void Solver1101E::run() {
    auto n = read<int>();
    int needX = 0, needY = 0;
    string result;
    for (int i : range(n)) {
        char c = read<string>()[0];
        int x = read<int>();
        int y = read<int>();
        if (x < y) swap(x, y);
        if (c == '+') {
            relax_max(needX, x);
            relax_max(needY, y);
        }
        else {
            if (x >= needX && y >= needY) {
                print("YES\n");
            }
            else {
                print("NO\n");
            }
        }
    }
}


class Solver1101ETest : public ProblemTest {};


TEST_F(Solver1101ETest, Example1) {
    setInput(R"(
10
+ 3 2
+ 2 3
? 1 20
? 3 3
? 2 3
+ 1 5
? 10 10
? 1 5
? 1 5
+ 1 1

)");
    string output = R"(
NO
YES
YES
YES
NO
NO

)";
    Solver1101E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

