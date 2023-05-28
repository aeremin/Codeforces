
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1837/problem/B

class Solver1837B {
  public:
    void run();
};

void Solver1837B::run() {
    for (auto i : range(read<int>())) {
        read<int>();
        auto s = read<string>();
        int answer = 0;
        char last = 'x';
        int l = 0;
        for (auto c : s) {
            if (last != c) {
                l = 0;
                last = c;
            }

            l++;
            relax_max(answer, l);
        }
        print(answer + 1);
        print("\n");
    }
}


class Solver1837BTest : public ProblemTest {};
    
TEST_F(Solver1837BTest, Example1) {
    setInput(R"(4
4
<<>>
4
>><<
5
>>>>>
7
<><><><
)");
    string output = R"(3
3
6
2

)";
    Solver1837B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


