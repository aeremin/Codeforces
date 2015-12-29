#include <Solvers/pch.h>

using namespace std;

class Solver476C
{
public:
    void run();
};

void Solver476C::run()
{
    int64_t MODULO = 1000000007;

    int64_t a, b;
    cin >> a >> b;

    int64_t r1 = ( b * ( b - 1 ) ) / 2;
    r1 = r1 % MODULO;

    int64_t r3 = ( a * ( a + 1 ) ) / 2;
    r3 = r3 % MODULO;

    int64_t r2 = a + b * r3;
    r2 = r2 % MODULO;

    cout << ( r1 * r2 ) % MODULO;
}

class Solver476CTest : public ProblemTest
{
};

TEST_F( Solver476CTest, Example1 )
{
    setInput("1 1");
    Solver476C().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F( Solver476CTest, Example2 )
{
    setInput("2 2");
    Solver476C().run();
    EXPECT_EQ("8", getOutput());
}