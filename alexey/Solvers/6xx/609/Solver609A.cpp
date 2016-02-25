#include "Solvers/pch.h"
#include <algorithm>
#include <utility>

using namespace std;

class Solver609A
{
public:
    void run();
};

void Solver609A::run()
{
    int n;
    cin >> n;
    vector<pair<int, int>> beacons(n);
    for (auto& p : beacons) cin >> p.first >> p.second;
    sort(begin(beacons), end(beacons));
    vector<int> numAlive;
    for (int i = 0; i < n; ++i)
    {
        auto left = beacons[i].first - beacons[i].second;
        auto it = lower_bound(begin(beacons), end(beacons), make_pair( left, 0 ));
        int res = 0;
        if (it == begin(beacons))
            res = 1;
        else
            res = numAlive[it - begin(beacons) - 1] + 1;
        numAlive.push_back(res);
    }

    auto maxIt = max_element(begin(numAlive), end(numAlive));
    cout << (n - *maxIt);
}

class Solver609ATest : public ProblemTest {};

TEST_F(Solver609ATest, Example1)
{
    setInput("4        1 9        3 1        6 1        7 4");
    Solver609A().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F(Solver609ATest, Example2)
{
    setInput("7        1 1        2 1        3 1        4 1        5 1        6 1        7 1");
    Solver609A().run();
    EXPECT_EQ("3", getOutput());
}