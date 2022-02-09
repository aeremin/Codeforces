#include <Solvers/pch.h>
#include "algo/indicator.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/625/problem/D
class Solver625D
{
public:
    void run();

    string run(string in);
    
    bool decrease(deque<int>& num)
    {
        for (int i = num.size() - 1; i >= 0; --i)
        {
            if (num[i] > 0)
            {
                num[i]--;
                for (int j = i + 1; j < num.size(); ++j)
                    num[j] = 9;
                return true;
            }
        }
        return false;
    }
    
    deque<int> decompose(deque<int> sum)
    {
        int d1 = sum.front();
        sum.pop_front();

        if (sum.empty())
        {
            if (d1 % 2 == 1)
                return{};
            return{ d1 / 2 };
        }

        int d2 = sum.back();
        sum.pop_back();

        if (sum.empty())
        {
            if (d1 == d2)
                return{ d1, 0 };
            if (d1 == d2 + 11 && d2 < 9)
                return{ 9, d2 + 1 };

            return{};
        }

        bool shouldTry = false;
        int addFront = -1;
        int addBack = -1;

        if (d1 == d2)
        {
            shouldTry = true;
            addFront = d2;
            addBack = 0;
        }
        if (d1 == d2 + 10 && d2 < 9)
        {
            shouldTry = decrease(sum);
            addFront = 9;
            addBack = d2 + 1;
        }
        if (d1 == d2 + 1)
        {
            sum.front() += 10;
            shouldTry = true;
            addFront = d2;
            addBack = 0;
        }
        if (d1 == d2 + 11)
        {
            sum.front() += 10;
            shouldTry = decrease(sum);
            addFront = 9;
            addBack = d2 + 1;
        }

        if (!shouldTry)
            return{};

        auto subres = decompose(move(sum));
        if (subres.empty())
            return{};
        subres.push_front(addFront);
        subres.push_back(addBack);
        return subres;
    }
};

void Solver625D::run()
{
    string s;
    cin >> s;
    cout << run(s);
}


string Solver625D::run(string in)
{
    if (in == "1")
        return "0";

    deque<int> d;
    for (auto c : in)
        d.push_back(c - '0');

    auto res = decompose(d);
    if ((res.empty() || res.front() == 0) && d.front() == 1)
    {
        d.pop_front();
        d.front() += 10;
        res = decompose(d);
    }

    if (res.empty() || res.front() == 0)
        return "0";
    else
    {
        string out;
        for (auto c : res) 
            out.push_back(c + '0');
        return out;
    }
}

class Solver625DTest : public ProblemTest {};

TEST_F(Solver625DTest, Example1)
{
    string input = R"(4)";
    string output = R"(2)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625DTest, Example2)
{
    string input = R"(11)";
    string output = R"(10)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625DTest, Example3)
{
    string input = R"(5)";
    string output = R"(0)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625DTest, Example4)
{
    string input = R"(33)";
    string output = R"(30)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625DTest, Example5)
{
    string input = R"(4213)";
    string output = R"(3920)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625DTest, Example6)
{
    string input = R"(1)";
    string output = R"(0)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625DTest, Example7)
{
    string input = R"(1009)";
    string output = R"(950)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625DTest, Example8)
{
    string input = R"(11000)";
    string output = R"(9901)";
    setInput(input);
    Solver625D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

namespace
{
int strToInt(const string& s)
{
    stringstream ss;
    ss << s;
    int res;
    ss >> res;
    return res;
}


int reverse(int a)
{
    auto aString = to_string(a);
    reverse(begin(aString), end(aString));
    return strToInt(aString);
}
}

TEST_F(Solver625DTest, AnswerIsValidIfGiven)
{
    for (int i = 1; i < 1000000; ++i)
    {
        auto res = Solver625D().run(to_string(i));
        for (auto c : res)
        {
            EXPECT_GE(c, '0');
            EXPECT_LE(c, '9');
        }
        if (res != "0")
        {
            EXPECT_GT(res[0], '0');
            auto a = strToInt(res);
            auto b = reverse(a);
            ASSERT_EQ(i, a + b) << i << " " << a << " " << b;
        }
    }
}

TEST_F(Solver625DTest, GivesAnswerIfExists)
{
    for (int a = 1; a < 1000000; ++a)
    {
        auto b = reverse(a);
        auto res = Solver625D().run(to_string(a + b));
        ASSERT_NE("0", res) << a << " " << b;
    }
}
