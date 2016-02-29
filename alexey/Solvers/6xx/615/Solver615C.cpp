#include <Solvers/pch.h>
#include "algo/strings/KnuttMorrisPratt.hpp"

using namespace std;

class Solver615C
{
public:
    void run();
};

void Solver615C::run()
{
    string inShop, needToBuild;
    cin >> inShop >> needToBuild;
    inShop = inShop + "!" + inShop;
    reverse_copy(begin(inShop), begin(inShop) + inShop.length() / 2, begin(inShop) + inShop.length() / 2 + 1);
    vector<pair<int, int>> ans;
    int buildIter = 0;
    while (buildIter < needToBuild.length())
    {
        auto prefixString = needToBuild.substr(buildIter, string::npos) + ":";
        string t = prefixString + inShop;
        auto pi = calc_prefix_function(t);
        auto maxLenIter = max_element(begin(pi) + prefixString.length(), end(pi));
        int maxLen = *maxLenIter;
        if (maxLen == 0)
        {
            cout << -1;
            return;
        }
        int indexInShopString = maxLenIter - begin(pi) - prefixString.length();
        if (indexInShopString > inShop.length() / 2)
            ans.emplace_back(inShop.length() - indexInShopString + maxLen - 1, inShop.length() - indexInShopString);
        else
            ans.emplace_back(indexInShopString - maxLen + 2, indexInShopString + 1);

        buildIter += maxLen;
    }

    cout << ans.size() << "\n";
    for (auto& p : ans)
        cout << p.first << " " << p.second << "\n";
}

class Solver615CTest : public ProblemTest
{
};

TEST_F( Solver615CTest, Example1 )
{
    setInput("abc cbaabc");
    Solver615C().run();
    EXPECT_EQ("2\n3 1\n1 3\n", getOutput());
}

TEST_F( Solver615CTest, Example2 )
{
    setInput("aaabrytaaa ayrat");
    Solver615C().run();
    EXPECT_EQ("3\n1 1\n6 5\n8 7\n", getOutput());
}

TEST_F(Solver615CTest, Example3)
{
    setInput("ami no");
    Solver615C().run();
    EXPECT_EQ("-1", getOutput());
}
