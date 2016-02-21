#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/Relax.hpp"
#include "algo/numbertheory/Residue.hpp"
using namespace std;

class Solver629C
{
public:
    void run();
};

void Solver629C::run()
{
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int toAdd = n - m;
    vector<vector<CodeforcesResidue64>> cnt = {vector<CodeforcesResidue64>(toAdd + 1, 0)};
    cnt.front().front() = 1;
    for (int i : range(1, toAdd + 1))
    {
        cnt.push_back(vector<CodeforcesResidue64>(toAdd + 1, 0));
        for (int j : range(toAdd + 1))
        {
            if (j > 0)
                cnt[i][j] += cnt[i - 1][j - 1];
            if (j < toAdd)
                cnt[i][j] += cnt[i - 1][j + 1];
        }
    }
    
    
    int lowestDisbalance = 0;
    int totalDisbalance = 0;
    for (auto c : s)
    {
        if (c == '(')
            totalDisbalance++;
        else
            totalDisbalance--;
        relaxMin(lowestDisbalance, totalDisbalance);
    }
    
    CodeforcesResidue64 ans = 0;
    for (int addL : range(toAdd + 1))
    {
        int addR = toAdd - addL;
        for (int disbL : range(-lowestDisbalance, toAdd + 1))
        {
            int disbR = totalDisbalance + disbL;
            if (disbR >= 0 && disbR <= toAdd)
                ans += cnt[addL][disbL] * cnt[addR][disbR];
        }
    }
    cout << ans;
}

class Solver629CTest : public ProblemTest {};

TEST_F(Solver629CTest, Example1)
{
    string input = R"(4 1
(
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver629C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver629CTest, Example2)
{
    string input = R"(4 4
(())
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver629C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver629CTest, Example3)
{
    string input = R"(4 3
(((
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver629C().run();
    EXPECT_EQ(output, getOutput());
}


