#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"

using namespace std;

class Solver615E
{
public:
    void run();
};

void Solver615E::run()
{
    int64_t n;
    cin >> n;
    if (n == 0)
    {
        cout << "0 0";
        return;
    }

    int64_t k = sqrt(double(n) / 3 + 0.25) - 0.5 + 0.999999999999;
    n -= 3 * k * (k - 1);
    
    GeomVector2<int64_t> pos({ 2 * (k - 1), 0 });

    vector<pair<int64_t, GeomVector2<int64_t>>> moves = 
    {
        { 1,     GeomVector2<int64_t>({ int64_t( 1), int64_t( 2) }) },
        { k - 1, GeomVector2<int64_t>({ int64_t(-1), int64_t( 2) }) },
        { k,     GeomVector2<int64_t>({ int64_t(-2), int64_t( 0) }) },
        { k,     GeomVector2<int64_t>({ int64_t(-1), int64_t(-2) }) },
        { k,     GeomVector2<int64_t>({ int64_t( 1), int64_t(-2) }) },
        { k,     GeomVector2<int64_t>({ int64_t( 2), int64_t( 0) }) },
        { k,     GeomVector2<int64_t>({ int64_t( 1), int64_t( 2) }) }
    };
    
    for (auto m : moves)
    {
        if (n <= m.first)
        {
            pos += n * m.second;
            cout << pos[0] << " " << pos[1];
            return;
        }
        pos += m.first * m.second;
        n -= m.first;
    }
}

class Solver615ETest : public ProblemTest
{
};

TEST_F(Solver615ETest, Example0)
{
    setInput("0");
    Solver615E().run();
    EXPECT_EQ("0 0", getOutput());
}

TEST_F(Solver615ETest, Example1)
{
    setInput("1");
    Solver615E().run();
    EXPECT_EQ("1 2", getOutput());
}

TEST_F(Solver615ETest, Example2)
{
    setInput("2");
    Solver615E().run();
    EXPECT_EQ("-1 2", getOutput());
}


TEST_F( Solver615ETest, Example3 )
{
    setInput("3");
    Solver615E().run();
    EXPECT_EQ("-2 0", getOutput());
}

TEST_F(Solver615ETest, Example4)
{
    setInput("4");
    Solver615E().run();
    EXPECT_EQ("-1 -2", getOutput());
}

TEST_F(Solver615ETest, Example5)
{
    setInput("5");
    Solver615E().run();
    EXPECT_EQ("1 -2", getOutput());
}

TEST_F(Solver615ETest, Example6)
{
    setInput("6");
    Solver615E().run();
    EXPECT_EQ("2 0", getOutput());
}

TEST_F( Solver615ETest, Example7 )
{
    setInput("7");
    Solver615E().run();
    EXPECT_EQ("3 2", getOutput());
}

TEST_F(Solver615ETest, Example18)
{
    setInput("18");
    Solver615E().run();
    EXPECT_EQ("4 0", getOutput());
}
