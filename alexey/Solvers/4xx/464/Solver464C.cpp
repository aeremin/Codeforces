#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"

using namespace std;

class Solver464C
{
public:
    void run();

    struct PerDigitOperationResult
    {
        CodeforcesResidue64 number;
        CodeforcesResidue64 tenToNumberLenPower;
    };
};

void Solver464C::run()
{
    string startString;
    cin >> startString;
    int nSubstitutions;
    cin >> nSubstitutions;
    vector<pair<int, string>> substitutions;
    substitutions.push_back({ 0, startString });
    for (int i = 0; i < nSubstitutions; ++i)
    {
        string line;
        cin >> line;
        substitutions.push_back({ line[0] - '0', line.substr(3, string::npos) });
    }

    vector<PerDigitOperationResult> perDigitsResults(10);
    for (int d = 0; d < 10; ++d)
        perDigitsResults[d] = { d, 10 };

    for (int iSubstitution = substitutions.size() - 1; iSubstitution >= 0; --iSubstitution)
    {
        auto currDigit = substitutions[iSubstitution].first;
        auto s = substitutions[iSubstitution].second;
        PerDigitOperationResult res = { 0, 1 };
        for (int i = s.length() - 1; i >= 0; --i)
        {
            int d = s[i] - '0';
            res.number += perDigitsResults[d].number * res.tenToNumberLenPower;
            res.tenToNumberLenPower *= perDigitsResults[d].tenToNumberLenPower;
        }
        perDigitsResults[currDigit] = res;
    }

    cout << perDigitsResults[0].number;
}

class Solver464CTest : public ProblemTest
{
};

TEST_F( Solver464CTest, Example1 )
{
    setInput(
R"(
123123
1
2->00
)");
    Solver464C().run();
    EXPECT_EQ("10031003", getOutput());
}

TEST_F( Solver464CTest, Example2 )
{
    setInput(
R"(
123123
1
3->
)");
    Solver464C().run();
    EXPECT_EQ("1212", getOutput());
}

TEST_F( Solver464CTest, Example3 )
{
    setInput(
R"(
222
2
2->0
0->7
)");
    Solver464C().run();
    EXPECT_EQ("777", getOutput());
}

TEST_F( Solver464CTest, Example4 )
{
    setInput(
R"(
1000000008
0
)");
    Solver464C().run();
    EXPECT_EQ("1", getOutput());
}
