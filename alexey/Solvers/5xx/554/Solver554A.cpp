#include <Solvers/pch.h>

using namespace std;

class Solver554A
{
public:
    void run();
};

void Solver554A::run()
{
    string s;
    cin >> s;
    std::unordered_set<string> possibleBooks;
    for ( size_t i = 0; i <= s.length(); ++i )
        for ( char c = 'a'; c <= 'z'; ++c )
            possibleBooks.insert( s.substr( 0, i ) + c + s.substr( i, string::npos ) );

    cout << possibleBooks.size();

}

class Solver554ATest : public ProblemTest {};

TEST_F(Solver554ATest, Example1)
{
    string input = R"(a
)";
    string output = R"(51
)";
    setInput(input);
    Solver554A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver554ATest, Example2)
{
    string input = R"(hi
)";
    string output = R"(76
)";
    setInput(input);
    Solver554A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


