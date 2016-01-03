#include <Solvers/pch.h>

using namespace std;

class Solver354C
{
public:
    void run();
};

void Solver354C::run()
{
    const int maxNum = 1000000;
    int n, k;
    cin >> n >> k;
    vector<int> marked(maxNum + 1);
    for (int i = 0; i < n; ++i)
    {
        int  elt; 
        cin >> elt; 
        marked[elt]++;
    }
    vector<int> markedSums; 
    markedSums.reserve(marked.size());
    partial_sum(begin(marked), end(marked), back_inserter(markedSums));
    int ans = 1;
    for (int posAns = 2; posAns <= maxNum; ++posAns)
    {
        int count = 0;
        for (int j = posAns; j <= maxNum; j += posAns)
            count += markedSums[min(maxNum, j + min(k, posAns - 1))] - markedSums[j - 1];
        if (count == n) 
            ans = posAns;
    }
    cout << ans;
}

class Solver354CTest : public ProblemTest
{
};

TEST_F( Solver354CTest, Example1 )
{
    setInput("6 1        3 6 10 12 13 16");
    Solver354C().run();
    EXPECT_EQ("3", getOutput());
}

TEST_F( Solver354CTest, Example2 )
{
    setInput("5 3        8 21 52 15 77");
    Solver354C().run();
    EXPECT_EQ("7", getOutput());
}