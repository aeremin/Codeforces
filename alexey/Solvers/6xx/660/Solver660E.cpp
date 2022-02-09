#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/number_theory/residue.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/660/problem/E
class Solver660E
{
public:
    void run();
};

void Solver660E::run()
{
    int n, m;
    cin >> n >> m;
    vector<CodeforcesResidue64> c(n + 1);
    vector<CodeforcesResidue64> pows(n + 1);
    CodeforcesResidue64 cnk = 1;
    CodeforcesResidue64 pow = 1;
    CodeforcesResidue64 pow2 = 1;
    for (int i : range(n + 1)) {
        c[i] = cnk * pow;
        pows[i] = pow2;
        pow *= (m - 1);
        pow2 *= m;
        cnk *= n - i;
        cnk = cnk / int64_t(i + 1);
    }

    vector<CodeforcesResidue64> d;
    partial_sum(begin(c), end(c), back_inserter(d));

    CodeforcesResidue64 ans = 0;
    for (int i : range(n + 1))
        ans += d[i] * pows[n - i];
    
    cout << ans;

}

class Solver660ETest : public ProblemTest {};

TEST_F(Solver660ETest, Example1)
{
    string input = R"(1 3
)";
    string output = R"(6
)";
    setInput(input);
    Solver660E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver660ETest, Example2)
{
    string input = R"(2 2
)";
    string output = R"(14
)";
    setInput(input);
    Solver660E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver660ETest, Example3)
{
    string input = R"(3 3
)";
    string output = R"(174
)";
    setInput(input);
    Solver660E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


