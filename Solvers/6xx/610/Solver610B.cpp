#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"
#include "algo/Relax.hpp"

using namespace std;

class Solver610B
{
public:
    void run();
};

void Solver610B::run()
{
    int64_t n;
    cin >> n;
    auto amounts = readVector<int64_t>(n);
    auto minAmount = *min_element(begin(amounts), end(amounts));
    int64_t maxAddition = 0;
    int64_t addition = 0;
    for ( int i = 0; i < 2 * n; ++i )
    {
        if ( amounts[i % n] > minAmount )
            addition++;
        else
        {
            relaxMax(maxAddition, addition);
            addition = 0;
        }
    }
    relaxMax( maxAddition, addition );

    cout << n * minAmount + maxAddition;
}

class Solver610BTest : public ProblemTest {};

TEST_F(Solver610BTest, Example1)
{
    string input = R"(5
2 4 2 3 3
)";
    string output = R"(12
)";
    output.pop_back();
    setInput(input);
    Solver610B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver610BTest, Example2)
{
    string input = R"(3
5 5 5
)";
    string output = R"(15
)";
    output.pop_back();
    setInput(input);
    Solver610B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver610BTest, Example3)
{
    string input = R"(6
10 10 10 1 10 10
)";
    string output = R"(11
)";
    output.pop_back();
    setInput(input);
    Solver610B().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F( Solver610BTest, Example4 )
{
    string input = R"(3
1 2 1
)";
    string output = R"(4)";
    setInput( input );
    Solver610B().run();
    EXPECT_EQ( output, getOutput() );
}


