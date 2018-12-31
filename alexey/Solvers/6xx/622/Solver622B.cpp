#include <Solvers/pch.h>

using namespace std;

class Solver622B
{
public:
    void run();

    int toInt(char a, char b)
    {
        return 10 * (a - '0') + b - '0';
    }

    string toStr(int a)
    {
        string res = to_string(a);
        while (res.length() != 2)
            res = '0' + res;
        return res;
    }
};

void Solver622B::run()
{
    string currTime;
    cin >> currTime;
    int diff;
    cin >> diff;
    int m = toInt(currTime[3], currTime[4]);
    int h = toInt(currTime[0], currTime[1]);
    m += diff;
    h += m / 60;
    m = m % 60;
    h = h % 24;
    cout << toStr(h) << ":" << toStr(m);
 }

class Solver622BTest : public ProblemTest {};

TEST_F(Solver622BTest, Example1)
{
    string input = R"(23:59
10
)";
    string output = R"(00:09
)";
    setInput(input);
    Solver622B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622BTest, Example2)
{
    string input = R"(20:20
121
)";
    string output = R"(22:21
)";
    setInput(input);
    Solver622B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622BTest, Example3)
{
    string input = R"(10:10
0
)";
    string output = R"(10:10
)";
    setInput(input);
    Solver622B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


