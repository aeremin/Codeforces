#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/659/problem/B
class Solver659B
{
public:
    void run();
};

void Solver659B::run()
{
    int nStudents, nRegions;
    cin >> nStudents >> nRegions;
    vector<vector<pair<int, string>>> results( nRegions );
    for ( int i : range( nStudents ) ) {
        string name;
        int region;
        int score;
        cin >> name >> region >> score;
        results[region - 1].push_back( { -score, name } );
    }

    for ( auto& resPerReg : results ) {
        sort( begin( resPerReg ), end( resPerReg ) );
        bool isGood = true;
        if ( resPerReg.size() > 2 ) {
            auto score2 = resPerReg[1].first;
            auto score3 = resPerReg[2].first;
            if ( score3 == score2 ) isGood = false;
        }

        if ( isGood )
            cout << resPerReg[0].second << " " << resPerReg[1].second << "\n";
        else
            cout << "?\n";
    }
}

class Solver659BTest : public ProblemTest {};

TEST_F(Solver659BTest, Example1)
{
    string input = R"(5 2
Ivanov 1 763
Andreev 2 800
Petrov 1 595
Sidorov 1 790
Semenov 2 503
)";
    string output = R"(Sidorov Ivanov
Andreev Semenov
)";
    setInput(input);
    Solver659B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659BTest, Example2)
{
    string input = R"(5 2
Ivanov 1 800
Andreev 2 763
Petrov 1 800
Sidorov 1 800
Semenov 2 503
)";
    string output = R"(?
Andreev Semenov
)";
    setInput(input);
    Solver659B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


