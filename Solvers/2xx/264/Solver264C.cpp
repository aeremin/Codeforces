#include <Solvers/pch.h>

using namespace std;

class Solver264C
{
public:
    void run();

    struct Ball
    {
        size_t color;
        int64_t value;
    };
};

void Solver264C::run()
{
    size_t nBalls, nQueries;
    cin >> nBalls >> nQueries;
    vector<Ball> balls(nBalls);
    for (auto& b : balls)
        cin >> b.value;
    for (auto& b : balls)
        cin >> b.color;

    for (size_t i = 0; i < nQueries; ++i)
    {
        int64_t a, b;
        cin >> a >> b;
        vector<int64_t> maxPerLastColor(nBalls + 1, numeric_limits<int64_t>::min() / 10);
        maxPerLastColor[0] = 0;
        size_t iMax = 0, iNextMax = 0;
        for (auto& ball : balls)
        {
            auto prevMaxSameColor = maxPerLastColor[ball.color];
            auto prevMaxOtherColor = (ball.color == iMax) ? maxPerLastColor[iNextMax] : maxPerLastColor[iMax];
            auto currMax = max({ prevMaxSameColor + a * ball.value, prevMaxOtherColor + b * ball.value, prevMaxSameColor });
            if (currMax > maxPerLastColor[iNextMax] && ball.color != iMax)
            {
                if (currMax > maxPerLastColor[iMax])
                {
                    iNextMax = iMax;
                    iMax = ball.color;
                }
                else
                    iNextMax = ball.color;
            }
            maxPerLastColor[ball.color] = currMax;
        }
        auto ans = *max_element(begin(maxPerLastColor), end(maxPerLastColor));
        cout << ans << "\n";
    }
}

class Solver264CTest : public ProblemTest
{
};

TEST_F( Solver264CTest, Example1 )
{
    setInput(R"(
6 3
1 -2 3 4 0 -1
1 2 1 2 1 1
5 1
-2 1
1 0
)");
    Solver264C().run();
    EXPECT_EQ("20\n9\n4\n", getOutput());
}

TEST_F( Solver264CTest, Example2 )
{
    setInput(R"(
4 1
-3 6 -1 2
1 2 3 1
1 -1
)");
    Solver264C().run();
    EXPECT_EQ("5\n", getOutput());
}
