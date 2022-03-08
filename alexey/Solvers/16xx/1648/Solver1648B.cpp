
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1648/problem/B
      
class Solver1648B {
  public:
    void run();

    bool contains_any(const vector<int>& sorted, int l, int r) {
        return lower_bound(sorted.begin(), sorted.end(), l) != upper_bound(sorted.begin(), sorted.end(), r);
    }

    bool is_good(const vector<int>& sorted, int c) {
        if (sorted[0] != 1) return false;
        for (auto elt: sorted) {
            if (elt == 1) continue;
            for (int l: range(2, c / elt + 1)) {
                if (!contains_any(sorted, l, l)) {
                    if (contains_any(sorted, l * elt, (l + 1) * elt - 1)) return false;
                }
            }
        }
        return true;
    }
};

void Solver1648B::run() {
    for (int t: range(read<int>())) {
        int n = read<int>();
        int c = read<int>();
        auto elts = readVector<int>(n);
        sort(elts.begin(), elts.end());
        auto last = unique(elts.begin(), elts.end());
        elts.erase(last, elts.end());
        print(is_good(elts, c) ? "Yes\n" : "No\n");
    }
}


class Solver1648BTest : public ProblemTest {};
    
TEST_F(Solver1648BTest, Example1) {
    setInput(R"(
4
3 5
1 2 5
4 10
1 3 3 7
1 2
2
1 1
1

)");
    string output = R"(
Yes
No
No
Yes

)";
    Solver1648B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1648BTest, Example2) {
    setInput(R"(
1
1 1000000
1000000

)");
    string output = R"(
No

)";
    Solver1648B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1648BTest, ContainsAny) {
    Solver1648B s;
    EXPECT_TRUE(s.contains_any({1, 2, 3}, 2, 2));
    EXPECT_FALSE(s.contains_any({1, 2, 3}, 4, 4));
    EXPECT_FALSE(s.contains_any({2, 3, 4}, 1, 1));
    EXPECT_TRUE(s.contains_any({2, 4, 6}, 4, 5));
    EXPECT_TRUE(s.contains_any({2, 4, 6}, 3, 4));
    EXPECT_FALSE(s.contains_any({2, 4, 7}, 5, 6));
}

TEST_F(Solver1648BTest, IsGood1) {
    Solver1648B s;
    vector<int> elts;
    for (int i: range(1, 1000000)) elts.push_back(i);
    EXPECT_TRUE(s.is_good(elts, 100000));
}

TEST_F(Solver1648BTest, IsGood2) {
    Solver1648B s;
    vector<int> elts;
    for (int i: range(1000000)) elts.push_back(1);
    EXPECT_TRUE(s.is_good(elts, 100000));
}

