#include <Solvers/pch.h>

using namespace std;

class Solver000A
{
public:
    void run();
    void runOneTest();
};

void Solver000A::run()
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

void Solver000A::runOneTest()
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

class Solver000ATest : public ProblemTest
{
};

TEST_F( Solver000ATest, Example )
{
    setInput(
R"(6
4
10 15 25 30
4
15 20 25 40
3
3 3 3
8
60 90 61 62 63 91 92 93
11
5 14 30 32 39 46 47 47 30 58 47
7 
100 100 100 100 100 100 100)");

    std::string expected = 
R"(Case #1: 0
Case #2: 4
Case #3: 9
Case #4: 4
Case #5: 9
Case #6: 21)";
    Solver000A().run();
    EXPECT_EQ(expected, getOutput());
}

