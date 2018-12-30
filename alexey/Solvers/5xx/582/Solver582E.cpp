#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"
#include "algo/BinaryCubePrefix.h"

using namespace std;

class Solver582E
{
public:
    void run();

    tuple<string, char, string> decomposeExpression(const string& expression)
    {
        int bracketBalance = 0;
        for (size_t i = 0; i < expression.length(); ++i)
        {
            if (expression[i] == '(')
                bracketBalance++;
            else if (expression[i] == ')')
                bracketBalance--;

            if (bracketBalance == 0)
                return make_tuple(expression.substr(1, i - 1), expression[i + 1], expression.substr(i + 3, expression.length() - i - 4));
        }
    }

    static constexpr uint64_t nPossibleInputs = 1 << 4;
    static constexpr uint64_t nPossibleFunctions = 1 << nPossibleInputs;
    
    using PossibleFunctionsCount = array<CodeforcesResidue64, nPossibleFunctions>;

    PossibleFunctionsCount orOp(PossibleFunctionsCount lh, PossibleFunctionsCount rh)
    {
        auto lhPrefixSums = calculatePrefixSums<CodeforcesResidue64, nPossibleInputs>(move(lh));
        auto rhPrefixSums = calculatePrefixSums<CodeforcesResidue64, nPossibleInputs>(move(rh));
        PossibleFunctionsCount resultPrefixSums;
        for (uint64_t i = 0; i < nPossibleFunctions; ++i)
            resultPrefixSums[i] = lhPrefixSums[i] * rhPrefixSums[i];
        return calculateValuesByPrefixSums<CodeforcesResidue64, nPossibleInputs>(move(resultPrefixSums));
    }

    void reverse(PossibleFunctionsCount& a)
    {
        std::reverse(begin(a), end(a));
    }
    
    PossibleFunctionsCount andOp(PossibleFunctionsCount lh, PossibleFunctionsCount rh)
    {
        reverse(lh);
        reverse(rh);
        auto inversedResult = orOp(lh, rh);
        reverse(inversedResult);
        return inversedResult;
    }

    PossibleFunctionsCount applyOperator(char op, PossibleFunctionsCount lh, PossibleFunctionsCount rh)
    {
        return (op == '|') ? orOp (lh, rh) : andOp(lh, rh);
    }
    
    PossibleFunctionsCount getNumberOfPossibilitiesFor(const string& expession)
    {
        array<CodeforcesResidue64, nPossibleFunctions> result;
        if (expession.length() == 1) // single variable or its inversion
        {
            vector<pair<int, bool>> variablePossibilies;
            if (expession == "?")
                variablePossibilies = { {0, false}, {1, false}, {2, false}, {3, false}, { 0, true },{ 1, true },{ 2, true },{ 3, true } };
            else
                if (expession >= "A" && expession <= "D")
                    variablePossibilies = { {expession[0] - 'A', true } };
                else
                    variablePossibilies = { { expession[0] - 'a', false } };

            for (auto p : variablePossibilies)
            {
                uint64_t functionDescription = 0;
                for (uint64_t input = 0; input < nPossibleInputs; ++input)
                    if (((input & (1 << p.first)) > 0) == p.second)
                        functionDescription += (1 << input);
                
                functionDescription += 0;

                result[functionDescription]++;
            }
        }
        else
        {
            auto decomposition = decomposeExpression(expession);
            auto lhPossibilities = getNumberOfPossibilitiesFor(get<0>(decomposition));
            auto rhPossibilities = getNumberOfPossibilitiesFor(get<2>(decomposition));
            auto operatorSymbol = get<1>(decomposition);
            vector<char> operatorPossibilites;
            if (operatorSymbol == '?')
                operatorPossibilites = { '|', '&' };
            else
                operatorPossibilites = { operatorSymbol };

            for (auto op : operatorPossibilites)
            {
                auto countsForOp = applyOperator(op, lhPossibilities, rhPossibilities);
                for (uint64_t fn = 0; fn < nPossibleFunctions; ++fn)
                    result[fn] += countsForOp[fn];
            }
        }
        return result;
    }
};

void Solver582E::run()
{
    string expression;
    cin >> expression;

    int nKnownResults;
    cin >> nKnownResults;

    vector<pair<int, int>> knownResults(nKnownResults);
    for (auto& p : knownResults)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d >> p.second;
        p.first = a + 2 * b + 4 * c + 8 * d;
    }

    auto possibilitiesCounts = getNumberOfPossibilitiesFor(expression);
    CodeforcesResidue64 ans = 0;
    for (uint64_t fn = 0; fn < nPossibleFunctions; ++fn)
    {
        auto fnHasProperValueOn = [&](pair<int, int> p) {return ((fn & (1 << p.first)) == p.second * (1 << p.first)); };
        bool fnIsAcceptable = all_of(begin(knownResults), end(knownResults), fnHasProperValueOn);
        if (fnIsAcceptable && !(possibilitiesCounts[fn] == CodeforcesResidue64(0)))
            ans += possibilitiesCounts[fn];
    }

    cout << ans;
}

// Tests below need a lot of stack memory to succeed.
// If you see them failing, make sure to set Stack Reserve Size
// (codeforces project Properties -> Linker -> System -> Stack Reserve Size)
// to 256000000 (256mb, value used on Codeforces servers: https://codeforces.com/blog/entry/47003?#comment-313808)

class Solver582ETest : public ProblemTest
{
};

TEST_F( Solver582ETest, Example1 )
{
    setInput("?        2        1 0 1 0 1        0 1 1 0 1");
    Solver582E().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F( Solver582ETest, Example2 )
{
    setInput("(A)?(?)     1        1 1 0 0 0");
    Solver582E().run();
    EXPECT_EQ("4", getOutput());
}

TEST_F(Solver582ETest, Example3)
{
    setInput("((?)&(?))|((?)&(?))     0");
    Solver582E().run();
    EXPECT_EQ("4096", getOutput());
}

TEST_F(Solver582ETest, Example4)
{
    setInput("b        1        1 0 1 1 1");
    Solver582E().run();
    EXPECT_EQ("1", getOutput());
}
