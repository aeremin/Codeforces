#include <Solvers/pch.h>

using namespace std;

class Solver158E
{
public:
    void run();
};

void Solver158E::run()
{
    int nCalls, nAllowedToIgnore;
    cin >> nCalls >> nAllowedToIgnore;
    vector<pair<int, int>> calls(nCalls);
    for (auto& p : calls)
        cin >> p.first >> p.second;

    vector<vector<int>> minTimeToFinishCalls(nCalls + 1, vector<int>(nAllowedToIgnore + 1, 1));
    for (int iCalls = 1; iCalls <= nCalls; ++iCalls)
        for (int iIgnoring = 0; iIgnoring <= nAllowedToIgnore; ++iIgnoring)
        {
            auto& curr = minTimeToFinishCalls[iCalls][iIgnoring];
            if (iCalls <= iIgnoring)
                curr = 1;
            else
            {
                curr = max(minTimeToFinishCalls[iCalls - 1][iIgnoring], calls[iCalls - 1].first) + calls[iCalls - 1].second;
                if (iIgnoring > 0)
                    curr = min(curr, minTimeToFinishCalls[iCalls - 1][iIgnoring - 1]);
            }
        }

    int maxTimeToSleep = 0;
    for (int ignoreBeforeSleep = 0; ignoreBeforeSleep <= nAllowedToIgnore; ++ignoreBeforeSleep)
        for (int callsBeforeSleep = 0; callsBeforeSleep <= nCalls; ++callsBeforeSleep)
        {
            auto ignoreAfterSleep = nAllowedToIgnore - ignoreBeforeSleep;
            auto firstCallAfterSleepStart = (callsBeforeSleep + ignoreAfterSleep) < nCalls ? calls[callsBeforeSleep + ignoreAfterSleep].first : 86401;
            maxTimeToSleep = max(maxTimeToSleep, firstCallAfterSleepStart - minTimeToFinishCalls[callsBeforeSleep][ignoreBeforeSleep]);
        }

    cout << maxTimeToSleep;
}

class Solver158ETest : public ProblemTest
{
};

TEST_F( Solver158ETest, Example1 )
{
    setInput("3 2        30000 15000        40000 15000        50000 15000");
    Solver158E().run();
    EXPECT_EQ("49999", getOutput());
}

TEST_F( Solver158ETest, Example2 )
{
    setInput("5 1        1 20000        10000 10000        20000 20000        25000 10000        80000 60000");
    Solver158E().run();
    EXPECT_EQ("39999", getOutput());
}

TEST_F(Solver158ETest, Example3)
{
    setInput("1 0        1 100");
    Solver158E().run();
    EXPECT_EQ("86300", getOutput());
}