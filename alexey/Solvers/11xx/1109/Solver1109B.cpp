
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1109/problem/B
      
class Solver1109B {
  public:
    void run();
};

void Solver1109B::run() {
    auto s = read<string>();
    if (auto same_as_first = count(begin(s), end(s), s[0]); same_as_first == s.length() ||
        (same_as_first == s.length() - 1 && s.length() % 2 == 1 && s[s.length() / 2] != s[0])
        ) {
        cout << "Impossible";
        return;
    }
    for (int i : range<int>(1, s.length() - 1)) {
        const auto reglued = s.substr(i) + s.substr(0, i);
        if (reglued == s) continue;
        auto reglued_r = reglued;
        reverse(begin(reglued_r), end(reglued_r));
        if (reglued == reglued_r) {
            cout << 1;
            return;
        }
    }
    cout << 2;
}


class Solver1109BTest : public ProblemTest {};
    
TEST_F(Solver1109BTest, Example1) {
    setInput(R"(
nolon

)");
    string output = R"(
2

)";
    Solver1109B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109BTest, Example2) {
    setInput(R"(
otto

)");
    string output = R"(
1

)";
    Solver1109B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109BTest, Example3) {
    setInput(R"(
qqqq

)");
    string output = R"(
Impossible

)";
    Solver1109B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109BTest, Example4) {
    setInput(R"(
kinnikkinnik

)");
    string output = R"(
1

)";
    Solver1109B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109BTest, Example5) {
    setInput(R"(
aaaabaaaa

)");
    string output = R"(
Impossible

)";
    Solver1109B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1109BTest, Example6) {
    setInput(R"(
a

)");
    string output = R"(
Impossible

)";
    Solver1109B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
