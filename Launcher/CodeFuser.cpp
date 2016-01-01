#include "CodeFuser.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
#include <unordered_set>

using namespace std;

namespace
{
const char* filePrefix =
R"(#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>
#include <functional>
#include <array>
#include <valarray>
#include <iomanip>
#include <cassert>

using namespace std;
)";

const char* fileMainPart =
R"(
#ifdef ONLINE_JUDGE
int main()
#else
int main2()
#endif
{
    ios::sync_with_stdio( false );
    CurrentSolver().run();
	return 0;
}
)";
}

CodeFuser::CodeFuser(std::string problemName) : problemName_(move(problemName))
{}

void CodeFuser::fuse()
{
    string fusedFile = filePrefix;
    
    string problemSetName = problemName_.substr( 0, 3 );
    string problemSolverPath = "../Solvers/" + problemSetName.substr(0, 1) + "xx/" + problemSetName + "/Solver" + problemName_ + ".cpp";
    stack<ifstream> openedFiles;
    unordered_set<string> alreadyIncluded;
    
    openedFiles.emplace( problemSolverPath );
    
    fusedFile.append( "namespace mainns\n{\n" );

    while ( !openedFiles.empty() )
    {
        bool shouldPop = true;
        auto& currFile = openedFiles.top();
        while ( !currFile.eof() )
        {
            string line;
            getline( currFile, line );

            if ( line.find( "#include \"algo" ) != string::npos )
            {
                auto fromPos = line.find_first_of( '\"' );
                auto toPos = line.find_last_of( '\"' );
                auto includedFilename = line.substr( fromPos + 1, toPos - fromPos - 1 );
                auto shouldInclude = alreadyIncluded.insert( includedFilename ).second;
                if ( shouldInclude )
                {
                    auto fullIncludePath = "../" + includedFilename;
                    openedFiles.emplace( fullIncludePath );
                    shouldPop = false;
                    break;
                }
            }

            if ( line.find( "#include" ) != string::npos )
                continue;

            if ( line.find( "#pragma once" ) != string::npos )
                continue;

            if ( line.find( "using namespace std;" ) != string::npos )
                continue;

            if ( line.find( "ProblemTest" ) != string::npos )
                break;

            fusedFile.append( line );
            fusedFile.append( "\n" );
        }
        if (shouldPop)
            openedFiles.pop();
    }

    fusedFile.append( "} //namespace mainns\n" );
    fusedFile.append( "using CurrentSolver = mainns::Solver" + problemName_ + ";" );
    fusedFile.append( fileMainPart );

    ofstream out( "testifcompiles.cpp" );
    out << fusedFile;
}
