#include <Solvers/pch.h>
#include "util/relax.h"

using namespace std;

namespace
{
const vector<pair<int, int>> offsets = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
const unordered_map<char, char> nextLetter = { { 'D', 'I' }, { 'I', 'M' }, { 'M', 'A' }, { 'A', 'D' } };
}

// Solution for Codeforces problem http://codeforces.com/contest/374/problem/C
class Solver374C
{
public:
    void run();

    int height, width;
    vector<string> board;
    vector<vector<int>> maxValues;

    int getMaxValue(int x, int y)
    {
        if (maxValues[x][y] > 0)
            return maxValues[x][y];

        if (maxValues[x][y] == -2)
            return numeric_limits<int>::max() / 10;

        maxValues[x][y] = -2;
        int maxNeighbourValue = 0;
        for (auto& offs : offsets)
        {
            auto neigbour = make_pair(x + offs.first, y + offs.second);
            if (neigbour.first >= 0 && neigbour.first < width && neigbour.second >= 0 && neigbour.second < height)
                if (nextLetter.at(board[y][x]) == board[neigbour.second][neigbour.first])
                    relax_max(maxNeighbourValue, getMaxValue(neigbour.first, neigbour.second));
        }
        return maxValues[x][y] = maxNeighbourValue + 1;
    }
};

void Solver374C::run()
{
    cin >> height >> width;
    board = vector<string>(height);
    for (auto& s : board)
        cin >> s;

    maxValues = vector<vector<int>>(width, vector<int>(height, -1));

    int maxValue = 0;

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
        {
            auto v = getMaxValue(x, y);
            if (board[y][x] == 'D')
                relax_max(maxValue, v);
        }


    if (maxValue < 4)
        cout << "Poor Dima!";
    else if (maxValue >= numeric_limits<int>::max() / 10)
        cout << "Poor Inna!";
    else
        cout << (maxValue / 4);
}

class Solver374CTest : public ProblemTest
{
};

TEST_F( Solver374CTest, Example1 )
{
    setInput("1 2\nDI");
    Solver374C().run();
    EXPECT_EQ("Poor Dima!", getOutput());
}

TEST_F( Solver374CTest, Example2 )
{
    setInput("2 2\nMA\nID");
    Solver374C().run();
    EXPECT_EQ("Poor Inna!", getOutput());
}

TEST_F(Solver374CTest, Example3)
{
    setInput(R"(
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID
)");
    Solver374C().run();
    EXPECT_EQ("4", getOutput());
}

TEST_F(Solver374CTest, Example4)
{
    setInput("1 40\nDIMADIMADIMADIMADIMADIMADIMADIMADIMADIMA");
    Solver374C().run();
    EXPECT_EQ("10", getOutput());
}