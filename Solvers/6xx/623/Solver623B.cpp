#include <Solvers/pch.h>
#include "algo/numbertheory/Primes.hpp"
#include "algo/io/readvector.hpp"
#include "algo/DPProcessor.hpp"

using namespace std;

class Solver623B
{
public:
    void run();

    
    void addDivisorsOfNumberAndNeighbours( int a )
    {
        addDivisorsOf( a - 1 );
        addDivisorsOf( a );
        addDivisorsOf( a + 1 );
    }

    void addDivisorsOf( int a )
    {
        for ( auto p : decomposeToPrimePowers( a ) )
            possiblePrimeDivisors.insert( p.first );
    }
    
    unordered_set<int> possiblePrimeDivisors;
};

void Solver623B::run()
{
    size_t n;
    cin >> n;
    int64_t a, b;
    cin >> a >> b;
    auto numbers = readVector<int>( n );
    addDivisorsOfNumberAndNeighbours( numbers.front() );
    addDivisorsOfNumberAndNeighbours( numbers.back() );
    int64_t minCost = numeric_limits<int64_t>::max();
    for ( auto p : possiblePrimeDivisors )
    {
        enum State { BeforeCut, StartedCut, StartedCutFromFirstElement, FinishedCut };
        DPProcessor<int, int64_t, 4> proc;
        auto costCut = [&](int) {return a;};
        auto costAdjust = [=]( int elt )->int64_t
        {
            auto residue = elt % p;
            if ( residue == 0 )
                return 0;
            if ( residue == 1 || residue == p - 1 )
                return b;
            return numeric_limits<int64_t>::max();
        };
        proc.addRule( BeforeCut, BeforeCut, costAdjust )
            .addRule( BeforeCut, StartedCut, costCut )
            .addRule( StartedCut, StartedCut, costCut )
            .addRule( StartedCut, FinishedCut, costAdjust )
            .addRule( StartedCutFromFirstElement, StartedCutFromFirstElement, costCut )
            .addRule( StartedCutFromFirstElement, FinishedCut, costAdjust )
            .addRule( FinishedCut, FinishedCut, costAdjust );

        vector<int64_t> initialState( 4, numeric_limits<int64_t>::max() );
        initialState[BeforeCut] = costAdjust( numbers.front() );
        initialState[StartedCutFromFirstElement] = a;
        auto res = proc.process( initialState, begin(numbers) + 1, end(numbers) );
        relaxMin( minCost, res[BeforeCut] );
        relaxMin( minCost, res[StartedCut] );
        relaxMin( minCost, res[FinishedCut] );
    }
    cout << minCost;
}

class Solver623BTest : public ProblemTest {};

TEST_F(Solver623BTest, Example1)
{
    string input = R"(3 1 4
4 2 3
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver623B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver623BTest, Example2)
{
    string input = R"(5 3 2
5 17 13 5 6
)";
    string output = R"(8
)";
    output.pop_back();
    setInput(input);
    Solver623B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver623BTest, Example3)
{
    string input = R"(8 3 4
3 7 5 4 3 12 9 4
)";
    string output = R"(13
)";
    output.pop_back();
    setInput(input);
    Solver623B().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F( Solver623BTest, BigExample )
{
    int count = 1000000;
    int num = 652250190;
    stringstream ss;
    ss << count << " 10 1 ";
    for ( int i = 0; i < count; ++i )
        ss << num << " ";
    setInput( ss.str() );
    Solver623B().run();
}




