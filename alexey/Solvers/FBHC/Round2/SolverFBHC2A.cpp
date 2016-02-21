#include <Solvers/pch.h>
#include "util/relax.h"

using namespace std;

class SolverFBHC2A
{
public:
    void run();
    void runOneTest();
};

void SolverFBHC2A::run()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        cout << "Case #" << i << ": ";
        runOneTest();
        if (i != t) cout << "\n";
    }
}

void SolverFBHC2A::runOneTest()
{
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    vector<int> indOfDifference;
    vector<int> prefixColorCount = { 0 }, suffixColorCount = { 0 };
    unordered_set<char> prefixColors, suffixColors;
    for (int i = 0; i < n; ++i)
    {
        if (s1[i] != s2[i])
            indOfDifference.push_back(i);

        prefixColors.insert(s2[i]);
        suffixColors.insert(s2[n - 1 - i]);
        prefixColorCount.push_back(prefixColors.size());
        suffixColorCount.push_back(suffixColors.size());
    }

    if (indOfDifference.size() == 0)
    {
        cout << 0;
        return;
    }
    
    indOfDifference.push_back(n);

    int ans = 2 * n;
    for (int i = 0; i <= n; ++i)
    {
        int j = *upper_bound(begin(indOfDifference), end(indOfDifference), i - 1 );
        relax_min(ans, max(prefixColorCount[i], suffixColorCount[n - j]));
    }

    cout << ans;
}

class SolverFBHC2ATest : public FBHCProblemTest
{
public:
    SolverFBHC2ATest() : FBHCProblemTest("Inputs\\FBHC\\Round2\\A\\") {}
};

TEST_F(SolverFBHC2ATest, Example )
{
    SolverFBHC2A().run();
}

