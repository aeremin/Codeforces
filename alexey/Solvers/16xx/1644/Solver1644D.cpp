
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/number_theory/residue.h"
#include "math/quick_power.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1644/problem/D
      
class Solver1644D {
  public:
    void run();
};

using Res = Residue<int64_t, 998244353>;

void Solver1644D::run() {
    for (int t: range(read<int>())) {
        auto n = read<int64_t>();
        auto m = read<int64_t>();
        auto k = read<int64_t>();
        auto q = read<int64_t>();
        vector<pair<int, int>> xy;
        for (int j: range(q)) {
            auto x = read<int64_t>();
            auto y = read<int64_t>();
            xy.emplace_back(x - 1, y - 1);
        }

        unordered_map<int, int> counts_vertical, counts_horizontal;
        for (auto [x, y]: xy) {
            counts_vertical[x]++;
            counts_horizontal[y]++;
        }

        bool all_horizontal = true;
        for (int y: range(m)) {
            if (counts_horizontal[y] == 0) {
                all_horizontal = false;
                break;
            }
        }

        bool all_vertical = true;
        for (int x: range(n)) {
            if (counts_vertical[x] == 0) {
                all_vertical = false;
                break;
            }
        }

        int64_t power = 0;
        for (auto [x, y]: xy) {
            counts_vertical[x]--;
            counts_horizontal[y]--;
            if (counts_vertical[x] == 0) all_vertical = false;
            if (counts_horizontal[y] == 0) all_horizontal = false;
            if (all_horizontal || all_vertical) continue;
            if (counts_vertical[x] && counts_horizontal[y]) continue;
            power++;
        }
        print(quick_power<Res>(Res(k), power));
        print("\n");
    }
}


class Solver1644DTest : public ProblemTest {};
    
TEST_F(Solver1644DTest, Example1) {
    setInput(R"(
2
1 1 3 2
1 1
1 1
2 2 2 3
2 1
1 1
2 2

)");
    string output = R"(
3
4

)";
    Solver1644D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


