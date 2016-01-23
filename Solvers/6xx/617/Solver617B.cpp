#include <Solvers/pch.h>

using namespace std;

class Solver621B
{
public:
    void run();
};

void Solver621B::run()
{
    int n;
    cin >> n;
    uint64_t res = 1;
    int prevNut = -1;
    for (int i = 0; i < n; ++i)
    {
        int c;
        cin >> c;
        if (c == 1)
        {
            if (prevNut >= 0)
            {
                res *= (i - prevNut);
            }
            prevNut = i;
        }
    }
    cout << ((prevNut == -1) ? 0 : res);
}

class Solver621BTest : public ProblemTest
{
};

TEST_F( Solver621BTest, Example1 )
{
    setInput("3             0 1 0");
    Solver621B().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver621BTest, Example2 )
{
    setInput("5                          1 0 1 0 1");
    Solver621B().run();
    EXPECT_EQ("4", getOutput());
}

TEST_F(Solver621BTest, NoNuts)
{
    setInput("5                          0 0 0 0 0");
    Solver621B().run();
    EXPECT_EQ("0", getOutput());
}