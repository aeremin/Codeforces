#include <Solvers/pch.h>
#include "iter/range.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/596/problem/C
class Solver596C
{
public:
    void run();
};

void Solver596C::run()
{
    int n;
    cin >> n;
    unordered_map<int, map<pair<int, int>, int>> bucketedPoints;
    for (int i : range(n)) {
        int x, y;
        cin >> x >> y;
        bucketedPoints[y - x][{x, y}] = 0;
    }

    map<int, vector<int>> val;

    for (int i : range(n)) {
        int w;
        cin >> w;
        val[w].push_back(i);
    }

    for (auto& p : val) {
        int bucket = p.first;
        auto& bucketVals = p.second;
        auto& bucketPts = bucketedPoints[bucket];
        if (bucketVals.size() != bucketPts.size()) {
            cout << "NO";
            return;
        }
        auto it = begin(bucketPts);
        for (auto w : bucketVals) {
            it->second = w;
            ++it;
        }
    }

    vector<pair<int, int>> ans(n);
    for (auto& p : bucketedPoints) {
        for (auto pt : p.second) {
            int bucket = p.first;
            int val = pt.second;
            ans[val] = pt.first;
            pair<int, int> neiRight = { pt.first.first + 1, pt.first.second };
            pair<int, int> neiUp = { pt.first.first, pt.first.second + 1};
            bool isInvalid = false;
            isInvalid = isInvalid || (bucketedPoints.count(bucket - 1) && 
                                      bucketedPoints[bucket - 1].count(neiRight) && 
                                      bucketedPoints[bucket - 1][neiRight] <= val);
            isInvalid = isInvalid || (bucketedPoints.count(bucket + 1) && 
                                      bucketedPoints[bucket + 1].count(neiUp) && 
                                      bucketedPoints[bucket + 1][neiUp]    <= val);
            if (isInvalid) {
                cout << "NO";
                return;
            }
        }
    }

    cout << "YES\n";
    for (auto pt : ans)
        cout << pt.first << " " << pt.second << "\n";

}

class Solver596CTest : public ProblemTest
{
};

TEST_F( Solver596CTest, Example1 )
{
    setInput("5   2 0  0 0  1 0  1 1  0 1   0 -1 -2 1 0");
    Solver596C().run();
    EXPECT_EQ("YES\n0 0\n1 0\n2 0\n0 1\n1 1\n", getOutput());
}

TEST_F( Solver596CTest, Example2 )
{
    setInput("3   1 0  0 0  2 0   0 1 2");
    Solver596C().run();
    EXPECT_EQ("NO", getOutput());
}

TEST_F(Solver596CTest, Example3) {
    setInput("2   0 0  0 1   1 0");
    Solver596C().run();
    EXPECT_EQ("NO", getOutput());
}

