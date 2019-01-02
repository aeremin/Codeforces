#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/509/problem/C
class Solver509C
{
public:
    void run();

    int charToDigit(char c) { return c - '0'; }
    char digitToChar(int d) { return '0' + d; }
    
    int countSumOfDigits(const string& s)
    {
        int ans = 0;
        for (auto& c : s) ans += charToDigit(c);
        return ans;
    }

    string minBySumAndCountOfDigit(int sumOfDigits, int countOfDigits)
    {
        if (countOfDigits * 9 < sumOfDigits || sumOfDigits < 0)
            return "!";

        auto numNines = sumOfDigits / 9;
        auto remainder = sumOfDigits % 9;
        if (remainder > 0)
            return string(countOfDigits - numNines - 1, '0') + digitToChar(remainder) + string(numNines, '9');
        else
            return string(countOfDigits - numNines, '0') + string(numNines, '9');
    }
    string minWithSumOfDigitsAndBiggerThan(int sumOfDigits, const string& startFrom)
    {
        int currSumOfDigits = countSumOfDigits(startFrom);
        for (int i = 0;; ++i)
        {
            int pos = startFrom.length() - i - 1;
            const int digitOnPos = (pos >= 0) ? charToDigit(startFrom[pos]) : 0;
            currSumOfDigits -= digitOnPos;
            for (int d = digitOnPos + 1; d <= 9; ++d)
            {
                auto maybeSuffix = minBySumAndCountOfDigit(sumOfDigits - currSumOfDigits - d, i);
                if (maybeSuffix != "!")
                    if (pos >= 0)
                        return startFrom.substr(0, pos) + digitToChar(d) + maybeSuffix;
                    else
                        return digitToChar(d) + maybeSuffix;
            }
        }
        return "!";
    }
};

void Solver509C::run()
{
    int n;
    cin >> n;
    string curr = "";
    for (int i = 0; i < n; ++i)
    {
        int sumOfDigits;
        cin >> sumOfDigits;
        curr = minWithSumOfDigitsAndBiggerThan(sumOfDigits, curr);
        cout << curr << '\n';
    }
}

class Solver509CTest : public ProblemTest
{
};

TEST_F( Solver509CTest, Example1 )
{
    setInput("3        1        2        3");
    Solver509C().run();
    EXPECT_EQ("1\n2\n3\n", getOutput());
}

TEST_F( Solver509CTest, Example2 )
{
    setInput("3        3        2        1");
    Solver509C().run();
    EXPECT_EQ("3\n11\n100\n", getOutput());
}

TEST_F(Solver509CTest, Example3)
{
    setInput("5 1 1 1 1 1");
    Solver509C().run();
    EXPECT_EQ("1\n10\n100\n1000\n10000\n", getOutput());
}


TEST_F(Solver509CTest, Example4)
{
    setInput("5 2 20 19 2 1");
    Solver509C().run();
    EXPECT_EQ("2\n299\n379\n1001\n10000\n", getOutput());
}

