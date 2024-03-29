#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/377/problem/C
class Solver377C {
public:
    void run();

    int nActions;
    vector<pair<char, int>> actions;
    vector<int> powers;

    int teamToSign(int t) {
        return 3 - 2 * t;
    }

    unordered_map<uint32_t, int> ansCache;
    
    int ans(uint32_t heroesMask, int actI) {
        if (actI == nActions)
            return 0;

        auto itCache = ansCache.find(heroesMask);
        if (itCache != end(ansCache))
            return itCache->second;

        auto teamSign = teamToSign(actions[actI].second);

        if (actions[actI].first == 'p')
            for (int iPick : range(nActions))
                if (heroesMask & (1 << iPick)) {
                    int res = ans(heroesMask ^ (1 << iPick), actI + 1)
                        + teamSign * powers[iPick];
                    ansCache[heroesMask] = res;
                    return res;
                }

        assert(actions[actI].first == 'b');
        int res = numeric_limits<int>::min();
        for (int iBan : range(nActions))
            if (heroesMask & (1 << iBan))
                relax_max(res, teamSign * ans(heroesMask ^ (1 << iBan), actI + 1));

        res *= teamSign;
        ansCache[heroesMask] = res;
        return res;
    }
};

void Solver377C::run() {
    int nHeroes;
    cin >> nHeroes;
    powers = readVector<int>(nHeroes);
    sort(powers.rbegin(), powers.rend());

    cin >> nActions;
    actions = vector<pair<char, int>>(nActions);

    for (auto& a : actions)
        cin >> a.first >> a.second;

    cout << ans((1 << nActions) - 1, 0);
}

class Solver377CTest : public ProblemTest {};

TEST_F(Solver377CTest, Example1)
{
    string input = R"(2
2 1
2
p 1
p 2
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver377C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377CTest, Example2)
{
    string input = R"(6
6 4 5 4 5 5
4
b 2
p 1
b 1
p 2
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver377C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377CTest, Example3)
{
    string input = R"(4
1 2 3 4
4
p 2
b 2
p 1
b 1
)";
    string output = R"(-2
)";
    output.pop_back();
    setInput(input);
    Solver377C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


