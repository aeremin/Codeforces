#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/321/problem/B
class Solver321B
{
public:
    void run();

    bool canBeat(const multiset<int>& attackers, const multiset<int>& defenders)
    {
        auto it1 = attackers.rbegin();
        auto it2 = defenders.rbegin();
        while (it2 != defenders.rend())
        {
            if (*it2 > *it1)
                return false;
            ++it1;
            ++it2;
        }
        return true;
    }
};

void Solver321B::run()
{
    int nDefenders, nAttackers;
    cin >> nDefenders >> nAttackers;
    multiset<int> goodDefenders, badDefenders, attackers;
    for (int i = 0; i < nDefenders; ++i)
    {
        string s;
        int power;
        cin >> s >> power;
        if (s == "DEF")
            goodDefenders.insert(power);
        else
            badDefenders.insert(power);
    }

    for (int i = 0; i < nAttackers; ++i)
    {
        int power;
        cin >> power;
        attackers.insert(power);
    }

    int maxDamage = 0;

    auto itAttackers = attackers.rbegin();
    auto itDefenders = begin(badDefenders);
    int totalAttack = 0;
    int totalDefence = 0;
    multiset<int> subDefenders, subAttackers;
    while (itAttackers != attackers.rend() && itDefenders != end(badDefenders))
    {
        auto currDef = *itDefenders;
        auto curAtk = *itAttackers;
        totalAttack += curAtk;
        totalDefence += currDef;
        subDefenders.insert(currDef);
        subAttackers.insert(curAtk);
        if (canBeat(subAttackers, subDefenders))
            maxDamage = max(maxDamage, totalAttack - totalDefence);
        else
            break;
        ++itAttackers;
        ++itDefenders;
    }

    subAttackers = attackers;
    bool canKillAllGoodDefenders = true;
    for (auto& p : goodDefenders)
    {
        auto it = subAttackers.upper_bound(p);
        if (it == end(subAttackers))
        {
            canKillAllGoodDefenders = false;
            break;
        }
        else
            subAttackers.erase(it);
    }

    if (canKillAllGoodDefenders && canBeat(subAttackers, badDefenders))
        maxDamage = max(maxDamage, accumulate(begin(subAttackers), end(subAttackers), 0)
        - accumulate(begin(badDefenders), end(badDefenders), 0));
    cout << maxDamage;
}

class Solver321BTest : public ProblemTest
{
};

TEST_F( Solver321BTest, Example1 )
{
    setInput("2 3        ATK 2000        DEF 1700        2500        2500        2500");
    Solver321B().run();
    EXPECT_EQ("3000", getOutput());
}

TEST_F( Solver321BTest, Example2 )
{
    setInput("3 4        ATK 10        ATK 100        ATK 1000        1        11        101        1001");
    Solver321B().run();
    EXPECT_EQ("992", getOutput());
}

TEST_F(Solver321BTest, Example3)
{
    setInput("2 4        DEF 0        ATK 0        0        0        1        1");
    Solver321B().run();
    EXPECT_EQ("1", getOutput());
}