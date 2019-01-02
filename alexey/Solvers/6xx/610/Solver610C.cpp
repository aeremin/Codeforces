#include <Solvers/pch.h>
#include "algo/io/printvector.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/610/problem/C
class Solver610C
{
public:
    void run();

    string reverse( string s )
    {
        for ( auto& c : s )
            c = '*' + '+' - c;
        return s;
    }

};

void Solver610C::run()
{
    int k;
    cin >> k;
    vector<string> answer = { "+" };
    for ( int i = 0; i < k ; ++i )
    {
        auto sz = answer.size();
        for ( size_t i = 0; i < sz; ++i )
        {
            answer.push_back( answer[i] + reverse( answer[i] ) );
            answer[i].append( answer[i] );
        }
    }
    printVector( answer, "\n" );
}

class Solver610CTest : public ProblemTest {};

TEST_F(Solver610CTest, Example1)
{
    string input = R"(2
)";
    string output = R"(++++
+*+*
++**
+**+)";
    setInput(input);
    Solver610C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


