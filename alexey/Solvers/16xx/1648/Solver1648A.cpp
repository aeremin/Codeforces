
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1648/problem/A
      
class Solver1648A {
  public:
    void run();

    int64_t calc(const vector<vector<int>>& table) {
        unordered_map<int, pair<int64_t, int64_t>> colors;
        int64_t result = 0;
        for (int j: range(table[0].size())) {
            for (int i: range(table.size())) {
                auto c = table[i][j];
                result += colors[c].first * j - colors[c].second;
                colors[c].first++;
                colors[c].second += j;
            }
        }
        return result;
    }
};

void Solver1648A::run() {
    auto n = read<int>();
    auto m = read<int>();
    vector<vector<int>> table;
    for (int i: range(n)) {
        table.push_back(readVector<int>(m));
    }

    vector<vector<int>> table_transposed(m, vector<int>(n, 0));
    for (int i: range(n)) {
        for (int j: range(m)) {
            table_transposed[j][i] = table[i][j];
        }
    }

    print(calc(table) + calc(table_transposed));
}


class Solver1648ATest : public ProblemTest {};
    
TEST_F(Solver1648ATest, Example1) {
    setInput(R"(
2 3
1 2 3
3 2 1

)");
    string output = R"(
7

)";
    Solver1648A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1648ATest, Example2) {
    setInput(R"(
3 4
1 1 2 2
2 1 1 2
2 2 1 1

)");
    string output = R"(
76

)";
    Solver1648A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1648ATest, Example3) {
    setInput(R"(
4 4
1 1 2 3
2 1 1 2
3 1 2 1
1 1 2 1

)");
    string output = R"(
129

)";
    Solver1648A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


