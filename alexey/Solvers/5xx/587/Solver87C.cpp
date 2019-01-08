#include "Solvers/pch.h"
#include "graph/graph.h"
#include "algo/graph/TreePreprocessor.hpp"

// Solution for Codeforces problem http://codeforces.com/contest/587/problem/C
class Solver587C
{
public:
    void run();

};

namespace
{
struct MyEmptyStruct
{
};

MyEmptyStruct concatenate( const MyEmptyStruct& a, const MyEmptyStruct& b )
{
    return{};
}
}

struct MinPeopleOnPath
{
    MinPeopleOnPath( const vector<int>& in = {} )
    {
        for ( int i = 0; i < min<int>( 10, in.size() ); ++i )
            people.push_back( in[i] );
    }
    vector<int> people;
};

MinPeopleOnPath concatenate( const MinPeopleOnPath& a, const MinPeopleOnPath& b )
{
    MinPeopleOnPath result;
    for ( int i = 0, j = 0; ( i < a.people.size() || j < b.people.size() ) && result.people.size() < 10; )
    {
        auto aVal = i < a.people.size() ? a.people[i] : numeric_limits<int>::max();
        auto bVal = j < b.people.size() ? b.people[j] : numeric_limits<int>::max();
        result.people.push_back( min( aVal, bVal ) );
        if ( aVal < bVal )
            ++i;
        else
            ++j;
    }
    return result;
}

void Solver587C::run()
{
    int nCities, nPeople, nQueries;
    cin >> nCities >> nPeople >> nQueries;
    vector<pair<int, int>> edges(nCities - 1);
    for ( auto& p : edges )
        cin >> p.first >> p.second;

    vector<vector<int>> peoplePerCity(nCities);

    for ( int i = 1; i <= nPeople; ++i )
    {
        int city;
        cin >> city;
        peoplePerCity[city - 1].push_back( i );
    }

    vector<MinPeopleOnPath> peoplePerCitySorted;
    for ( auto& people : peoplePerCity )
        peoplePerCitySorted.push_back( MinPeopleOnPath( people ) );

    UndirectedGraph<MyEmptyStruct, MinPeopleOnPath> tree( peoplePerCitySorted );
    for ( auto& p : edges )
        tree.add_edge( p.first - 1, p.second - 1);

    TreePreprocessor<MyEmptyStruct, MinPeopleOnPath> processor( tree );

    for ( int i = 0; i < nQueries; ++i )
    {
        int from, to, maxCount;
        cin >> from >> to >> maxCount;
        auto minimums = processor.valueOnPath( from - 1, to - 1 ).second;
        auto count = min<int>( maxCount, minimums.people.size() );
        cout << count << " ";
        for ( int i = 0; i < count; ++i )
            cout << minimums.people[i] << " ";
        cout << "\n";
    }
}

class Solver587CTest : public ProblemTest {};

TEST_F( Solver587CTest, Example1 )
{
    setInput("5 4 5       1 3       1 2      1 4      4 5      2 1 4 3          4 5 6     1 5 2     5 5 10     2 3 3     5 3 1");
    Solver587C().run();
    EXPECT_EQ("1 3 \n2 2 3 \n0 \n3 1 2 4 \n1 2 \n", getOutput());
}
