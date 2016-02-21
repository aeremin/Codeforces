#include <Solvers/pch.h>
#include "util/relax.h"

using namespace std;

class Solver552E
{
public:
    void run();

    int64_t charToDigit(char c) const
    {
        return c - '0';
    }

    int64_t calcExpressionResult(const string& expression) const
    {
        int64_t res = 0;
        int64_t currProduct = charToDigit(expression[0]);
        for (size_t pos = 1; pos < expression.length() - 1; pos += 2)
        {
            if (expression[pos] == '+')
            {
                res += currProduct;
                currProduct = charToDigit(expression[pos + 1]);
            }
            else
                currProduct *= charToDigit(expression[pos + 1]);
        }
        res += currProduct;
        return res;
    }
};

void Solver552E::run()
{
    string expression;
    cin >> expression;
    expression = "0+1*" + expression + "*1+0";
    int64_t maxValue = 0;
    vector<int> multiplyingPositions;
    for (size_t i = 1; i < expression.length() - 1; i += 2)
        if (expression[i] == '*')
            multiplyingPositions.push_back(i);

    for (size_t l = 0; l < multiplyingPositions.size(); ++l)
        for (size_t r = l + 1; r < multiplyingPositions.size(); ++r)
        {
            int64_t productOnLeft = 1;
            size_t posL;
            for (posL = multiplyingPositions[l]; expression[posL] == '*'; posL -= 2)
                productOnLeft *= charToDigit(expression[posL - 1]);

            int64_t productOnRight = 1;
            size_t posR;
            for (posR = multiplyingPositions[r]; expression[posR] == '*'; posR += 2)
                productOnRight *= charToDigit(expression[posR + 1]);

            relax_max(maxValue,
                calcExpressionResult(expression.substr(0, posL)) +
                productOnLeft * calcExpressionResult(expression.substr(multiplyingPositions[l] + 1, multiplyingPositions[r] - multiplyingPositions[l] - 1)) * productOnRight +
                calcExpressionResult(expression.substr(posR + 1, string::npos)));
        }

    cout << maxValue;
}

class Solver552ETest : public ProblemTest
{
};

TEST_F(Solver552ETest, Example1)
{
    setInput("3+5*7+8*4");
    Solver552E().run();
    EXPECT_EQ("303", getOutput());
}

TEST_F(Solver552ETest, Example2)
{
    setInput("2+3*5");
    Solver552E().run();
    EXPECT_EQ("25", getOutput());
}

TEST_F(Solver552ETest, Example3)
{
    setInput("3*4*5");
    Solver552E().run();
    EXPECT_EQ("60", getOutput());
}

TEST_F(Solver552ETest, OnlySumm)
{
    setInput("1+2+3+1+4+6+9");
    Solver552E().run();
    EXPECT_EQ("26", getOutput());
}
