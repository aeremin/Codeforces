#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/498/problem/B
class Solver498B
{
public:
    void run();

    double quickpow(double a, int d)
    {
        double res = 1.0;
        while (d > 0)
        {
            if (d % 2 == 0)
            {
                d /= 2;
                a *= a;
            }
            else
            {
                d--;
                res *= a;
            }
        }
        return res;
    }

    vector<vector<double>> PP, QQ;

    const double ALMOST_ONE = 1 - 1e-12;

    double getP(int a, int t)
    {
        if (t < 0)
            return 0;

        if (t == 0)
            return (a == 0) ? 1 : 0;

        if (a == 0)
            return 0;

        if (a > t)
            return 0;

        return PP[a][t - a];
    }

    double getQ(int a, int t)
    {
        if (t < 0)
            return 0;

        if (t == 0)
            return 0;

        if (a > t)
            return 0;

        return QQ[a][t - a];
    }
};

void Solver498B::run()
{
    int n, timeToPlay;

    cin >> n >> timeToPlay;

    n = min(n, timeToPlay);

    PP.resize(n + 1);
    QQ.resize(n + 1);
    vector<double> p(n + 1);
    vector<int> timeToGuess(n + 1);
    vector<double> pPowered(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int percent, ti;
        cin >> percent >> ti;
        if (percent == 100 || ti == 1)
        {
            p[i] = -1;
        }
        else
        {
            p[i] = (double)percent / 100.0;
            pPowered[i] = quickpow(1 - p[i], ti - 2);
        }
        timeToGuess[i] = ti;
    }


    PP[0].push_back(1);
    QQ[0].push_back(0);

    for (int t = 1; t <= timeToPlay; ++t)
    {
        for (int iSong = 1; iSong <= min(n, t); ++iSong)
        {
            if (p[iSong] < 0)
                PP[iSong].push_back(getP(iSong - 1, t - 1));
            else
            {
                QQ[iSong].push_back(
                    getP(iSong - 1, t - 1) + (1 - p[iSong]) * (getQ(iSong, t - 1) - pPowered[iSong] * getP(iSong - 1, t - timeToGuess[iSong])));
                PP[iSong].push_back(
                    p[iSong] * getQ(iSong, t) + getP(iSong - 1, t - timeToGuess[iSong]) * pPowered[iSong] * (1 - p[iSong]));
            }
        }

        if (n <= t)
            PP[n][t - n] += getP(n, t - 1);
    }

    double ev = 0;
    double fullprob = 0;
    for (int iSong = 1; iSong < n; ++iSong)
    {
        double prob;
        if (p[iSong + 1] < 0)
            prob = getP(iSong, timeToPlay);
        else
            prob = getP(iSong, timeToPlay) + (1 - p[iSong + 1]) * (getQ(iSong + 1, timeToPlay) - pPowered[iSong + 1] * getP(iSong, timeToPlay + 1 - timeToGuess[iSong + 1]) +
            getP(iSong, timeToPlay - timeToGuess[iSong + 1] + 1) * pPowered[iSong + 1]);
        fullprob += prob;
        ev += iSong * prob;
    }

    double prob = PP[n].back();
    fullprob += prob;
    ev += n * prob;

    cout << setprecision(9) << fixed << ev;
}

class Solver498BTest : public ProblemTest
{
};

TEST_F( Solver498BTest, Example1 )
{
    setInput("2 2        50 2        10 1");
    Solver498B().run();
    EXPECT_EQ("1.500000000", getOutput());
}

TEST_F( Solver498BTest, Example2 )
{
    setInput("2 2        0 2        100 2");
    Solver498B().run();
    EXPECT_EQ("1.000000000", getOutput());
}

TEST_F(Solver498BTest, Example3)
{
    setInput("3 3        50 3        50 2        25 2");
    Solver498B().run();
    EXPECT_EQ("1.687500000", getOutput());
}

TEST_F(Solver498BTest, Example4)
{
    setInput("2 2        0 2        0 2");
    Solver498B().run();
    EXPECT_EQ("1.000000000", getOutput());
}