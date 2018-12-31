#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"
#include "algo/io/readvector.hpp"

using namespace std;

class Solver576C
{
public:
    void run();
};

void Solver576C::run()
{
    int n;
    cin >> n;
    auto pts = readVector<GeomVector2I>(n);
    vector<vector<pair<GeomVector2I, int>>> buckets(1001);
    for (int i = 0; i < n; ++i)
    {
        auto pt = pts[i];
        buckets[pt[1] / 1000].push_back({ pt, i + 1});
    }

    for (auto& b : buckets)
        sort(begin(b), end(b));

    for (int i = 0; i < buckets.size(); ++i)
        if (i % 2 == 0)
            for (int j = 0; j < buckets[i].size(); ++j)
                cout << buckets[i][j].second << " ";
        else
            for (int j = 0; j < buckets[i].size(); ++j)
                cout << buckets[i][buckets[i].size() - 1 - j].second << " ";
}

class Solver576CTest : public ProblemTest {};

TEST_F(Solver576CTest, Example1)
{
    string input = R"(5
0 7
8 10
3 4
5 0
9 12
)";
    string output = R"(1 3 4 2 5 
)";
    setInput(input);
    Solver576C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


