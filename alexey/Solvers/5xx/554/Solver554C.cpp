#include <Solvers/pch.h>
#include "algo/numbertheory/Residue.hpp"
#include "algo/io/readvector.hpp"
#include "math/binomial_coefficients.h"

using namespace std;

class Solver554C
{
public:
    void run();
};

void Solver554C::run()
{
    int k;
    cin >> k;
    auto count = readVector<int64_t>( k );
    
    auto nBalls = accumulate( begin( count ), end( count ), int64_t(0) );

    CodeforcesResidue64 ans = 1;
    while ( !count.empty() )
    {
        int countOfMax = count.back();
        count.pop_back();
        ans *= BinomialCoefficient( CodeforcesResidue64( 1 ), nBalls - 1, countOfMax - 1 );
        nBalls -= countOfMax;
    }

    cout << ans;
}

class Solver554CTest : public ProblemTest {};

TEST_F(Solver554CTest, Example1)
{
    string input = R"(3
2
2
1
)";
    string output = R"(3
)";
    output.pop_back();
    setInput(input);
    Solver554C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver554CTest, Example2)
{
    string input = R"(4
1
2
3
4
)";
    string output = R"(1680
)";
    output.pop_back();
    setInput(input);
    Solver554C().run();
    EXPECT_EQ(output, getOutput());
}
