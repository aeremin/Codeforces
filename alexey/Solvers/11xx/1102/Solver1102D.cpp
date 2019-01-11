#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1102/problem/D
class Solver1102D {
public:
    void run();
};



void Solver1102D::run() {
    auto n = read<int>();
    auto k = n / 3;
    auto seq = read<string>();

    array<int, 3> counts = {0, 0, 0};
    for (auto c: seq) counts[c - '0']++;

    int r = 0;
    int maxM = 0;

    vector<int> diffs(3);
    for (int i : range(3))
        diffs[i] = k - counts[i];

    for (int i : range(3)) {
        if (auto d = abs(diffs[i]); d > maxM) {
            maxM = d;
            r = i;
        }
    }

    vector<int> opts;
    for (int i : range(3))
        if (i != r)
            opts.push_back(i);

    int p = opts[0];
    int q = opts[1];

    struct Change {
        int from;
        int to;
        int howMany;
    };


    auto changes = (diffs[r] > 0) ?
        vector<Change>{{p, r, -diffs[p]}, {q, r, -diffs[q]}} :
        vector<Change>{{r, p, diffs[p]}, {r, q, diffs[q]}};

    if (changes[0].from < changes[0].to && changes[1].from < changes[1].to) {
        if (changes[1].to > changes[0].to) swap(changes[0], changes[1]);
    }

    if (changes[0].from > changes[0].to && changes[1].from > changes[1].to) {
        if (changes[1].to < changes[0].to) swap(changes[0], changes[1]);
    }

    for (auto ch: changes) {
        // cerr << ch.from << " --> " << ch.to << " (" << ch.howMany << ")\n";
        if (ch.to < ch.from) {
            for (auto it = begin(seq); it != end(seq); ++it) {
                if (*it == '0' + ch.from && ch.howMany > 0) {
                    *it = '0' + ch.to;
                    ch.howMany--;
                }
            }
        } else {
            for (auto it = rbegin(seq); it != rend(seq); ++it) {
                if (*it == '0' + ch.from && ch.howMany > 0) {
                    *it = '0' + ch.to;
                    ch.howMany--;
                }
            }
        }
    }

    cout << seq;
}


class Solver1102DTest : public ProblemTest {};


TEST_F(Solver1102DTest, Example1) {
    setInput(R"(
3
121

)");
    string output = R"(
021

)";
    Solver1102D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102DTest, Example2) {
    setInput(R"(
6
000000

)");
    string output = R"(
001122

)";
    Solver1102D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102DTest, Example3) {
    setInput(R"(
6
211200

)");
    string output = R"(
211200

)";
    Solver1102D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102DTest, Example4) {
    setInput(R"(
6
120110

)");
    string output = R"(
120120

)";
    Solver1102D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102DTest, Example5) {
    setInput(R"(
6
111111

)");
    string output = R"(
001122

)";
    Solver1102D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1102DTest, Example6) {
    setInput(R"(
6
222222

)");
    string output = R"(
001122

)";
    Solver1102D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
