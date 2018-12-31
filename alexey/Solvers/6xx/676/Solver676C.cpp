#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/FunctorIterator.hpp"
using namespace std;

class Solver676C {
public:
    void run();
};

void Solver676C::run() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    replace(begin(s), end(s), 'a', char(0));
    replace(begin(s), end(s), 'b', char(1));

    auto canGet = [&](int l) {
        if (l > n) return 1;
        int cnt[2] = { 0, 0 };
        for (int i : range(l))
            ++cnt[s[i]];

        if (min(cnt[0], cnt[1]) <= k) return 0;

        for (int j : range(n - l)) {
            --cnt[s[j]];
            ++cnt[s[j + l]];
            if (min(cnt[0], cnt[1]) <= k) return 0;
        }
        return 1;
    };

    auto l = makeFunctorIterator(0, canGet);
    auto r = makeFunctorIterator(int(s.length()) + 1, canGet);
    cout << (upper_bound(l, r, 0).getParameter() - 1);
}


class Solver676CTest : public ProblemTest {};


TEST_F(Solver676CTest, Example1) {
    string input = R"(4 2
abba
)";
    string output = R"(4
)";
    setInput(input);
    Solver676C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver676CTest, Example2) {
    string input = R"(8 1
aabaabaa
)";
    string output = R"(5
)";
    setInput(input);
    Solver676C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

