#include <Solvers/pch.h>

using namespace std;

class Solver600C
{
public:
    void run();
};

void Solver600C::run()
{
    string s;
    cin >> s;
    unordered_map<char, int> counts;
    set<char> usedSymbols;
    for ( auto c : s )
    {
        ++counts[c];
        usedSymbols.insert( c );
    }

    set<char> oddSymbols;
    for ( auto c : usedSymbols )
        if ( counts[c] % 2 == 1 )
            oddSymbols.insert( c );

    int symbolsToIncrease = oddSymbols.size() / 2;
    int i = 0;
    char middle = 0;
    for ( auto c : oddSymbols )
    {
        if ( i < symbolsToIncrease )
            counts[c]++;
        else if ( i >= symbolsToIncrease + oddSymbols.size() % 2 )
            counts[c]--;
        else
            middle = c;
        ++i;
    }
    
    string out;
    for ( auto c : usedSymbols )
        out.append( string( ( counts[c] ) / 2, c ) );

    i = out.length() - 1;
    if ( middle != 0 )
        out.push_back( middle );
    for ( ; i >= 0; --i )
        out.push_back( out[i] );
    cout << out;

}

class Solver600CTest : public ProblemTest {};

TEST_F(Solver600CTest, Example1)
{
    string input = R"(aabc
)";
    string output = R"(abba
)";
    setInput(input);
    Solver600C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver600CTest, Example2)
{
    string input = R"(aabcd
)";
    string output = R"(abcba
)";
    setInput(input);
    Solver600C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F( Solver600CTest, Example3 )
{
    string input = R"(aacccdd
)";
    string output = R"(acdcdca)";
    setInput( input );
    Solver600C().run();
    EXPECT_EQ( output, getOutput() );
}

