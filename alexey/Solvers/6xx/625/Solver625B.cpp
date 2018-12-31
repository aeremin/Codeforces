#include <Solvers/pch.h>

using namespace std;

class Solver625B
{
public:
    void run();
};

void Solver625B::run()
{
    string name, pattern;
    cin >> name >> pattern;
    vector<int> patternStarts;
    int lengthDiff = name.length() - pattern.length();
    if (lengthDiff < 0)
    {
        cout << 0;
        return;
    }
    for (int i = 0; i < lengthDiff + 1; ++i)
        if (name.substr(i, pattern.length()) == pattern)
            patternStarts.push_back(i);

    int ans = 0;
    int lastPinned = -100;
    for (auto s : patternStarts)
    {
        if (s > lastPinned)
        {
            ++ans;
            lastPinned = s + pattern.length() - 1;
        }
    }

    cout << ans;
}

class Solver625BTest : public ProblemTest {};

TEST_F(Solver625BTest, Example1)
{
    string input = R"(intellect
tell
)";
    string output = R"(1)";
    setInput(input);
    Solver625B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625BTest, Example2)
{
    string input = R"(google
apple
)";
    string output = R"(0)";
    setInput(input);
    Solver625B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver625BTest, Example3)
{
    string input = R"(sirisiri
sir
)";
    string output = R"(2)";
    setInput(input);
    Solver625B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625BTest, Example4)
{
    string input = R"(aaaaaaa
a
)";
    string output = R"(7)";
    setInput(input);
    Solver625B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625BTest, Example5)
{
    string input = R"(aaaaaaa
aa
)";
    string output = R"(3)";
    setInput(input);
    Solver625B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver625BTest, Example6)
{
    string input = R"(aaa
aaaa
)";
    string output = R"(0)";
    setInput(input);
    Solver625B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}