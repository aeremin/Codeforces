#include "CodeFuser.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
#include <unordered_set>
#include <cassert>

using namespace std;

namespace
{
const char* filePrefix =
R"(#include <vector>
#include <deque>
#include <queue>
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
#include <memory>
#include <complex>
#include <regex>

using namespace std;
)";

const char* fileMainPart =
R"(
#ifdef LOCAL_PC
int main2()
#else
int main()
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


std::string CodeFuser::getSolverFileNameByProblemName_() const
{
    if (problemName_.length() == 4) // Codeforces
    {
        string problemSetName = problemName_.substr(0, 3);
        return "../Solvers/" + problemSetName.substr(0, 1) + "xx/" + problemSetName + "/Solver" + problemName_ + ".cpp";
    }
    else if (problemName_.length() == 6)
    {
        assert(problemName_.substr(0, 4) == "FBHC");
        string roundName = string("Round") + problemName_[4];
        return "../Solvers/FBHC/" + roundName + "/Solver" + problemName_ + ".cpp";
    }
    assert(false);
    return{};
}

void CodeFuser::fuse()
{
    string fusedFile = filePrefix;
   
    string problemSolverPath = getSolverFileNameByProblemName_();
    stack<ifstream> openedFiles;
    unordered_set<string> alreadyIncluded;
    
    openedFiles.emplace( problemSolverPath );
    if (!openedFiles.top().good())
        return;

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
