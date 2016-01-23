#include <Solvers/pch.h>

using namespace std;

class SolverFBHC1A
{
public:
    void run();
    void runOneTest();
};

void SolverFBHC1A::run()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        cout << "Case #" << i << ": ";
        runOneTest();
        if (i != t) cout << "\n";
    }
}

void SolverFBHC1A::runOneTest()
{
    int n;
    cin >> n;
    vector<int> ratings(n);
    for (auto& r : ratings)
        cin >> r;

    int ans = 0;
    int i = 0;
    int totalAdded = 0;
    while (i < n)
    {
        vector<int> nextIncreasing = { ratings[i] };
        for (int j = i + 1; (j < i + 4) && j < n && ratings[j] > ratings[j - 1]; ++j)
            nextIncreasing.push_back(ratings[j]);

        int added = 0;
        bool wasBreak = false;
        for (int j = 1; j < nextIncreasing.size(); ++j)
        {
            if (j + added == 4)
            {
                wasBreak = true;
                break;
            }
            auto prev = nextIncreasing[j - 1];
            while ((nextIncreasing[j] > prev + 10))
            {
                ++added;
                prev += 10;
                if (j + added == 4)
                {
                    wasBreak = true;
                    break;
                }
            }
        }
        
        if (!wasBreak)
            added = 4 - nextIncreasing.size();

        totalAdded += added;
        i += 4 - added;
    }

    cout << totalAdded;
}

class SolverFBHC1ATest : public FBHCProblemTest
{
public:
    SolverFBHC1ATest() : FBHCProblemTest("Inputs\\FBHC\\Round1\\A\\") {}
};

TEST_F(SolverFBHC1ATest, Example )
{
    SolverFBHC1A().run();
}

