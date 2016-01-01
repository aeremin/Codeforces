#include <Solvers/pch.h>
#include "algo/Residue.hpp"

using namespace std;

class Solver568B
{
public:
    void run();
};

void Solver568B::run()
{
    size_t n;
    cin >> n;
    vector<vector<CodeforcesResidue>> equivalenceRelationsCount(n + 1, vector<CodeforcesResidue>(n + 1, 0));
    equivalenceRelationsCount[0][0] = 1;
    for (int nElements = 1; nElements <= n; ++nElements)
    {
        equivalenceRelationsCount[nElements][1] = 1;
        equivalenceRelationsCount[nElements][nElements] = 1;
        for (int nEquivClasses = 2; nEquivClasses < nElements; ++nEquivClasses)
            equivalenceRelationsCount[nElements][nEquivClasses] = equivalenceRelationsCount[nElements - 1][nEquivClasses - 1] * 1 +
                                                                  equivalenceRelationsCount[nElements - 1][nEquivClasses] * nEquivClasses;
    }

    vector<CodeforcesResidue> totalEquivalenceRelationsCount(n + 1, 0);
    for (int nElements = 0; nElements <= n; ++nElements)
        totalEquivalenceRelationsCount[nElements] = accumulate(begin(equivalenceRelationsCount[nElements]), end(equivalenceRelationsCount[nElements]), CodeforcesResidue(0));

    vector<CodeforcesResidue> C_n_ = { 1 };
    for (int k = 1; k <= n; ++k)
    {
        C_n_.push_back(C_n_.back());
        C_n_.back() *= (n - k + 1);
        C_n_.back() *= CodeforcesResidue(k).inversed();
    }

    CodeforcesResidue ans = 0;
    for (int badElements = 1; badElements <= n; ++badElements)
        ans += C_n_[badElements] * totalEquivalenceRelationsCount[n - badElements];

    cout << ans.rep();
}

class Solver568BTest : public ProblemTest
{
};

TEST_F( Solver568BTest, Example1 )
{
    setInput("1");
    Solver568B().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver568BTest, Example2 )
{
    setInput("2");
    Solver568B().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver568BTest, Example3)
{
    setInput("3");
    Solver568B().run();
    EXPECT_EQ("10", getOutput());
}