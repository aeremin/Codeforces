#include "CodeFuser.h"
#include <cassert>
#include <string>
#include <fstream>

#include "tools/fuser/fuser.h"

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
#include <list>
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
int main()
{
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
        return "Solvers/" + problemSetName.substr(0, 1) + "xx/" + problemSetName + "/Solver" + problemName_ + ".cpp";
    }
    else if (problemName_.length() == 6)
    {
        assert(problemName_.substr(0, 4) == "FBHC");
        string roundName = string("Round") + problemName_[4];
        return "Solvers/FBHC/" + roundName + "/Solver" + problemName_ + ".cpp";
    }
    assert(false);
    return{};
}

void CodeFuser::fuse()
{
    ofstream out( "Fused/main.cpp" );
    out << filePrefix;
   
    string problemSolverPath = getSolverFileNameByProblemName_();

    CompilerOptions options;
    options.include_paths = {".", "../common/lib"};
    auto fused = Compile(problemSolverPath, options);
    string pchToDelete = "#include <Solvers/pch.h>";
    fused.erase(fused.find(pchToDelete), pchToDelete.length());
    out << fused;
}
