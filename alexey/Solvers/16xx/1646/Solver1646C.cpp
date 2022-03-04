
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "math/factorial.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1646/problem/C
      
class Solver1646C {
  public:
    void run();
    
    int answer(int64_t sum, int64_t min_allowed_factorial = 3) {
        int64_t f = factorial(int64_t(1), min_allowed_factorial);
        if (sum < f) return num_of_ones(sum);
        return min(answer(sum, min_allowed_factorial + 1), 1 + answer(sum - f, min_allowed_factorial + 1));
    }
    
    int num_of_ones(int64_t n) {
        int res = 0;
        while (n) {
            res += n % 2;
            n /= 2;
        }
        return res;
    }
};

void Solver1646C::run() {
    for (int i: range(read<int>())) {
        auto n = read<int64_t>();
        print(answer(n));
        print("\n");
    }
}


class Solver1646CTest : public ProblemTest {};
    
TEST_F(Solver1646CTest, Example1) {
    setInput(R"(
4
7
11
240
17179869184

)");
    string output = R"(
2
3
4
1

)";
    Solver1646C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


