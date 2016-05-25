#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/graph/Graph.hpp"
#include "algo/graph/Dijkstra.hpp"
using namespace std;

class Solver676D {
public:
    void run();
};

void Solver676D::run() {
    map<char, int8_t> charToMask = {
        {'+', 15}, {'-', 5}, {'|', 10}, {'^', 8}, {'>', 1}, {'<', 4}, {'v', 2}, 
        {'L', 15 - 4}, {'R', 15 - 1}, {'U', 15 - 8}, {'D', 15 - 2}, {'*', 0} 
    };

    int n, m;
    cin >> n >> m;
    vector<string> fieldIn(n);
    for (auto& l : fieldIn)
        cin >> l;

    int xt, yt, xm, ym;
    cin >> xt >> yt >> xm >> ym;
    --xt; --yt; --xm; --ym;

    vector<vector<int8_t>> field(n, vector<int8_t>(m));
    for (int x : range(n))
        for (int y : range(m))
            field[x][y] = charToMask[fieldIn[x][y]];

    auto pack = [&](int x, int y, int level) {return level * n * m + y * n + x; };
    SimpleGraph g(n * m * 4);
    for (int x : range(n))
        for (int y : range(m))
            for (int l : range(4))
                g.add_directed_edge(pack(x, y, l), pack(x, y, (l + 1) % 4));

    struct Nei {
        int offsX, offsY;
        int mask, neiMask;
    };

    vector<Nei> neis = {
        {0, +1, 1, 4}, {+1, 0, 2, 8}, {0, -1, 4, 1}, {-1, 0, 8, 2}
    };

    for (int l : range(4)) {
        for (int x : range(n))
             for (int y : range(m))
                 for (auto& nei : neis) {
                     int xx = x + nei.offsX;
                     int yy = y + nei.offsY;
                     if (xx >= n || yy >= m || xx < 0 || yy < 0) continue;
                     if ((field[x][y] & nei.mask) && (field[xx][yy] & nei.neiMask))
                         g.add_directed_edge(pack(x, y, l), pack(xx, yy, l));
                 }

        for (int x : range(n))
            for (int y : range(m))
                field[x][y] = ((field[x][y] << 1) | (field[x][y] >> 3)) & 15;
    }

    auto dr = getMinimalPathsFromUnweighted(g, pack(xt, yt, 0), numeric_limits<int>::max());
    auto ans = min({ dr.minimalDistances[pack(xm, ym, 0)], dr.minimalDistances[pack(xm, ym, 1)], 
                     dr.minimalDistances[pack(xm, ym, 2)], dr.minimalDistances[pack(xm, ym, 3)] });
    if (ans == numeric_limits<int>::max()) ans = -1;
    cout << ans;
}


class Solver676DTest : public ProblemTest {};




TEST_F(Solver676DTest, Example2) {
    string input = R"(2 3
<><
><>
1 1
2 1
)";
    string output = R"(4
)";
    output.pop_back();
    setInput(input);
    Solver676D().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver676DTest, Example1) {
    string input = R"(2 2
+*
*U
1 1
2 2
)";
    string output = R"(-1
)";
    output.pop_back();
    setInput(input);
    Solver676D().run();
    EXPECT_EQ(output, getOutput());
}