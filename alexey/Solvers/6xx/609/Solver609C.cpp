#include "Solvers/pch.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/609/problem/C
class Solver609C
{
public:
    void run();
};

vector<int> calcPrefixFunction(const string& s)
{
    vector<int> pi;
    if (s.empty())
        return pi;
    pi.push_back(0);
    for (int i = 1; i < s.length(); ++i)
    {
        int curPi = pi.back();
        while (curPi > 0 && s[i] != s[curPi])
            curPi = pi[curPi - 1];
        if (s[i] == s[curPi]) curPi++;
        pi.push_back(curPi);
    }
    return pi;
}

void Solver609C::run()
{
    int n;
    cin >> n;
    std::string first, second;
    cin >> first >> second;
    std::set<char> lasts = { first.back(), second.back() };
    
    std::map<char, char> invertor = { {'N', 'S'}, {'S', 'N'}, {'W', 'E'}, {'E', 'W'} };
    std::string conc;
    for (auto i = n - 2; i >= 0; --i)
        conc.push_back(invertor[first[i]]);

    conc = conc + second;

    auto pi = calcPrefixFunction(conc);
    if (pi.back() > 0)
        cout << "NO";
    else
        cout << "YES";
}

class Solver609CTest : public ProblemTest {};

TEST_F(Solver609CTest, Example1)
{
    setInput("7        NNESWW        SWSWSW");
    Solver609C().run();
    EXPECT_EQ("YES", getOutput());
}

TEST_F(Solver609CTest, Example2)
{
    setInput("3        NN        SS");
    Solver609C().run();
    EXPECT_EQ("NO", getOutput());
}

TEST_F(Solver609CTest, Example3)
{
    setInput("3        NW        ES");
    Solver609C().run();
    EXPECT_EQ("NO", getOutput());
}