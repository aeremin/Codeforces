#include <Solvers/pch.h>

using namespace std;

class Solver611C
{
public:
    void run();
};

void Solver611C::run()
{
    int h, w;
    cin >> h >> w;
    vector<string> field(h);
    for (auto& s : field)
        cin >> s;

    vector<vector<int>> possibilitiesH(w, vector<int>(h, 0));
    vector<vector<int>> possibilitiesW(w, vector<int>(h, 0));
    for (int x = 0; x < w; ++x)
        for (int y = 0; y < h; ++y)
            if (field[y][x] == '.')
            {
                if (y + 1 < h && field[y + 1][x] == '.')
                    ++possibilitiesW[x][y];
                if (x + 1 < w && field[y][x + 1] == '.')
                    ++possibilitiesH[x][y];
            }

    vector<vector<int>> possibilitiesSumsH(w + 1, vector<int>(h + 1, 0));
    vector<vector<int>> possibilitiesSumsW(w + 1, vector<int>(h + 1, 0));
    for (int x = 1; x <= w; ++x)
        for (int y = 1; y <= h; ++y)
        {
            possibilitiesSumsH[x][y] = possibilitiesSumsH[x - 1][y] + possibilitiesSumsH[x][y - 1] - possibilitiesSumsH[x - 1][y - 1] + possibilitiesH[x - 1][y - 1];
            possibilitiesSumsW[x][y] = possibilitiesSumsW[x - 1][y] + possibilitiesSumsW[x][y - 1] - possibilitiesSumsW[x - 1][y - 1] + possibilitiesW[x - 1][y - 1];
        }

    int nQueries;
    cin >> nQueries;
    for (int i = 0; i < nQueries; ++i)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        --r1; --c1;
        auto possH = possibilitiesSumsH[c2 - 1][r2] - possibilitiesSumsH[c2 - 1][r1] - possibilitiesSumsH[c1][r2] + possibilitiesSumsH[c1][r1];
        auto possW = possibilitiesSumsW[c2][r2 - 1] - possibilitiesSumsW[c2][r1] - possibilitiesSumsW[c1][r2 - 1] + possibilitiesSumsW[c1][r1];
        cout << (possH + possW) << "\n";
    }
}

class Solver611CTest : public ProblemTest
{
};



TEST_F( Solver611CTest, Example1 )
{
    setInput(R"(
5 8
....#..#
.#......
##.#....
##..#.##
........
4
1 2 4 5
2 5 5 8
1 1 2 3
4 1 4 1
)");
    Solver611C().run();
    EXPECT_EQ("10\n15\n4\n0\n", getOutput());
}

TEST_F(Solver611CTest, Example2)
{
    setInput(R"(
7 39
.......................................
.###..###..#..###.....###..###..#..###.
...#..#.#..#..#.........#..#.#..#..#...
.###..#.#..#..###.....###..#.#..#..###.
.#....#.#..#....#.....#....#.#..#..#.#.
.###..###..#..###.....###..###..#..###.
.......................................
6
1 1 3 20
2 10 6 30
2 10 7 30
2 2 7 7
1 7 7 7
1 8 7 8
)");
    Solver611C().run();
    EXPECT_EQ("53\n89\n120\n23\n0\n2\n", getOutput());
}

TEST_F(Solver611CTest, Example0)
{
    setInput(R"(
2 2
..
..
1
1 1 2 2
)");
    Solver611C().run();
    EXPECT_EQ("4\n", getOutput());
}