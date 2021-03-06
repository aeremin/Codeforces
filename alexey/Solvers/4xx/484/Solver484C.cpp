#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/484/problem/C
class Solver484C
{
public:
    void run();
};

// By default Maps A -> (A - offset) for any int A
// One can override mappings from not-negative ints
class IntToIntOffsettingMap
{
public:
    // Sort of hack for quick_power to work 
    IntToIntOffsettingMap( int dummy, int offset = 0 ) : offset_( offset )
    {
    }

    void addMapping( int from, int to )
    {
        if ( from >= map_.size() )
            map_.resize( from + 1 );
        map_[from] = to;
    }

    int operator()( int from ) const
    {
        if ( from >= 0 && from < map_.size() )
            return map_[from];
        else
            return from - offset_;
    }

    // A *= B means A = B * A, not A = A * B!
    const IntToIntOffsettingMap& operator*=( const IntToIntOffsettingMap& other )
    {
        int endInd = max( map_.size() + other.offset_, other.map_.size() );
        vector<int> newMap( endInd );
        for ( int i = 0; i < endInd; ++i )
            newMap[i] = other( ( *this )( i ) );
        swap( newMap, map_ );
        offset_ += other.offset_;
        return *this;
    }
private:
    vector<int> map_;
    int offset_;
};

template<class T>
void quick_power( const T& a, int d, T& res )
{
    T m = a;
    while ( d > 0 )
    {
        if ( d % 2 == 0 )
        {
            m *= m;
            d /= 2;
        }
        else
        {
            res *= m;
            d--;
        }
    }
}

void Solver484C::run()
{
    string str1, str2;
    cin >> str1;

    int strLen = str1.length();

    str2 = str1;
    auto curStr = &str1;
    auto nextStr = &str2;


    int nQueries;
    cin >> nQueries;

    for ( int iQuery = 0; iQuery < nQueries; ++iQuery )
    {
        int k, d;
        cin >> k >> d;

        IntToIntOffsettingMap dsort( 0, 1 );
        int prePi = 0;
        int residue = 0;
        for ( int postPi = 0; postPi < k; ++postPi )
        {
            dsort.addMapping( prePi, postPi - 1 );
            prePi += d;
            if ( prePi >= k )
            {
                residue++;
                prePi = residue;
            }
        }

        IntToIntOffsettingMap permutation( dsort );
        quick_power( dsort, strLen - k, permutation );
        for ( int i = 0; i < strLen; ++i )
        {
            int indexAfterPermutation = permutation( i ) + ( strLen - k + 1 );
            ( *nextStr )[indexAfterPermutation] = ( *curStr )[i];
        }
        swap( nextStr, curStr );
        cout << *curStr << '\n';
    }
}

class Solver484CTest : public ProblemTest
{
};

TEST_F( Solver484CTest, Example1 )
{
    setInput( "qwerty              3              4 2              6 3              5 2" );
    Solver484C().run();
    EXPECT_EQ( "qertwy\nqtewry\nqetyrw\n", getOutput() );
}
