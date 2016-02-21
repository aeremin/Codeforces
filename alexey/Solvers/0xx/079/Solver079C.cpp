#include <Solvers/pch.h>
#include "algo/KnuttMorrisPratt.hpp"
#include "util/relax.h"

using namespace std;

class Solver079C
{
public:
    void run();
};

void Solver079C::run()
{
    string s;
    cin >> s;
    int nBannedStrings;
    cin >> nBannedStrings;
    vector<vector<int>> prefixFunctions(nBannedStrings);
    for (auto& ref : prefixFunctions)
    {
        string bannedString;
        cin >> bannedString;
        ref = calc_prefix_function(bannedString + "!" + s);
    }

    int maxLen = 0;
    int startPos = 0;
    int l = 0;
    for (int r = 0; r < s.length(); ++r)
    {
        for (auto& pi : prefixFunctions)
        {
            int bannedStringLen = pi.size() - s.length() - 1;
            if (pi[r + bannedStringLen + 1] == bannedStringLen)
                relax_max(l, r - bannedStringLen + 2);
        }
        if (r + 1 - l > maxLen)
        {
            maxLen = r + 1 - l;
            startPos = l;
        }
    }

    cout << maxLen << " " << startPos;
}

class Solver079CTest : public ProblemTest
{
};

TEST_F( Solver079CTest, Example1 )
{
    setInput(R"(Go_straight_along_this_street
5
str
long
tree
biginteger
ellipse)");
    Solver079C().run();
    EXPECT_EQ("12 4", getOutput());
}

TEST_F(Solver079CTest, Example2)
{
    setInput(R"(IhaveNoIdea
9
I
h
a
v
e
N
o
I
d)");
    Solver079C().run();
    EXPECT_EQ("0 0", getOutput());
}

TEST_F(Solver079CTest, Example3)
{
    setInput(R"(unagioisii
2
ioi
unagi)");
    Solver079C().run();
    EXPECT_EQ("5 1", getOutput());
}
