#include <Solvers/pch.h>

using namespace std;

class Solver346B
{
public:
    void run();
};

vector<vector<int>> calcAdvancedPrefixFunction(const string& s)
{
    vector<vector<int>> res(s.length(), vector<int>('Z' - 'A' + 1));
    for (int i = 1; i < s.length(); ++i)
    {
        int curPi = res[i - 1][s[i - 1] - 'A'];
        for (char c = 'A'; c <= 'Z'; ++c)
        {
            if (c == s[curPi])
                res[i][c - 'A'] = curPi + 1;
            else
                res[i][c - 'A'] = res[curPi][c - 'A'];
        }
    }
    return res;
}

void relax_max(string& s, const string& r)
{
    if (r.length() > s.length())
        s = r;
}

void Solver346B::run()
{
    string s1, s2, virus;
    cin >> s1 >> s2 >> virus;
    vector<vector<vector<string>>> maxSubsequence(s1.length() + 1, vector <vector<string>>(s2.length() + 1, vector<string>(virus.length() + 1)));
    auto prefixFunc = calcAdvancedPrefixFunction(virus);

    for (int i1 = 0; i1 <= s1.length(); ++i1)
        for (int i2 = 0; i2 <= s2.length(); ++i2)
            for (int j = 0; j < virus.length(); ++j)
            {
                if (i1 < s1.length())
                    relax_max(maxSubsequence[i1 + 1][i2][j], maxSubsequence[i1][i2][j]);
                if (i2 < s2.length())
                    relax_max(maxSubsequence[i1][i2 + 1][j], maxSubsequence[i1][i2][j]);

                if (i1 < s1.length() && i2 < s2.length() && s1[i1] == s2[i2])
                {
                    int jj = -1;
                    if (virus[j] == s1[i1])
                        jj = j + 1;
                    else
                        jj = prefixFunc[j][s1[i1] - 'A'];
                    relax_max(maxSubsequence[i1 + 1][i2 + 1][jj], maxSubsequence[i1][i2][j] + s1[i1]);
                }
            }

    string ans;
    for (int j = 0; j < virus.length(); ++j)
        relax_max(ans, maxSubsequence[s1.length()][s2.length()][j]);

    if (ans.length() > 0)
        cout << ans;
    else
        cout << 0;
}

class Solver346BTest : public ProblemTest
{
};

TEST_F(Solver346BTest, Example3)
{
    setInput("AB       AB        B");
    Solver346B().run();
    EXPECT_EQ("A", getOutput());
}


TEST_F( Solver346BTest, Example1 )
{
    setInput("AJKEQSLOBSROFGZ        OVGURWZLWVLUXTH        OZ");
    Solver346B().run();
    EXPECT_EQ("ORZ", getOutput());
}

TEST_F( Solver346BTest, Example2 )
{
    setInput("AA        A        A");
    Solver346B().run();
    EXPECT_EQ("0", getOutput());
}