#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/482/problem/D
class Solver482D
{
public:
    void run();
};

namespace
{
const int MODULO = 1000000000 + 7;

// Represents a1 * x + a0;
// Powers are modulo 2 (x * x = 1)
// Coefficients are taken modulo Modulo
template<int Modulo>
struct GeneratingPolynomial
{
    int64_t a0_, a1_;

    void transpose()
    {
        swap( a0_, a1_ );
    }

    // Neutral element (1)
    GeneratingPolynomial() : a0_( 1 ), a1_( 0 )
    {
    }

    GeneratingPolynomial( int64_t a0, int64_t a1 ) : a0_( a0 ), a1_( a1 )
    {
    };

    const GeneratingPolynomial& operator-=( const GeneratingPolynomial& right )
    {
        a0_ = ( a0_ - right.a0_ + Modulo ) % Modulo;
        a1_ = ( a1_ - right.a1_ + Modulo ) % Modulo;
        return *this;
    }

    const GeneratingPolynomial& operator*=( const GeneratingPolynomial& right )
    {
        int64_t prodA0 = a0_ * right.a0_ + a1_ * right.a1_;
        int64_t prodA1 = a0_ * right.a1_ + a1_ * right.a0_;
        a0_ = prodA0 % Modulo;
        a1_ = prodA1 % Modulo;
        return *this;
    }
};

typedef GeneratingPolynomial<MODULO> ProblemPolynomial;

vector<vector<int>> childs;

ProblemPolynomial possiblities( int ind )
{
    if ( childs[ind].empty() )
    {
        ProblemPolynomial leafres( 1, 1 );
        return leafres;
    }

    ProblemPolynomial resWithDuplicates( 2, 0 ); // As we have two directions
    ProblemPolynomial oddDuplicates;
    ProblemPolynomial evenDuplicates;

    for ( int childInd : childs[ind] )
    {
        auto childPoss = possiblities( childInd );
        resWithDuplicates *= childPoss;

        ProblemPolynomial oddChildPoss( 1, childPoss.a1_ );
        oddDuplicates *= oddChildPoss;

        ProblemPolynomial evenChildPoss( childPoss.a0_, 0 );
        evenDuplicates *= evenChildPoss;
    }

    resWithDuplicates.a0_ = ( resWithDuplicates.a0_ - evenDuplicates.a0_ + MODULO ) % MODULO;
    resWithDuplicates.a1_ = ( resWithDuplicates.a1_ - oddDuplicates.a1_ + MODULO + 1 ) % MODULO;

    resWithDuplicates.transpose();

    return resWithDuplicates;
}
}

void Solver482D::run()
{
    int nVert;
    cin >> nVert;

    childs = vector<vector<int>>( nVert );
    for ( int i = 1; i < nVert; ++i )
    {
        int parI;
        cin >> parI;
        childs[parI - 1].push_back( i );
    }

    for ( auto& childlist : childs )
        sort( begin( childlist ), end( childlist ) );

    auto res = possiblities( 0 );

    cout << ( res.a0_ + res.a1_ + MODULO - 1 ) % MODULO;
}

class Solver482DTest : public ProblemTest
{
};

TEST_F( Solver482DTest, Example1 )
{
    setInput("4              1 2 1");
    Solver482D().run();
    EXPECT_EQ("8", getOutput());
}

TEST_F( Solver482DTest, Example2 )
{
    setInput( "3              1 1" );
    Solver482D().run();
    EXPECT_EQ("5", getOutput());
}