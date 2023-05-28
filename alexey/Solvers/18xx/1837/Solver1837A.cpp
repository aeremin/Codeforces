
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/printvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1837/problem/A

class Solver1837A {
  public:
    void run();
};

void Solver1837A::run() {
    for (auto i : range(read<int>())) {
        auto x = read<int>();
        auto k = read<int>();
        if (x % k == 0) {
            print(2);
            print("\n");
            printVector<int>({x - 1, 1});
        } else {
            print(1);
            print("\n");
            print(x);
        }
        print("\n");
    }
}

class Solver1837ATest : public ProblemTest {};

TEST_F(Solver1837ATest, Example1) {
    setInput(R"(3
10 2
10 3
3 4
)");
    string output = R"(2
9 1
1
10
1
3

)";
    Solver1837A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
