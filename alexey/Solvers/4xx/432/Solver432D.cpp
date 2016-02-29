#include <Solvers/pch.h>
#include "algo/strings/KnuttMorrisPratt.hpp"

using namespace std;

class Solver432D
{
public:
    void run();

    void runBruteForce(const string& s);

};

void Solver432D::runBruteForce(const string& s)
{
    vector<pair<int, int>> ans;
    for (int len = 1; len <= s.length(); ++len)
    {
        if (s.substr(0, len) == s.substr(s.length() - len, len))
        {
            int total = 0;
            for (int i = 0; i <= s.length() - len; ++i)
                if (s.substr(0, len) == s.substr(i, len)) total++;
            ans.push_back({ len, total });
        }
    }

    cout << ans.size() << "\n";
    for (auto& p : ans) cout << p.first << " " << p.second << "\n";
}

void Solver432D::run()
{
    string s;
    cin >> s;
    auto pi = calc_prefix_function(s);
    vector<vector<size_t>> inversedPi(s.length() + 1);
    for (size_t i = 0; i < s.length(); ++i)
        inversedPi[pi[i]].push_back(i);

    vector<int> nSubstringsEqualPrefixFullString(s.length() + 1);
    for (auto i = s.length(); i > 0; --i)
    {
        nSubstringsEqualPrefixFullString[i] = 1;
        for (auto j : inversedPi[i])
            nSubstringsEqualPrefixFullString[i] += nSubstringsEqualPrefixFullString[j + 1];
    }

    vector<int> nSubstringsEqualPrefixStringWithoutLastChar(s.length() + 1);
    for (auto i = s.length() - 1; i > 0; --i)
    {
        nSubstringsEqualPrefixStringWithoutLastChar[i] = 1;
        for (auto j : inversedPi[i])
           nSubstringsEqualPrefixStringWithoutLastChar[i] += nSubstringsEqualPrefixStringWithoutLastChar[j + 1];
    }
    
    int outCount = 0;
    for (int i = 1; i <= s.length(); ++i)
        if (nSubstringsEqualPrefixFullString[i] > nSubstringsEqualPrefixStringWithoutLastChar[i])
            outCount++;

    cout << outCount << "\n";

    for (int i = 1; i <= s.length(); ++i)
        if (nSubstringsEqualPrefixFullString[i] > nSubstringsEqualPrefixStringWithoutLastChar[i])
            cout << i << " " << nSubstringsEqualPrefixFullString[i] << "\n";
}

class Solver432DTest : public ProblemTest
{
};

TEST_F(Solver432DTest, Example1)
{
    setInput("ABACABA");
    Solver432D().run();
    EXPECT_EQ("3\n1 4\n3 2\n7 1\n", getOutput());
}

TEST_F(Solver432DTest, Example2)
{
    setInput("AAA");
    Solver432D().run();
    EXPECT_EQ("3\n1 3\n2 2\n3 1\n", getOutput());
}

TEST_F(Solver432DTest, Example3)
{
    setInput("ABCDEFG");
    Solver432D().run();
    EXPECT_EQ("1\n7 1\n", getOutput());
}

TEST_F(Solver432DTest, Example4)
{
    setInput("CCB");
    Solver432D().run();
    EXPECT_EQ("1\n3 1\n", getOutput());
}

TEST_F(Solver432DTest, SameAsBruteForce)
{
    const int len = 5;
    const int allowedLettersCount = 3;
    string s(len, 'A');
    for (auto& c : s)
        c = 'A' + rand() % 3;

    setInput(s);
    Solver432D().run();
    auto out1 = getOutput();

    Solver432D().runBruteForce(s);
    EXPECT_EQ(out1 + out1, getOutput()) << s;
}