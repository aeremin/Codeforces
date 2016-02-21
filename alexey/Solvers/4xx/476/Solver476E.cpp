#include <Solvers/pch.h>

using namespace std;

class Solver476E
{
public:
    void run();
};

void improve( int& value, int cand )
{
    value = max( value, cand );
}

void Solver476E::run()
{
    string str, pattern;
    vector<int> endOfPattern;

    cin >> str >> pattern;

    vector<vector<int>> answer( str.length() + 1, vector<int>( str.length() + 1, 0 ) );

    for ( int i = 0; i < str.length(); ++i )
    {
        int patternPos = 0;
        int strpos;
        for ( strpos = i; strpos < str.length(); ++strpos )
        {
            if ( str[strpos] == pattern[patternPos] )
            {
                patternPos++;
                if ( patternPos == pattern.length() )
                    break;
            }
        }
        endOfPattern.push_back( strpos < str.length() ? strpos : -1 );
    }

    for ( int right = 0; right < str.length(); ++right )
    {
        for ( int removed = 0; removed <= right; ++removed )
        {
            improve( answer[right + 1][removed], answer[right][removed] );
            improve( answer[right + 1][removed + 1], answer[right][removed] );
            if ( endOfPattern[right] != -1 )
                improve( answer[endOfPattern[right] + 1][removed + endOfPattern[right] - right - pattern.length() + 1], answer[right][removed] + 1 );
        }
    }

    for ( int elt : answer.back() )
        cout << elt << ' ';
}

class Solver476ETest : public ProblemTest
{
};

TEST_F( Solver476ETest, Example1 )
{
    setInput("aaaaa              aa");
    Solver476E().run();
    EXPECT_EQ("2 2 1 1 0 0 ", getOutput());
}

TEST_F( Solver476ETest, Example2 )
{
    setInput("axbaxxb              ab");
    Solver476E().run();
    EXPECT_EQ("0 1 1 2 1 1 0 0 ", getOutput());
}