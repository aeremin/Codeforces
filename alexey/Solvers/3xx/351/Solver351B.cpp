#include <Solvers/pch.h>

using namespace std;

class Solver351B
{
public:
    void run();
};

void Solver351B::run()
{
    int n;
    cin >> n;
    
    vector<int> permutation(n);
    for (auto& elt : permutation)
        cin >> elt;
    
    int nInversions = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (permutation[j] > permutation[i])
                nInversions++;

    if (nInversions % 2 == 0)
        cout << 2 * nInversions;
    else
        cout << 2 * nInversions - 1;
}

class Solver351BTest : public ProblemTest
{
};

TEST_F( Solver351BTest, Example1 )
{
    setInput("2        1 2");
    Solver351B().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F( Solver351BTest, Example2 )
{
    setInput("5        3 5 2 4 1");
    Solver351B().run();
    EXPECT_EQ("13", getOutput());
}