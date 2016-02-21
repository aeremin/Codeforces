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

/////////////////////////////////////////////////////////

FBHCProblemTest::FBHCProblemTest(std::string filename)
    : filename_(filename),
      in_(filename + "in.txt"),
      out_(filename + "out.txt")
{
    defaultOutBuf_ = std::cout.rdbuf();
    defaultInBuf_ = std::cin.rdbuf();

    std::cin.rdbuf(in_.rdbuf());
    std::cout.rdbuf(out_.rdbuf());
}

FBHCProblemTest::~FBHCProblemTest()
{
    std::cout.rdbuf(defaultOutBuf_);
    std::cin.rdbuf(defaultInBuf_);
    in_.close();
    out_.close();

    std::ifstream expectedOut(filename_ + "out_expected.txt");
    std::ifstream realOut(filename_ + "out.txt");

    std::string strExpected((std::istreambuf_iterator<char>(expectedOut)),
                             std::istreambuf_iterator<char>());

    std::string strReal((std::istreambuf_iterator<char>(realOut)),
                         std::istreambuf_iterator<char>());

    EXPECT_EQ(strExpected, strReal);
}
