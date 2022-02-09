#include "CodeFuser.h"
#include <cassert>
#include <string>
#include <fstream>
#include <regex>

#include "tools/fuser/fuser.h"

using namespace std;

namespace
{
const char* filePrefix =
R"(#include <vector>
#include <deque>
#include <queue>
#include <stack>
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
#include <optional>

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

std::string GetProblemNameFromGtestFilter(std::string arg)
{
    std::regex normalRegex(R"(--gtest_filter=\*([1-9][0-9][0-9]+[A-Z])\*)");
    std::smatch piecesMatch;
    if (std::regex_match(arg, piecesMatch, normalRegex)) {
        return piecesMatch[1].str();
    }

    return "";
}

std::string GetSolverFileNameByProblemName(std::string problemName) {
    string problemSetName = problemName.substr(0, problemName.length() - 1);
    string problemSetPrefix = problemSetName.substr(0, problemSetName.length() - 2);
    return "Solvers/" + problemSetPrefix + "xx/" + problemSetName + "/Solver" + problemName + ".cpp";
}

CodeFuser::CodeFuser(std::string problemName) : problemName_(move(problemName))
{}


void CodeFuser::fuse()
{
    ofstream out( "Fused/main.cpp" );
    out << filePrefix;
   
    string problemSolverPath = GetSolverFileNameByProblemName(problemName_);

    CompilerOptions options;
    options.include_paths = {".", "../common/lib"};
    auto fused = Compile(problemSolverPath, options);
    string pchToDelete = "#include <Solvers/pch.h>";
    fused.erase(fused.find(pchToDelete), pchToDelete.length());
    out << fused;
}
