#include <Solvers/pch.h>

using namespace std;

class Solver431D
{
public:
    void run();

    int64_t find(int64_t order, int64_t onesCount)
    {
        if (onesCount == 0)
            return 0;

        if (onesCount == 1)
            return int64_t(1) << (order - 1);

        int64_t l = onesCount;
        int64_t c_l_k = 1;
        while (c_l_k < order)
        {
            ++l;
            c_l_k = (c_l_k * l) / (l - onesCount);
        }

        c_l_k = (c_l_k * (l - onesCount)) / l;
        
        return (int64_t(1) << (l - 1)) + find(order - c_l_k, onesCount - 1);
    }
};

void Solver431D::run()
{
    int64_t m, k;
    cin >> m >> k;
    if (m == 0)
    {
        cout << 1;
        return;
    }

    cout << find(m, k - 1) + 1;
}

class Solver431DTest : public ProblemTest
{
};

TEST_F( Solver431DTest, Example1 )
{
    setInput("1 1");
    Solver431D().run();
    EXPECT_EQ("1", getOutput());
}

TEST_F( Solver431DTest, Example2 )
{
    setInput("3 2");
    Solver431D().run();
    EXPECT_EQ("5", getOutput());
}

TEST_F(Solver431DTest, Find)
{
    Solver431D solver;
    EXPECT_EQ(3, solver.find(1, 2));
    EXPECT_EQ(5, solver.find(2, 2));
    EXPECT_EQ(6, solver.find(3, 2));
    EXPECT_EQ(9, solver.find(4, 2));
    EXPECT_EQ(10, solver.find(5, 2));
}