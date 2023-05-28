
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1837/problem/C

class Solver1837C {
  public:
    void run();
};

void Solver1837C::run() {
    for (auto i : range(read<int>())) {
        auto s = read<string>();
        char last = '0';
        for (auto& c : s) {
            if (c == '?') {
                c = last;
            } else {
                last = c;
            }
        }
        print(s);
        print("\n");
    }
}


class Solver1837CTest : public ProblemTest {};
    
TEST_F(Solver1837CTest, Example1) {
    setInput(R"(4
??01?
10100
1??10?
0?1?10?10
)");
    string output = R"(00011
10100
111100
001110010

)";
    Solver1837C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


