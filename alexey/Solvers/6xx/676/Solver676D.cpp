#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/graph/Graph.hpp"
#include "algo/graph/Dijkstra.hpp"
using namespace std;

class Solver676D {
public:
    void run();

    class GridGraph {
    public:
        struct Vertex {
            Vertex(int v) : v_(v) {}
            int vertex() const { return v_; }
            int v_;
        };

        GridGraph(vector<vector<int8_t>> zeroLevel) {
            field[0] = move(zeroLevel);
            for (int l : range(1, 4)) {
                field[l] = vector<vector<int8_t>>(n(), vector<int8_t>(m()));
                for (int x : range(n()))
                    for (int y : range(m()))
                        field[l][x][y] = ((field[l - 1][x][y] << 1) | (field[l - 1][x][y] >> 3)) & 15;
            }
        }

        int n() const { return field[0].size(); }
        int m() const { return field[0][0].size(); }
        int num_vertices() const { return n() * m() * 4; }

        vector<Vertex> out_nbrs(int v) const {
            struct Nei {
                int offsX, offsY;
                int mask, neiMask;
            };
            static vector<Nei> neis = {
                { 0, +1, 1, 4 },{ +1, 0, 2, 8 },{ 0, -1, 4, 1 },{ -1, 0, 8, 2 }
            };
            
            int x = v % n();
            int y = (v / n()) % m();
            int level = v / (n() * m());

            vector<Vertex> result = { pack(x, y, (level + 1) % 4) };

            for (auto& nei : neis) {
                int xx = x + nei.offsX;
                int yy = y + nei.offsY;
                if (xx >= n() || yy >= m() || xx < 0 || yy < 0) continue;
                if ((field[level][x][y] & nei.mask) && (field[level][xx][yy] & nei.neiMask))
                    result.push_back(pack(xx, yy, level));
            }

            return result;
        }

        int pack(int x, int y, int level) const { return level * n() * m() + y * n() + x; }

    private:
        vector<vector<int8_t>> field[4];
    };

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

    GridGraph g(move(field));

    auto dr = getMinimalPathsFromUnweighted(g, g.pack(xt, yt, 0), numeric_limits<int>::max());
    auto ans = min({ dr.minimalDistances[g.pack(xm, ym, 0)], dr.minimalDistances[g.pack(xm, ym, 1)],
                     dr.minimalDistances[g.pack(xm, ym, 2)], dr.minimalDistances[g.pack(xm, ym, 3)] });
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
    setInput(input);
    Solver676D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
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
    setInput(input);
    Solver676D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}