#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"

using namespace std;

class Solver611D
{
public:
    void run();

    string seq;

    vector<vector<int>> compareCache;
    
    int firstLesserDigit(int start1, int start2)
    {
        int len = start2 - start1;
        if (compareCache[start1][start2] != -2)
            return compareCache[start1][start2];

        if (start2 + len == seq.length())
        {
            int res = -1;
            for (int offs = 0; offs < len; ++offs)
            {
                if (seq[start1 + offs] > seq[start2 + offs])
                    break;
                
                if (seq[start1 + offs] < seq[start2 + offs])
                {
                    res = start1 + offs;
                    break;
                }
            }
            compareCache[start1][start2] = res;
            return res;
        }

        if (seq[start1] < seq[start2])
            return start1;

        if (seq[start1] > seq[start2])
            return -1;

        int ansForShifted = firstLesserDigit(start1 + 1, start2 + 1);
        if (ansForShifted == start1 + len)
            ansForShifted = -1;
        compareCache[start1][start2] = ansForShifted;
        return ansForShifted;
    }
};

void Solver611D::run()
{
    int n;
    cin >> n;
    cin >> seq;

    compareCache = vector<vector<int>>(seq.length(), vector<int>(seq.length(), -2));

    vector<vector<CodeforcesResidue>> a(n, vector<CodeforcesResidue>(n + 1, 0));
    vector<vector<CodeforcesResidue>> s(n + 1, vector<CodeforcesResidue>(n + 1, 0));
    a[0][1] = 1;
    s[0][1] = 0;
    s[1][1] = 1;
    for (int j = 2; j <= n; ++j)
    {
        s[0][j] = 0;
        for (int i = 0; i < j; ++i)
        {
            if (i == 0)
            {
                a[i][j] = 1;
            }
            else
            {
                int p = i - (j - i);
                if (p >= 0)
                {
                    int k = (seq[p] != '0' && firstLesserDigit(p, i) != -1) ? 1 : 0;
                    a[i][j] += a[p][i] * k;
                }
                auto m = max(0, 2 * i + 1 - j);
                if (seq[i] != '0')
                    a[i][j] += s[i][i] - s[m][i];
            }
            s[i + 1][j] = s[i][j] + a[i][j];
        }
    }

    CodeforcesResidue ans = 0;
    for (int i = 0; i < n; ++i) ans += a[i][n];

    cout << ans;
}

class Solver611DTest : public ProblemTest
{
};

TEST_F( Solver611DTest, Example1 )
{
    setInput("6        123434");
    Solver611D().run();
    EXPECT_EQ("8", getOutput());
}

TEST_F( Solver611DTest, Example2 )
{
    setInput("8        20152016");
    Solver611D().run();
    EXPECT_EQ("4", getOutput());
}

TEST_F(Solver611DTest, Example3)
{
    string s(5000, '1');
    setInput("5000\n" + s);
    Solver611D().run();
}

TEST_F(Solver611DTest, Example4)
{
    setInput("10        5558403946");
    Solver611D().run();
    EXPECT_EQ("11", getOutput());
}

