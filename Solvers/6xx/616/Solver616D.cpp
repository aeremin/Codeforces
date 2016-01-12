#include <Solvers/pch.h>

using namespace std;

class Solver616D
{
public:
    void run();
};

void Solver616D::run()
{
    int k, n;
    cin >> n >> k;
    vector<int> numbers(n);
    for (auto& elt : numbers)
        cin >> elt;

    int ans = 0;
    int l = -1;
    int bestL = 0;
    int bestR = -1;
    unordered_map<int, int> counts;
    for (int r = 0; r < n; ++r)
    {
        ++counts[numbers[r]];
        while (counts.size() > k)
        {
            ++l;
            auto iter = counts.find(numbers[l]);
            if (iter->second == 1)
                counts.erase(iter);
            else
                --iter->second;
        }
        if (r - l > bestR - bestL)
        {
            bestL = l;
            bestR = r;
        }
    }

    cout << (bestL + 2) << " " << (bestR + 1);
}

class Solver616DTest : public ProblemTest
{
};

TEST_F( Solver616DTest, Example1 )
{
    setInput("5 5             1 2 3 4 5");
    Solver616D().run();
    EXPECT_EQ("1 5", getOutput());
}

TEST_F( Solver616DTest, Example2 )
{
    setInput("9 3             6 5 1 2 3 2 1 4 5");
    Solver616D().run();
    EXPECT_EQ("3 7", getOutput());
}

TEST_F(Solver616DTest, Example3)
{
    setInput("3 1             1 2 3");
    Solver616D().run();
    EXPECT_EQ("1 1", getOutput());
}
