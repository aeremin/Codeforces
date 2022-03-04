
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1646/problem/B
      
class Solver1646B {
  public:
    void run();
};

void Solver1646B::run() {
    for (int i: range(read<int>())) {
        auto a = readVector<int64_t>(read<int>());
        sort(a.begin(), a.end());
        int64_t s_red = 0;
        int64_t s_blue = a[0];
        bool possible = false;
        for (int n_red: range((a.size() - 1)/2)) {
            int n_blue = n_red + 1;
            s_red += a[a.size() - 1 - n_red];
            s_blue += a[n_blue];
            if (s_red > s_blue) {
                possible = true;
                break;
            }
        }
        
        print(possible ? "YES\n" : "NO\n");
    }
}


class Solver1646BTest : public ProblemTest {};
    
TEST_F(Solver1646BTest, Example1) {
    setInput(R"(
4
3
1 2 3
5
2 8 6 3 1
4
3 5 4 2
5
1000000000 1000000000 1000000000 1000000000 1000000000

)");
    string output = R"(
NO
YES
NO
NO

)";
    Solver1646B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


