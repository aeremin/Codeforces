#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/strings/suffix_automaton.h"
#include "util/relax.h"
using namespace std;

class Solver427D
{
public:
    void run();

    SuffixAutomaton* sa1 = nullptr;
    SuffixAutomaton* sa2 = nullptr;
    int minLen = numeric_limits<int>::max();

    void dfs(int state1, int state2, int len) {
        if (state1 == -1 || state2 == -1)
            return;
        if (sa1->getSize(state1) == 1 && sa2->getSize(state2) == 1) {
            relax_min(minLen, len);
            return;
        }
        for (auto edge : sa1->getStates()[state1].edges)
            dfs(edge.second, sa2->traverse(edge.first, state2), len + 1);
    }
};

void Solver427D::run()
{
    string s1, s2;
    cin >> s1 >> s2;
    SuffixAutomaton a1(s1), a2(s2);
    sa1 = &a1; sa2 = &a2;
    dfs(0, 0, 0);
    cout << (minLen == numeric_limits<int>::max() ? -1 : minLen);
}

class Solver427DTest : public ProblemTest {};

TEST_F(Solver427DTest, Example1)
{
    string input = R"(apple
pepperoni
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver427D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver427DTest, Example2)
{
    string input = R"(lover
driver
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver427D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver427DTest, Example3)
{
    string input = R"(bidhan
roy
)";
    string output = R"(-1
)";
    output.pop_back();
    setInput(input);
    Solver427D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver427DTest, Example4)
{
    string input = R"(testsetses
teeptes
)";
    string output = R"(3
)";
    output.pop_back();
    setInput(input);
    Solver427D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver427DTest, RandomMaxExample) {
    string s1, s2;
    for (int i : range(5000)) {
        s1.push_back('a' + rand() % 2);
        s2.push_back('a' + rand() % 2);
    }
    
    string input = s1 + '\n' + s2;
    string output = "3";
    setInput(input);
    Solver427D().run();
}


