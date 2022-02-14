
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1637/problem/D
      
class Solver1637D {
  public:
    void run();
};

void Solver1637D::run() {
    for (int i : range(read<int>())) {
        auto n = read<int>();
        auto a = readVector<int>(n);
        auto b = readVector<int>(n);
        vector<char> achievable_diff(2 * 200 * n + 1, 0);
        auto achievable_diff_next = achievable_diff;
        achievable_diff[200 * n] = 1;
        for (int j: range(n)) {
            for (int k: range(achievable_diff.size())) {
                if (achievable_diff[k]) {
                    achievable_diff_next[k + a[j] - b[j]] = 1;
                    achievable_diff_next[k + b[j] - a[j]] = 1;
                }
            }
            std::swap(achievable_diff, achievable_diff_next);
            for (int k: range(achievable_diff.size())) {
                achievable_diff_next[k] = 0;
            }
        }
        int smallest_diff = std::numeric_limits<int>::max();
        for (int j: range(200 * n + 1)) {
            if (achievable_diff[200 * n + j] || achievable_diff[200 * n - j]) {
                smallest_diff = j;
                break;
            }
        }
        int64_t sum = std::accumulate(a.begin(), a.end(), 0) + std::accumulate(b.begin(), b.end(), 0);
        auto add_square = [](int current, int a) { return current + a * a;};
        int64_t square_sum = std::accumulate(a.begin(), a.end(), 0, add_square) + std::accumulate(b.begin(), b.end(), 0, add_square);
        auto square = [](int64_t a) {return a * a;};
        int64_t answer = (n - 2) * square_sum + square((sum + smallest_diff) / 2) + square((sum - smallest_diff + 1) / 2);
        print(answer);
        print('\n');
    }
}


class Solver1637DTest : public ProblemTest {};
    
TEST_F(Solver1637DTest, Example1) {
    setInput(R"(
3
1
3
6
4
3 6 6 6
2 7 4 1
4
6 7 2 4
2 5 3 5

)");
    string output = R"(
0
987
914

)";
    Solver1637D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


