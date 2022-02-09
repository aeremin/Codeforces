#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "algo/disjoint_set.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/659/problem/F
class Solver659F
{
public:
    void run();

    int h, w;
    int64_t sum;
    vector<int> field;

    int ind( int x, int y ) const {
        return x + y * w;
    }

    bool isValid( int x, int y ) const {
        return x >= 0 && x < w && y >= 0 && y < h;
    }
};

void Solver659F::run()
{
    cin >> h >> w >> sum;
    field = readVector<int>( h * w );
    map<int, vector<pair<int, int>>> perValue;
    int maxV = 0;
    for ( int x : range(w) )
        for ( int y : range( h ) ) {
            perValue[field[ind( x, y )]].push_back( { x, y } );
        }

    pair<int, int> offs[4] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    DisjointSet ds( h * w );
    for ( auto it = perValue.rbegin(); it != perValue.rend(); ++it ) {
        auto currH = it->first;
        const auto& currList = it->second;
		auto neededCount = sum / currH;
        for ( auto inds : currList ) {
            auto currInd = ind( inds.first, inds.second );
            for ( auto off : offs ) {
                int x = inds.first + off.first;
                int y = inds.second + off.second;
                if ( isValid( x, y ) ) {
                    auto neiind = ind( x, y );
                    if ( field[neiind] >= currH )
                        ds.unionSets( currInd, neiind );
                }
            }
        }

        if ( sum % currH != 0 ) continue;

        for ( auto inds : currList ) {
            auto currInd = ind( inds.first, inds.second );
            auto compSize = ds.componentSize( currInd );
            if ( compSize >= neededCount ) {
                vector<int> ans( h * w );
                vector<pair<int, int>> q;
                q.push_back( { inds.first, inds.second } );
                while ( neededCount ) {
                    auto nextElt = q.back();
                    q.pop_back();
                    
                    if ( ans[ind( nextElt.first, nextElt.second )] > 0 ) continue;

                    --neededCount;
                    ans[ind( nextElt.first, nextElt.second )] = currH;

                    for ( auto off : offs ) {
                        int x = nextElt.first + off.first;
                        int y = nextElt.second + off.second;
                        if ( isValid( x, y ) ) {
                            auto neiind = ind( x, y );
                            if ( field[neiind] >= currH )
                                q.push_back( { x, y } );
                        }
                    }
                }

                cout << "YES\n";
                for ( int y : range( h ) ) {
                    for ( int x : range( w ) )
                        cout << ans[ind( x, y )] << " ";
                    cout << "\n";
                }
                return;
            }

        }
    }
    cout << "NO\n";
}

class Solver659FTest : public ProblemTest {};

TEST_F(Solver659FTest, Example1)
{
    string input = R"(2 3 35
10 4 9
9 9 7
)";
    string output = R"(YES
7 0 7 
7 7 7 
)";
    setInput(input);
    Solver659F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659FTest, Example2)
{
    string input = R"(4 4 50
5 9 1 1 
5 1 1 5 
5 1 5 5 
5 5 7 1 
)";
    string output = R"(YES
5 5 0 0 
5 0 0 5 
5 0 5 5 
5 5 5 0 
)";
    setInput(input);
    Solver659F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver659FTest, Example3)
{
    string input = R"(2 4 12
1 1 3 1
1 6 2 4
)";
    string output = R"(NO
)";
    setInput(input);
    Solver659F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


