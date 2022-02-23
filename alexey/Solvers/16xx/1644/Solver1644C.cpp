
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/printvector.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1644/problem/C
      
class Solver1644C {
  public:
    void run();
};

void Solver1644C::run() {
    for (int i: range(read<int>())) {
        auto n = read<int>();
        auto x = read<int>();
        auto a = readVector<int64_t>(n);
        vector<int64_t> maximums(n + 1, numeric_limits<int64_t>::min());
        vector<int64_t> prefix_sums = { 0 };
        partial_sum(begin(a), end(a), back_inserter(prefix_sums));

        for (int i : range(n + 1)) {
            for (int j : range(i, n + 1)) {
                relax_max(maximums[j - i], prefix_sums[j] - prefix_sums[i]);
            }
        }

        vector<int64_t> answers;
        for (int k: range(n + 1)) {
            if (k != 0) {
                for (int increases : range(k, n + 1)) {
                    maximums[increases] += x;
                }
            }
            answers.push_back(*max_element(maximums.begin(), maximums.end()));
        }
        printVector(answers);
        print("\n");
    }
}


class Solver1644CTest : public ProblemTest {};
    
TEST_F(Solver1644CTest, Example1) {
    setInput(R"(
3
4 2
4 1 3 2
3 5
-2 -7 -1
10 2
-6 -1 -2 4 -6 -1 -4 4 -5 -4

)");
    string output = R"(
10 12 14 16 18
0 4 4 5
4 6 6 7 7 7 7 8 8 8 8

)";
    Solver1644C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


