#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver672B {
public:
    void run();
};

void Solver672B::run() {
    string s;
    read<int>();
    cin >> s;

    if (s.length() > 26) {
        cout << -1;
        return;
    }

    map<char, int> symbolCount;
    for (auto c : s)
        ++symbolCount[c];

    int ans = 0;
    for (auto p : symbolCount)
        ans += p.second - 1;

    cout << ans;
}


class Solver672BTest : public ProblemTest {};


TEST_F(Solver672BTest, Example1) {
    string input = R"(2
aa
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver672B().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver672BTest, Example2) {
    string input = R"(4
koko
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver672B().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver672BTest, Example3) {
    string input = R"(5
murat
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver672B().run();
    EXPECT_EQ(output, getOutput());
}
