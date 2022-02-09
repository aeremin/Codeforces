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
