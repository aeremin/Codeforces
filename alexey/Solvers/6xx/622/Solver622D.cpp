#include <Solvers/pch.h>

using namespace std;

class Solver622D
{
public:
    void run();
};

void Solver622D::run()
{
    int n;
    cin >> n;
    deque<int> odd, even;
    for (int i = n - 1; i > 0; i -= 2)
    {
        odd.push_back(i);
        odd.push_front(i);
    }

    even.push_back(n);
    for (int i = n - 2; i > 0; i -= 2)
    {
        even.push_back(i);
        even.push_front(i);
    }
    even.push_back(n);

    for (auto elt : odd)
        cout << elt << " ";

    for (auto elt : even)
        cout << elt << " ";
}

class Solver622DTest : public ProblemTest {};

TEST_F(Solver622DTest, Example1)
{
    string input = R"(2
)";
    string output = R"(1 1 2 2 
)";
    setInput(input);
    Solver622D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver622DTest, Example2)
{
    string input = R"(1
)";
    string output = R"(1 1 
)";
    setInput(input);
    Solver622D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


