#include <Solvers/pch.h>

using namespace std;

class Solver620B
{
public:
    void run();
};

void Solver620B::run()
{
    vector<int64_t> segmentCount = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };
    int64_t ans = 0;
    int64_t a, b;
    cin >> a >> b;
    for ( auto i = a; i <= b; ++i )
    {
        auto ii = i;
        while ( ii > 0 )
        {
            ans += segmentCount[ii % 10];
            ii /= 10;
        }
    }
    cout << ans;
}

class Solver620BTest : public ProblemTest
{
};

TEST_F( Solver620BTest, Example1 )
{
    setInput("1 3");
    Solver620B().run();
    EXPECT_EQ("12", getOutput());
}

TEST_F( Solver620BTest, Example2 )
{
    setInput("10 15");
    Solver620B().run();
    EXPECT_EQ("39", getOutput());
}