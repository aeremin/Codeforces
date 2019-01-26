
#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Divisors.hpp"
#include "util/relax.h"
#include "algo/io/readvector.hpp"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1107/problem/D
      
class Solver1107D {
  public:
    void run();
};

void Solver1107D::run() {
    int n = read<int>();
    vector<vector<char>> m(n, vector<char>(n));
    auto lines = readVector<string>(n);
    for (int i : range(n)) {
        auto& l = lines[i];
        for (int j : range(n / 4)) {
            auto& c = l[j];
            int d = (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10;
            m[i][4 * j] = (d & 8) > 0;
            m[i][4 * j + 1] = (d & 4) > 0;
            m[i][4 * j + 2] = (d & 2) > 0;
            m[i][4 * j + 3] = (d & 1) > 0;
        }
    }

    auto candidates = getDivisorsOf(n);
    reverse(begin(candidates), end(candidates));
    candidates.pop_back();
    for (auto k : candidates) {
        bool possible = true;
        for (int j : range(n / k))
            for (int kk : range(k))
                possible = possible && (lines[k * j + kk] == lines[k * j]);
        if (!possible) continue;
        for (int i : range(n / k))
            for (int j : range(n / k))
                for (int kk : range(k))
                    possible = possible && (m[i * k][k * j + kk] == m[i * k][k * j]);
        if (possible) {
            cout << k;
            return;
        }
    }
    cout << 1;
}


class Solver1107DTest : public ProblemTest {};
    
TEST_F(Solver1107DTest, Example1) {
    setInput(R"(
8
E7
E7
E7
00
00
E7
E7
E7

)");
    string output = R"(
1

)";
    Solver1107D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1107DTest, Example2) {
    setInput(R"(
4
7
F
F
F

)");
    string output = R"(
1

)";
    Solver1107D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver1107DTest, Example3) {
    setInput(R"(
4
F
F
F
F

)");
    string output = R"(
4

)";
    Solver1107D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
