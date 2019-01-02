#include "Solvers/pch.h"

// Solution for Codeforces problem http://codeforces.com/contest/579/problem/B
class Solver579B
{
public:
    void run();
};

struct TeamData
{
    int n1, n2;
    int strength;
};

void Solver579B::run()
{
    int nTeams;
    cin >> nTeams;

    std::vector<TeamData> teamData;
    for (int line = 2; line <= 2 * nTeams; ++line)
    {
        for (int i = 1; i < line; ++i)
        {
            int str;
            cin >> str;
            teamData.push_back({ line, i, str });
        }
    }

    std::sort(begin(teamData), end(teamData), [](const TeamData& td1, const TeamData& td2)
    {
        return td1.strength < td2.strength;
    });

    std::vector<int> teamedTo(2 * nTeams + 1, 0);
    while (!teamData.empty())
    {
        auto bestMatch = teamData.back();
        teamData.pop_back();
        if (!teamedTo[bestMatch.n1] && !teamedTo[bestMatch.n2])
        {
            teamedTo[bestMatch.n1] = bestMatch.n2;
            teamedTo[bestMatch.n2] = bestMatch.n1;
        }
    }

    for (int i = 1; i <= 2 * nTeams; ++i)
        cout << teamedTo[i] << " ";
}

class Solver579BTest : public ProblemTest {};

TEST_F(Solver579BTest, Example1)
{
    setInput("2        6        1 2        3 4 5");
    Solver579B().run();
    EXPECT_EQ("2 1 4 3 ", getOutput());
}

TEST_F(Solver579BTest, Example2)
{
    setInput("3        487060        3831 161856        845957 794650 976977        83847 50566 691206 498447        698377 156232 59015 382455 626960");
    Solver579B().run();
    EXPECT_EQ("6 5 4 3 2 1 ", getOutput());
}