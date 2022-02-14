
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1637/problem/C
      
class Solver1637C {
  public:
    void run();
};

void Solver1637C::run() {
    for (int i : range(read<int>())) {
        auto v = readVector<int64_t>(read<int>());
        auto m = *max_element(v.begin() + 1, v.end() - 1);
        if (m == 1 || (v.size() == 3 && m % 2 == 1)) {
            print(-1);
            print("\n");
        } else {
            auto s = std::accumulate(v.begin() + 1, v.end() - 1, int64_t(0));
            auto odd = std::count_if(v.begin() + 1, v.end() - 1, [](int elt) {return elt % 2 == 1;});
            print((s + odd) / 2);
            print("\n");
        }
    }
}


class Solver1637CTest : public ProblemTest {};
    
TEST_F(Solver1637CTest, Example1) {
    setInput(R"(
4
5
1 2 2 3 6
3
1 3 1
3
1 2 1
4
3 1 1 2

)");
    string output = R"(
4
-1
1
-1 

)";
    Solver1637C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
