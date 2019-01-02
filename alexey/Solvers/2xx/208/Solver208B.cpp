#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/208/problem/B
class Solver208B
{
public:
    void run();
};

void Solver208B::run()
{
    size_t nCards;
    cin >> nCards;
    string cards = "xxxx";
    for (size_t i = 0; i < nCards; ++i)
    {
        string card;
        cin >> card;
        cards.append(card);
    }
    nCards += 2;

    unordered_set<string> allowedSuffixes = { cards.substr(cards.length() - 6, 6) };
    for (int i = nCards - 4; i >= 0; --i)
    {
        unordered_set<string> nextAllowedSuffixes;
        for (auto& suff : allowedSuffixes)
        {
            if (suff[2] == suff[4] || suff[3] == suff[5])
                nextAllowedSuffixes.insert(cards.substr(2 * i, 2) + suff.substr(0, 2) + suff.substr(4, 2));

            if (cards[2 * i] == suff[4] || cards[2 * i + 1] == suff[5])
                nextAllowedSuffixes.insert(suff.substr(4, 2) + suff.substr(0, 4));
        }
        allowedSuffixes = move(nextAllowedSuffixes);
    }

    if (allowedSuffixes.empty())
        cout << "NO";
    else
        cout << "YES";
}

class Solver208BTest : public ProblemTest
{
};

TEST_F( Solver208BTest, Example1 )
{
    setInput("4\n2S 2S 2C 2C");
    Solver208B().run();
    EXPECT_EQ("YES", getOutput());
}

TEST_F( Solver208BTest, Example2 )
{
    setInput("2\n3S 2C");
    Solver208B().run();
    EXPECT_EQ("NO", getOutput());
}

TEST_F(Solver208BTest, OneCard)
{
    setInput("1\n3S");
    Solver208B().run();
    EXPECT_EQ("YES", getOutput());
}

TEST_F(Solver208BTest, TwoCompatibleCards)
{
    setInput("2\n3S 3C");
    Solver208B().run();
    EXPECT_EQ("YES", getOutput());
}
