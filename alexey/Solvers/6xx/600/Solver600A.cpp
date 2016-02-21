#include <Solvers/pch.h>

using namespace std;

class Solver600A
{
public:
    void run();
};

void Solver600A::run()
{
    string s;
    cin >> s;
    s.append( ";" );
    regex delimiter( ",|;" );
    vector<string> tokens;
    std::copy( sregex_token_iterator( begin( s ), end( s ), delimiter, -1 ),
               sregex_token_iterator(),
               back_inserter( tokens ) );

    string numbers = "\"";
    string notNumbers = "\"";

    regex intNumberString( "[1-9]\\d*|0" );
    for ( auto& token : tokens )
    {
        if ( regex_match( token, intNumberString ) )
            numbers.append( token + "," );
        else
            notNumbers.append( token + "," );
    }
    
    numbers.back() = '\"';
    notNumbers.back() = '\"';
    if ( numbers.length() == 1 )
        numbers = "-";

    if ( notNumbers.length() == 1 )
        notNumbers = "-";

    cout << numbers << "\n" << notNumbers;
}

class Solver600ATest : public ProblemTest {};

TEST_F(Solver600ATest, Example1)
{
    string input = R"(aba,123;1a;0
)";
    string output = R"("123,0"
"aba,1a"
)";
    output.pop_back();
    setInput(input);
    Solver600A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver600ATest, Example2)
{
    string input = R"(1;;01,a0,
)";
    string output = R"("1"
",01,a0,"
)";
    output.pop_back();
    setInput(input);
    Solver600A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver600ATest, Example3)
{
    string input = R"(1
)";
    string output = R"("1"
-
)";
    output.pop_back();
    setInput(input);
    Solver600A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver600ATest, Example4)
{
    string input = R"(a
)";
    string output = R"(-
"a"
)";
    output.pop_back();
    setInput(input);
    Solver600A().run();
    EXPECT_EQ(output, getOutput());
}


