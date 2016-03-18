#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/io/printvector.h"
using namespace std;

class Solver644C {
public:
    void run();

    pair<string, string> decompose( const string& url ) const {
        auto pathStart = url.find( '/', 7 );
        return{ url.substr( 0, pathStart ), 
                pathStart == string::npos ? "" : url.substr( pathStart, string::npos ) };
    }
};

void Solver644C::run() {
    int n = read<int>();
    auto urls = readVector<string>( n );
    unordered_map<string, vector<string>> perSitePaths;
    for ( auto& url : urls ) {
        auto decomposed = decompose( url );
        perSitePaths[decomposed.first].push_back( decomposed.second );
    }

    unordered_map<string, vector<string>> perPathSites;

    for ( auto& paths : perSitePaths ) {
        sort( begin( paths.second ), end( paths.second ) );
        paths.second.erase( unique( begin( paths.second ), end( paths.second ) ), end( paths.second ) );
        string concatenatedPaths;
        for ( auto& p : paths.second )
            concatenatedPaths.append( p + "$" );
        perPathSites[concatenatedPaths].push_back( paths.first );
    }

    int nNotUniqueSites = 0;
    for ( auto& p : perPathSites )
        if ( p.second.size() > 1 )
            ++nNotUniqueSites;

    print( nNotUniqueSites );
    print( '\n' );
    for ( auto& p : perPathSites )
        if ( p.second.size() > 1 ) {
			sort(begin(p.second), end(p.second));
			printVector( p.second );
            print( '\n' );
        }
}

class Solver644CTest : public ProblemTest {};

TEST_F( Solver644CTest, Example1 ) {
    string input = R"(10
http://abacaba.ru/test
http://abacaba.ru/
http://abacaba.com
http://abacaba.com/test
http://abacaba.de/
http://abacaba.ru/test
http://abacaba.de/test
http://abacaba.com/
http://abacaba.com/t
http://abacaba.com/test
)";
    string output = R"(1
http://abacaba.de http://abacaba.ru
)";
    setInput( input );
    Solver644C().run();
    EXPECT_EQ( output, getOutput() );
}


TEST_F( Solver644CTest, Example2 ) {
    string input = R"(14
http://c
http://ccc.bbbb/aba..b
http://cba.com
http://a.c/aba..b/a
http://abc/
http://a.c/
http://ccc.bbbb
http://ab.ac.bc.aa/
http://a.a.a/
http://ccc.bbbb/
http://cba.com/
http://cba.com/aba..b
http://a.a.a/aba..b/a
http://abc/aba..b/a
)";
    string output = R"(2
http://cba.com http://ccc.bbbb
http://a.a.a http://a.c http://abc
)";
    setInput( input );
    Solver644C().run();
    EXPECT_EQ( output, getOutput() );
}


