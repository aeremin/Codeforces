#include <Solvers/pch.h>

using namespace std;

class Solver372B
{
public:
    void run();
};

void Solver372B::run()
{
    int h, w, nQueries;
    cin >> h >> w >> nQueries;
    vector<string> field(h);
    for (auto& s : field)
        cin >> s;

    vector<vector<int>> prefixSum(w + 1, vector<int>(h + 1));
    for (int x = 1; x <= w; ++x)
        for (int y = 1; y <= h; ++y)
            prefixSum[x][y] = (field[y - 1][x - 1] - '0') +
            prefixSum[x - 1][y] + prefixSum[x][y - 1] - prefixSum[x - 1][y - 1];

    auto counts = vector<vector<vector<vector<int>>>>(w + 1, vector <vector<vector<int>>>(h + 1, vector<vector<int>>(w + 2, vector<int>(h + 2))));
    for (int ww = 2; ww <= w + 1; ++ww)
        for (int hh = 2; hh <= h + 1; ++hh)
            for (int x = 0; x + ww - 1 <= w; ++x)
                for (int y = 0; y + hh - 1<= h; ++y)
                {
                    bool isFullRectangleEmpty = (prefixSum[x + ww - 1][y + hh - 1] - prefixSum[x][y + hh - 1] - prefixSum[x + ww - 1][y] + prefixSum[x][y] == 0);
                    int a = counts[x][y][ww][hh] = (isFullRectangleEmpty ? 1 : 0) +
                        counts[x + 1][y][ww - 1][hh] + counts[x][y + 1][ww][hh - 1] + counts[x][y][ww - 1][hh] + counts[x][y][ww][hh - 1]
                        - counts[x + 1][y + 1][ww - 1][hh - 1] - counts[x + 1][y][ww - 2][hh] - counts[x + 1][y][ww - 1][hh - 1]
                        - counts[x][y + 1][ww - 1][hh - 1] - counts[x][y + 1][ww][hh - 2] - counts[x][y][ww - 1][hh - 1]
                        + counts[x][y + 1][ww - 1][hh - 2] + counts[x + 1][y][ww - 2][hh - 1] + counts[x + 1][y + 1][ww - 1][hh - 2] + counts[x + 1][y + 1][ww - 2][hh - 1]
                        - counts[x + 1][y + 1][ww - 2][hh - 2];
                    a = a;
                }

    for (int i = 0; i < nQueries; ++i)
    {
        int a, b, c, d;
        cin >> b >> a >> d >> c;
        cout << counts[a - 1][b - 1][c - a + 2][d - b + 2] << "\n";
    }
}

class Solver372BTest : public ProblemTest
{
};

TEST_F(Solver372BTest, Example0)
{
    setInput(R"(
1 2 1
00
1 1 1 2
)");
    Solver372B().run();
    EXPECT_EQ("3\n", getOutput());
}


TEST_F(Solver372BTest, Example1)
{
    setInput(R"(
5 5 5
00101
00000
00001
01000
00001
1 2 2 4
4 5 4 5
1 2 5 2
2 2 4 5
4 2 5 3
)");
    Solver372B().run();
    EXPECT_EQ("10\n1\n7\n34\n5\n", getOutput());
}

TEST_F(Solver372BTest, Example)
{
    setInput(R"(
4 7 5
0000100
0000010
0011000
0000000
1 7 2 7
3 1 3 1
2 3 4 5
1 2 2 7
2 2 4 7
)");
    Solver372B().run();
    EXPECT_EQ("3\n1\n16\n27\n52\n", getOutput());
}
