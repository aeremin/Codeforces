#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/graph/Graph.hpp"
#include "algo/graph/Dijkstra.hpp"
#include "algo/SortWithMapping.hpp"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/377/problem/A
class Solver377A
{
public:
    void run();
    int h, w;
    int k;
    vector<string> field;

    int pack(int x, int y) {
        return x + y * w;
    }

    bool isValid(int x, int  y) {
        return x >= 0 && x < w && y >= 0 && y < h;
    }
};

void Solver377A::run() {
    cin >> h >> w;
    cin >> k;
    field = vector<string>(h);
    for (auto& s : field)
        cin >> s;

    vector<pair<int, int>> nei = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
    UndirectedGraph<int> g(h * w);
    
    int empty = -1;
    for (int y : range(h))
        for (int x : range(w)) {
            if (field[y][x] == '#') continue;
            for (auto nn : nei) {
                auto xx = x + nn.first;
                auto yy = y + nn.second;
                if (isValid(xx, yy) && field[yy][xx] == '.')
                    g.add_edge(pack(x, y), pack(xx, yy), 1);
            }
            empty = pack(x, y);
        }

    auto dr = getMinimalPathsFrom(g, empty, -1);
    vector<size_t> revM;
    sortWithMappings(dr.minimalDistances, nullptr, &revM);

    for (int i : range(k)) {
        int ind = revM[revM.size() - 1 - i];
        field[ind / w][ind % w] = 'X';
    }

    printVector(field, "\n");
}

class Solver377ATest : public ProblemTest {};

TEST_F(Solver377ATest, Example1)
{
    string input = R"(3 4 2
#..#
..#.
#...
)";
    string output = R"(#.X#
X.#.
#...
)";
    output.pop_back();
    setInput(input);
    Solver377A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377ATest, Example2)
{
    string input = R"(5 4 5
#...
#.#.
.#..
...#
.#.#
)";
    string output = R"(#XXX
#X#.
.#..
...#
X#.#
)";
    output.pop_back();
    setInput(input);
    Solver377A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


