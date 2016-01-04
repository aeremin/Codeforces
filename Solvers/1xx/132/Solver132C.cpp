#include <Solvers/pch.h>

using namespace std;

class Solver132C
{
public:
    void run();
};

void Solver132C::run()
{
    string s;
    int n;
    cin >> s >> n;
    auto minIntPair = make_pair(numeric_limits<int>::min() / 2, numeric_limits<int>::min() / 2);
    vector<vector<pair<int, int>>> maxDist(s.length() + 1, vector<pair<int, int>>(n + 1, minIntPair));
    maxDist[0][0].first = 0;
    for (int i = 1; i <= s.length(); ++i)
    {
        char c = s[i - 1];
        for (int j = 0; j <= n; ++j)
        {
            auto& currRef = maxDist[i][j];
            vector<pair<char, int>> possibilities;
            possibilities.push_back( { 'F', 0 } );
            if (j >= 1)
                possibilities.push_back({ 'T', 1 });
            for (auto p : possibilities)
            {
                if (c == p.first)
                {
                    auto prevMaxDistForward = maxDist[i - 1][j - p.second].first;
                    currRef.first = max(currRef.first, prevMaxDistForward + 1);

                    auto prevMaxDistBackward = maxDist[i - 1][j - p.second].second;
                    if (prevMaxDistBackward == 0)
                    {
                        currRef.first = max(currRef.first, 1);
                    }
                    else
                    {
                        currRef.second = max(currRef.second, prevMaxDistBackward - 1);
                    }
                }
                else
                {
                    currRef.first = max(currRef.first, maxDist[i - 1][j - p.second].second);
                    currRef.second = max(currRef.second, maxDist[i - 1][j - p.second].first);
                }
            }

            if (j >= 2)
            {
                currRef.first = max(currRef.first, maxDist[i][j - 2].first);
                currRef.second = max(currRef.second, maxDist[i][j - 2].second);
            }
        }
    }

    cout << max(maxDist[s.length()][n].first, maxDist[s.length()][n].second);
}

class Solver132CTest : public ProblemTest
{
};

TEST_F(Solver132CTest, Example1)
{
    setInput("FT        1");
    Solver132C().run();
    EXPECT_EQ("2", getOutput());
}

TEST_F(Solver132CTest, Example2)
{
    setInput("FFFTFFF        2");
    Solver132C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F(Solver132CTest, Example3)
{
    setInput("FFFFFF        0");
    Solver132C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F(Solver132CTest, Example4)
{
    setInput("FFFFFF        1");
    Solver132C().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver132CTest, Example5)
{
    setInput("FFFFFF        2");
    Solver132C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F(Solver132CTest, Example6)
{
    setInput("FFFFFF        100");
    Solver132C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F(Solver132CTest, Example7)
{
    setInput("TFFFFF        101");
    Solver132C().run();
    EXPECT_EQ("6", getOutput());
}

TEST_F(Solver132CTest, Example8)
{
    setInput("TTFTTTFTTT       3");
    Solver132C().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver132CTest, Example9)
{
    setInput("TTFTTTFTTT       3");
    Solver132C().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver132CTest, Example10)
{
    setInput("FTF       0");
    Solver132C().run();
    EXPECT_EQ("0", getOutput());
}