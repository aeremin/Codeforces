#include <Solvers/pch.h>
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/468/problem/B
class Solver468B
{
public:
    void run();
};

void Solver468B::run()
{
    unordered_map<int, int> nums;
    vector<int> result;
    vector<bool> used;
    vector<pair<int, int>> edges;

    int n, a, b;
    cin >> n >> a >> b;
    for ( int i = 0; i < n; ++i )
    {
        int p;
        cin >> p;
        nums.emplace( p, i );
        used.push_back( false );
        result.push_back( 0 );
    }

    edges.resize( n );

    for ( auto x : nums )
    {
        int ax = a - x.first;
        int bx = b - x.first;
        if ( nums.find( ax ) != end( nums ) )
            edges[x.second].first = nums[ax];
        else
            edges[x.second].first = -1;

        if ( nums.find( bx ) != end( nums ) )
            edges[x.second].second = nums[bx];
        else
            edges[x.second].second = -1;
    }

    bool res = true;
    for ( auto x : nums )
    {
        if ( used[x.second] ) continue;
        if ( min( edges[x.second].first, edges[x.second].second ) >= 0 ) continue;

        used[x.second] = true;
        int cur = x.second;
        int len = 0;
        bool isFirst = edges[x.second].first >= 0;
        int to = isFirst ? 0 : 1;
        do
        {
            ++len;
            result[cur] = to;
            used[cur] = true;
            cur = ( isFirst ? edges[cur].first : edges[cur].second );
            isFirst = !isFirst;
        } while ( cur != -1 );
        if ( len % 2 == 1 )
        {
            res = false;
            break;
        }
    }

    if ( !res )
    {
        cout << "NO";
        return;
    }

    cout << "YES" << endl;
    for ( int elt : result )
        cout << elt << ' ';
}

class Solver468BTest : public ProblemTest
{
};

TEST_F( Solver468BTest, Example1 )
{
    setInput("4 5 9              2 3 4 5");
    Solver468B().run();
    EXPECT_EQ("YES\n0 0 1 1 ", getOutput());
}

TEST_F( Solver468BTest, Example2 )
{
    setInput("3 3 4              1 2 4");
    Solver468B().run();
    EXPECT_EQ("NO", getOutput());
}