#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/KnuttMorrisPratt.hpp"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver633C
{
public:
    void run();

    vector<int> allowedFinishes( string pattern, const string& ciphered )
    {
        transform( pattern.begin(), pattern.end(), pattern.begin(), ::tolower );
        reverse( pattern.begin(), pattern.end() );
        string s = pattern + "$" + ciphered;
        auto pi = calc_prefix_function( s );
        vector<int> result;
        for ( int i : range( ciphered.length() ) )
            if ( pi[pattern.length() + 1 + i] == pattern.length() )
                result.push_back( i );
        return result;
    }

};

void Solver633C::run()
{
    int len;
    cin >> len;
    string ciphered;
    cin >> ciphered;
    int dictionarySize;
    cin >> dictionarySize;
    vector<string> dictionary = readVector<string>( dictionarySize );
    vector<vector<pair<int, int>>> allowedBackJumps( len );
    for ( auto i : range(dictionarySize) )
    {
        auto finishes = allowedFinishes( dictionary[i], ciphered );
        for ( auto j : finishes )
            allowedBackJumps[j].push_back( { dictionary[i].length(), i } );
    }

    vector<int> jumps(len + 1, -2);
    jumps[0] = -1;
    for ( int i : range( len ) )
        for ( auto p : ; [i] )
            if ( jumps[1 + i - p.first] >= -1 )
            {
                jumps[1 + i] = p.second;
                break;
            }

    deque<int> indices;
    int currPos = len;
    do
    {
        int currIndex = jumps[currPos];
        indices.push_front( currIndex );
        currPos -= dictionary[currIndex].length();
    } while ( currPos > 0 );

    for ( auto i : indices )
        cout << dictionary[i] << " ";
}

class Solver633CTest : public ProblemTest {};

TEST_F(Solver633CTest, Example1)
{
    string input = R"(30
ariksihsidlihcdnaehsetahgnisol
10
Kira
hates
is
he
losing
death
childish
L
and
Note
)";
    string output = R"(Kira is childish and he hates losing 
)";
    output.pop_back();
    setInput(input);
    Solver633C().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver633CTest, Example2)
{
    string input = R"(12
iherehtolleh
5
HI
Ho
there
HeLLo
hello
)";
    string output = R"(HI there HeLLo 
)";
    output.pop_back();
    setInput(input);
    Solver633C().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F( Solver633CTest, MaxCase )
{
    stringstream ss;
    ss << "10000\n";
    ss << string( 10000, 'a' ) << "\n";
    ss << "1000\n";
    for ( int i : range( 1, 1001 ) )
        ss << string( i, 'a' ) << "\n";
    
    setInput( ss.str() );
    Solver633C().run();
}


