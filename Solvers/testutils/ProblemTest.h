#pragma once

class ProblemTest : public testing::Test
{
protected:
    ProblemTest();
    ~ProblemTest();

    void setInput(const std::string& in);
    std::string getOutput();

private:
    std::streambuf* defaultOutBuf = nullptr;
    std::stringstream ssOut;

    std::streambuf* defaultInBuf = nullptr;
    std::stringstream ssIn;
};

class FBHCProblemTest : public testing::Test
{
protected:
    FBHCProblemTest(std::string filename);
    ~FBHCProblemTest();

private:
    std::string filename_;

    std::ifstream in_;
    std::ofstream out_;

    std::streambuf* defaultOutBuf_ = nullptr;
    std::streambuf* defaultInBuf_ = nullptr;
};

