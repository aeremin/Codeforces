#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1101/problem/B
class Solver1101B {
public:
    void run();
};

void Solver1101B::run() {
    auto s = read<string>();

    bool seenOpeningBrace = false;
    int left = -1;
    for (int i : range(s.length())) {
        auto c = s[i];
        seenOpeningBrace = seenOpeningBrace || c == '[';
        if (seenOpeningBrace && c == ':') {
            left = i;
            break;
        }
    }

    bool seenClosingBrace = false;
    int right = -1;
    for (int j : range(s.length())) {
        int i = s.length() - j;
        auto c = s[i];
        seenClosingBrace = seenClosingBrace || c == ']';
        if (seenClosingBrace && c == ':') {
            right = i;
            break;
        }
    }

    // left and right are either -1 or points strictly inside the string
    // In the last case, they point to ':' symbol, so if left == right,
    // so we can't make accordion.
    if (left == -1 || right == -1 || left >= right) {
        cout << -1;
        return;
    }

    // See above - both iterators are strictly inside the string
    cout << count(s.begin() + left, s.begin() + right, '|') + 4;
}


class Solver1101BTest : public ProblemTest {};


TEST_F(Solver1101BTest, Example1) {
    setInput(R"(
|[a:b:|]

)");
    string output = R"(
4

)";
    Solver1101B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1101BTest, Example2) {
    setInput(R"(
|]:[|:]

)");
    string output = R"(
-1

)";
    Solver1101B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

