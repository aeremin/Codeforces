#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/316/problem/B
class Solver316B
{
public:
    void run();

    int nBeavers, iSmartBeaver;
    vector<int> beaverPred;

    struct BeaverInfo
    {
        bool calculated = false;
        int depth;
        bool lastInChain = true;
        bool isInSmartBeaverQueue;
    };

    vector<BeaverInfo> info;

    void calcInfo(int i)
    {
        if (info[i].calculated)
            return;
        
        info[i].calculated = true;

        if (beaverPred[i] == -1)
        {
            info[i].depth = 1;
            info[i].isInSmartBeaverQueue = (i == iSmartBeaver);
        }
        else
        {
            calcInfo(beaverPred[i]);
            info[beaverPred[i]].lastInChain = false;
            info[i].depth = info[beaverPred[i]].depth + 1;
            info[i].isInSmartBeaverQueue = info[beaverPred[i]].isInSmartBeaverQueue || i == iSmartBeaver;
        }
    }
};

void Solver316B::run()
{

    cin >> nBeavers >> iSmartBeaver;
    --iSmartBeaver;

    beaverPred = vector<int>(nBeavers);
    for (auto& elt : beaverPred)
    {
        cin >> elt;
        --elt;
    }

    info = vector<BeaverInfo>(nBeavers);

    for (int i = 0; i < nBeavers; ++i)
        calcInfo(i);

    vector<int> chainLengths;
    for (int i = 0; i < nBeavers; ++i)
        if (info[i].lastInChain && !info[i].isInSmartBeaverQueue)
            chainLengths.push_back(info[i].depth);

    set<int> possiblePositionsOfFirstBeaverInChain = { 1 };
    for (auto& chainLen : chainLengths)
    {
        auto nextPossiblePositionsOfFirstBeaverInChain = possiblePositionsOfFirstBeaverInChain;
        for (auto& possiblePosition : possiblePositionsOfFirstBeaverInChain)
            nextPossiblePositionsOfFirstBeaverInChain.insert(possiblePosition + chainLen);
        possiblePositionsOfFirstBeaverInChain = move(nextPossiblePositionsOfFirstBeaverInChain);
    }

    for (auto& pos : possiblePositionsOfFirstBeaverInChain)
        cout << pos + info[iSmartBeaver].depth - 1 << "\n";
}

class Solver316BTest : public ProblemTest
{
};

TEST_F( Solver316BTest, Example1 )
{
    setInput("6 1        2 0 4 0 6 0");
    Solver316B().run();
    EXPECT_EQ("2\n4\n6\n", getOutput());
}

TEST_F( Solver316BTest, Example2 )
{
    setInput("6 2        2 3 0 5 6 0");
    Solver316B().run();
    EXPECT_EQ("2\n5\n", getOutput());
}

TEST_F(Solver316BTest, Example3)
{
    setInput("4 1        0 0 0 0");
    Solver316B().run();
    EXPECT_EQ("1\n2\n3\n4\n", getOutput());
}

TEST_F(Solver316BTest, Example4)
{
    setInput("6 2        0 0 1 0 4 5");
    Solver316B().run();
    EXPECT_EQ("1\n3\n4\n6\n", getOutput());
}