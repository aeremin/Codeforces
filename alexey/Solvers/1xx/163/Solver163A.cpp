#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"

using namespace std;

class Solver163A
{
public:
    void run();
};

void Solver163A::run()
{
    string str, seq;
    cin >> str >> seq;
    vector<vector<CodeforcesResidue>> ans(2, vector<CodeforcesResidue>(seq.length() + 1));
    vector<vector<CodeforcesResidue>> ansForSuffixSubstrings(2, vector<CodeforcesResidue>(seq.length() + 1));
    for (int i = 1; i <= str.length(); ++i)
        for (int j = 1; j <= seq.length(); ++j)
        {
            auto currI = i % 2;
            auto prevI = (i - 1) % 2;

            ansForSuffixSubstrings[currI][j] = ansForSuffixSubstrings[currI][j - 1];
            if (str[i - 1] == seq[j - 1])
                ansForSuffixSubstrings[currI][j] += ansForSuffixSubstrings[prevI][j - 1] + 1;

            ans[currI][j] = ans[prevI][j] + ans[currI][j - 1] - ans[prevI][j - 1];
            if (str[i - 1] == seq[j - 1])
                ans[currI][j] += ansForSuffixSubstrings[prevI][j - 1] + 1;
        }

    cout << ans[str.length() % 2][seq.length()];
}

class Solver163ATest : public ProblemTest
{
};

TEST_F( Solver163ATest, Example1 )
{
    setInput("aa\naa");
    Solver163A().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F( Solver163ATest, Example2 )
{
    setInput("codeforces\nforceofcode");
    Solver163A().run();
    EXPECT_EQ("60", getOutput());
}

TEST_F(Solver163ATest, Example3)
{
    string sameSymbolString(5000, 'a');
    setInput(sameSymbolString + '\n' + sameSymbolString);
    Solver163A().run();
}