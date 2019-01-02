#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/615/problem/A
class Solver615A
{
public:
    void run();
};

void Solver615A::run()
{
    int nButtons, nLights;
    cin >> nButtons >> nLights;
    unordered_set<int> enabledLights;
    for (int i = 0; i < nButtons; ++i)
    {
        int nEnablingLights;
        cin >> nEnablingLights;
        for (int j = 0; j < nEnablingLights; ++j)
        {
            int l;
            cin >> l;
            enabledLights.insert(l);
        }
    }
    if (enabledLights.size() == nLights)
        cout << "YES";
    else
        cout << "NO";
}

class Solver615ATest : public ProblemTest
{
};

TEST_F( Solver615ATest, Example1 )
{
    setInput("3 3        1 1        1 2        1 1");
    Solver615A().run();
    EXPECT_EQ("NO", getOutput());
}

TEST_F( Solver615ATest, Example2 )
{
    setInput("3 4        2 1 4        3 1 3 1        1 2");
    Solver615A().run();
    EXPECT_EQ("YES", getOutput());
}

