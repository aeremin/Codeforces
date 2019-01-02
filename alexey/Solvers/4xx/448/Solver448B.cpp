#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/448/problem/B
class Solver448B
{
public:
    void run();

    unordered_map<char, int> cnt(const string& s) {
        unordered_map<char, int> res;
        for (auto c : s)
            ++res[c];
        return res;
    }
};

void Solver448B::run()
{
    string s, t;
    cin >> s >> t;
    int pos = -1;

    for (char c : t) {
        pos = s.find(c, pos + 1);
        if (pos == string::npos)
            break;
    }

    if (pos != string::npos) {
        cout << "automaton";
        return;
    }

    auto cntS = cnt(s);
    auto cntT = cnt(t);
    for (auto p : cntT) {
        if (cntS[p.first] < p.second) {
            cout << "need tree";
            return;
        }
    }

    if (s.length() == t.length())
        cout << "array";
    else
        cout << "both";
}

class Solver448BTest : public ProblemTest {};

TEST_F(Solver448BTest, Example1)
{
    string input = R"(automaton
tomat
)";
    string output = R"(automaton
)";
    setInput(input);
    Solver448B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448BTest, Example2)
{
    string input = R"(array
arary
)";
    string output = R"(array
)";
    setInput(input);
    Solver448B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448BTest, Example3)
{
    string input = R"(both
hot
)";
    string output = R"(both
)";
    setInput(input);
    Solver448B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448BTest, Example4)
{
    string input = R"(need
tree
)";
    string output = R"(need tree
)";
    setInput(input);
    Solver448B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver448BTest, Example5) {
    string input = R"(aa
aaaaaa
)";
    string output = R"(need tree
)";
    setInput(input);
    Solver448B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


