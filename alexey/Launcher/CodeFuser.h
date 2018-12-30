#pragma once
#include <string>

std::string GetProblemNameFromGtestFilter(std::string arg);
std::string GetSolverFileNameByProblemName(std::string arg);

class CodeFuser
{
public:
    CodeFuser(std::string problemName);
    void fuse();

private:
    std::string problemName_;
};

