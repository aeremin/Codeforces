#include <Solvers/pch.h>

using namespace std;

class Solver597B
{
public:
    void run();
};

void Solver597B::run()
{
    int nOrders;
    cin >> nOrders;
    vector<pair<int, int>> orders(nOrders);
    for (auto& p : orders)
        cin >> p.second >> p.first;

    sort(begin(orders), end(orders));

    int lastAcceptedOrderFinishTime = numeric_limits<int>::min();
    int ans = 0;
    for (auto& p : orders)
    {
        if (p.second > lastAcceptedOrderFinishTime)
        {
            ++ans;
            lastAcceptedOrderFinishTime = p.first;
        }
    }

    cout << ans;
}

class Solver597BTest : public ProblemTest
{
};

TEST_F( Solver597BTest, Example1 )
{
    setInput("2        7 11        4 7");
    Solver597B().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver597BTest, Example2 )
{
    setInput("5        1 2        2 3        3 4        4 5        5 6");
    Solver597B().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F(Solver597BTest, Example3)
{
    setInput("6        4 8        1 5        4 7        2 5        1 3        6 8");
    Solver597B().run();
    EXPECT_EQ("2", getOutput());
}