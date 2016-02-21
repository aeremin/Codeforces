#pragma once
#include <string>

class CodeFuser
{
public:
    CodeFuser(std::string problemName);
    void fuse();

private:
    std::string getSolverFileNameByProblemName_() const;
    std::string problemName_;
};

