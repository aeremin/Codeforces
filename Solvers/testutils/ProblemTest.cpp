#include "Solvers/pch.h"
#include "ProblemTest.h"

ProblemTest::ProblemTest()
{
    defaultOutBuf = std::cout.rdbuf();
    std::cout.rdbuf(ssOut.rdbuf());
    
    defaultInBuf = std::cin.rdbuf();
    std::cin.rdbuf(ssIn.rdbuf());
}


ProblemTest::~ProblemTest()
{
    std::cout.rdbuf(defaultOutBuf);
    std::cin.rdbuf(defaultInBuf);
}


void ProblemTest::setInput(const std::string& in)
{
    ssIn << in;
}

std::string ProblemTest::getOutput()
{
    return ssOut.str();
}