#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Residue.hpp"
#include "algo/SortWithMapping.hpp"
using namespace std;

class Solver645E
{
public:
    void run();
};

void Solver645E::run() {
    int nToAdd;
    int knownLetters;
    cin >> nToAdd >> knownLetters;
    string s;
    cin >> s;
    vector<CodeforcesResidue> dp;
    vector<CodeforcesResidue> sum = { 0, 1 };
    vector<int> lastEncounter(knownLetters);

    for (int i : range(int(s.length()))) {
        int ci = s[i] - 'a';
        dp.push_back(sum.back() - sum[lastEncounter[ci]]);
        sum.push_back(sum.back() + dp.back());
        lastEncounter[ci] = i + 1;
    }

    auto cp = lastEncounter;
    vector<size_t> mp;
    sortWithMappings(cp, nullptr, &mp);
    
    for (int i : range(nToAdd)) {
        int ci = mp[i % knownLetters];
        dp.push_back(sum.back() - sum[lastEncounter[ci]]);
        sum.push_back(sum.back() + dp.back());
        lastEncounter[ci] = s.length() + i + 1;
    }

    cout << sum.back();
}

class Solver645ETest : public ProblemTest {};

TEST_F(Solver645ETest, Example1)
{
    string input = R"(1 10
ac
)";
    string output = R"(8
)";
    output.pop_back();
    setInput(input);
    Solver645E().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver645ETest, Example2)
{
    string input = R"(0 2
aaba
)";
    string output = R"(10
)";
    output.pop_back();
    setInput(input);
    Solver645E().run();
    EXPECT_EQ(output, getOutput());
}
