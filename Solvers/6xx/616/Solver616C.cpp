#include <Solvers/pch.h>
#include "algo/DisjointSet.hpp"

using namespace std;

class Solver616C
{
public:
    void run();

    int h, w;
    int ind(int x, int y)
    {
        return x + w * y;
    }

    bool valid(int x, int y)
    {
        return (x >= 0 && x < w && y >= 0 && y < h);
    }
};

void Solver616C::run()
{

    cin >> h >> w;
    vector<string> field(h);
    string t;
    getline(cin, t);
    for (auto& s : field)
        getline(cin, s);

    DisjointSet ds(h * w);
    for (int x = 0; x < w; ++x)
        for (int y = 0; y < h; ++y)
            if (field[y][x] == '.')
            {
                if (y > 0 && field[y - 1][x] == '.')
                    ds.unionSets(ind(x, y), ind(x, y - 1));
                if (x > 0 && field[y][x - 1] == '.')
                    ds.unionSets(ind(x, y), ind(x - 1, y));
            }

    vector<int> componentSize(h * w, 0);
    for (int x = 0; x < w; ++x)
        for (int y = 0; y < h; ++y)
            if (field[y][x] == '.')
                ++componentSize[ds.rep(ind(x, y))];

    vector<pair<int, int>> offsets = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    unordered_map<int, int> neighborhood;
    for (int x = 0; x < w; ++x)
        for (int y = 0; y < h; ++y)
            if (field[y][x] == '*')
            {
                neighborhood.clear();
                for (auto& offs : offsets)
                {
                    auto xx = x + offs.first;
                    auto yy = y + offs.second;
                    if (valid(xx, yy))
                        neighborhood[ds.rep(ind(xx, yy))] = componentSize[ds.rep(ind(xx, yy))];
                }
                int currAns = 1;
                for (auto& p : neighborhood)
                    currAns += p.second;

                field[y][x] = '0' + (currAns % 10);
            }

    for (auto& s : field)
        cout << s << '\n';
}

class Solver616CTest : public ProblemTest
{
};

TEST_F( Solver616CTest, Example1 )
{
    setInput(R"(
3 3
*.*
.*.
*.*)");
    Solver616C().run();
    string expected = 
        R"(3.3
.5.
3.3
)";
    EXPECT_EQ(expected, getOutput());
}

TEST_F(Solver616CTest, Example2)
{
    setInput(R"(
4 5
**..*
..***
.*.*.
*.*.*)");
    Solver616C().run();
    string expected =
        R"(46..3
..732
.6.4.
5.4.3
)";
    EXPECT_EQ(expected, getOutput());
}
