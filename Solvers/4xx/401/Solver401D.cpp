#include <Solvers/pch.h>

using namespace std;

class Solver401D
{
public:
    void run();
};

void Solver401D::run()
{
    string n;
    int mod;
    cin >> n >> mod;
    int endMask = 1 << n.length();
    vector<vector<int64_t>> residueDistribution(endMask, vector<int64_t>(mod));

    vector<vector<int>> digitPositions(10);
    for (int i = 0; i < n.length(); ++i)
        digitPositions[n[i] - '0'].push_back(i);
    
    residueDistribution[0][0] = 1;
    for (int mask = 1; mask < endMask; ++mask)
        for (int d = 0; d < 10; ++d)
            for (int i : digitPositions[d])
                if (mask & (1 << i))
                {
                    int d = n[i] - '0';
                    if (mask == (1 << i) && d == 0)
                        break;

                    for (int r = 0; r < mod; ++r)
                        residueDistribution[mask][(r * 10 + d) % mod] += residueDistribution[mask ^ (1 << i)][r];
                    break;
                }


    cout << residueDistribution[endMask - 1][0];
}

class Solver401DTest : public ProblemTest
{
};

TEST_F( Solver401DTest, Example1 )
{
    setInput("104 2");
    Solver401D().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F( Solver401DTest, Example2 )
{
    setInput("223 4");
    Solver401D().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver401DTest, Example3)
{
    setInput("7067678 8");
    Solver401D().run();
    EXPECT_EQ("47", getOutput());
}
