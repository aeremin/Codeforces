#include "Solvers/pch.h"
#include "Solver581B.h"


void Solver581B::run()
{
    int nHouses;
    cin >> nHouses;
    std::vector<int64_t> heights(nHouses);
    for (auto& h : heights)
        cin >> h;

    std::deque<int64_t> maxHeights = { 0 };
    for (int i = nHouses - 1; i > 0; --i)
        maxHeights.push_front(max(maxHeights.front(), heights[i]));

    for (int i = 0; i < nHouses; ++i)
        cout << max<int64_t>(0, maxHeights[i] - heights[i] + 1) << " ";
}

class Solver581BTest : public ProblemTest {};

TEST_F(Solver581BTest, Example1)
{
    setInput("5        1 2 3 1 2");
    Solver581B().run();
    EXPECT_EQ("3 2 0 2 0 ", getOutput());
}

TEST_F(Solver581BTest, Example2)
{
    setInput("4        3 2 1 4");
    Solver581B().run();
    EXPECT_EQ("2 3 4 0 ", getOutput());
}
