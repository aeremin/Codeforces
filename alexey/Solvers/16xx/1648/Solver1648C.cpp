
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "algo/number_theory/residue.h"
#include "math/factorial.h"
#include "iter/range.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/increase_by_sum.h"
#include "algo/segment_tree/update_types/increase_by.h"


using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1648/problem/C

using NewCodeforcesResidue64 = Residue<int64_t, 998244353>;

class Solver1648C {
  public:
    void run();
};


void Solver1648C::run() {
    int n = read<int>();
    int m = read<int>();
    auto s = readVector<int>(n);
    auto t = readVector<int>(m);

    unordered_map<int, int> counts;
    vector<int> counts_vec(200000 + 1, 0);
    for (auto x: s) {
        counts[x]++;
        counts_vec[x]++;
    }

    NewCodeforcesResidue64 mult = factorial(NewCodeforcesResidue64(1), s.size());
    {
        NewCodeforcesResidue64 div = 1;
        for (auto [x, cnt]: counts) div *= factorial(NewCodeforcesResidue64(1), cnt);
        mult = mult / div;
    }

    auto helper = makeSegmentTree(counts_vec, plus<int>(), update_types::IncreaseBy<int>());

    NewCodeforcesResidue64 answer = 0;
    for (auto i: range<int>(t.size())) {
        auto y = t[i];

        if (s.size() - i == 0) {
            answer += 1;
            break;
        }

        answer += NewCodeforcesResidue64(helper.getValueOnSegment(0, y)) * (mult / NewCodeforcesResidue64(s.size() - i));

        if (!counts[y]) {
            break;
        }
        mult = (mult / NewCodeforcesResidue64(s.size() - i)) * NewCodeforcesResidue64(counts[y]);
        helper.updateElement(y, update_types::IncreaseBy(-1));
        --counts[y];
    }

    print(answer);
}


class Solver1648CTest : public ProblemTest {};
    
TEST_F(Solver1648CTest, Example1) {
    setInput(R"(
3 4
1 2 2
2 1 2 1

)");
    string output = R"(
2

)";
    Solver1648C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1648CTest, Example2) {
    setInput(R"(
4 4
1 2 3 4
4 3 2 1

)");
    string output = R"(
23

)";
    Solver1648C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1648CTest, Example3) {
    setInput(R"(
4 3
1 1 1 2
1 1 2

)");
    string output = R"(
1

)";
    Solver1648C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


