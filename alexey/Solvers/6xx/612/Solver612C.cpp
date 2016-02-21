#include "Solvers/pch.h"
#include <stack>

using namespace std;

class Solver612C
{
public:
    void run();
};


void Solver612C::run()
{
    string s;
    cin >> s;

    set<char> opening = { '(', '{', '[', '<' };
    map<char, char> corresponding = { {')', '('}, {'}', '{' }, { ']', '[' }, { '>', '<' } };
    int ans = 0;
    stack<char> opened;
    for (auto c : s)
    {
        if (opening.count(c))
            opened.push(c);
        else
        {
            if (opened.empty())
            {
                cout << "Impossible";
                return;
            }
            if (opened.top() != corresponding[c]) ans++;
            opened.pop();
        }
    }

    if (!opened.empty())
    {
        cout << "Impossible";
        return;
    }

    cout << ans;
};

class Solver612CTest : public ProblemTest {};

TEST_F(Solver612CTest, Example1)
{
    setInput("[<}){}");
    Solver612C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver612CTest, Example2)
{
    setInput("{()}[]");
    Solver612C().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver612CTest, Example3)
{
    setInput("]]");
    Solver612C().run();
    EXPECT_EQ("Impossible", getOutput());
}