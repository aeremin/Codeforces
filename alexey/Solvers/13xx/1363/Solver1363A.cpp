
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1363/problem/A
      
class Solver1363A {
  public:
    void run();
};

void Solver1363A::run() {
    auto t = read<int>();
    for (int i : range(t)) {
        auto n = read<int>();
        auto x = read<int>();
        auto a = readVector<int>(n);
        int sum = 0;
        bool all_odd = true;
        bool all_even = true;
        for (auto elt: a) {
            sum += elt;
            all_even = all_even && (elt % 2 == 0);
            all_odd = all_odd && (elt % 2 == 1);
        }
        if (all_even) {
            print("No\n");
        } else if (all_odd) {
            if (x % 2 == 1)
                print("Yes\n");
            else
                print("No\n");
        } else if (x == n) {
            if (sum % 2 == 1)
                print("Yes\n");
            else
                print("No\n");
        } else {
            print("Yes\n");
        }
    }
}


class Solver1363ATest : public ProblemTest {};
    
TEST_F(Solver1363ATest, Example1) {
    setInput(R"(
5
1 1
999
1 1
1000
2 1
51 50
2 2
51 50
3 3
101 102 103

)");
    string output = R"(
Yes
No
Yes
Yes
No

)";
    Solver1363A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


