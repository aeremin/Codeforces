#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"

using namespace std;

class Solver621A
{
public:
    void run();
};

void Solver621A::run()
{
    int n;
    cin >> n;
    auto nums = readVector<int64_t>(n);
    auto nOdd = count_if(begin(nums), end(nums), [](int64_t a) { return a % 2 == 1; });
    auto sum = accumulate(begin(nums), end(nums), int64_t(0));
    if (nOdd % 2 == 1)
    {
        vector<int64_t> odd;
        copy_if(begin(nums), end(nums), back_inserter(odd), [](int64_t a) { return a % 2 == 1; });
        sum -= *min_element(begin(odd), end(odd));
    }
    cout << sum;
}

class Solver621ATest : public ProblemTest {};

TEST_F(Solver621ATest, Example1)
{
    string input = R"(3
1 2 3
)";
    string output = R"(6)";
    output.pop_back();
    setInput(input);
    Solver621A().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver621ATest, Example2)
{
    string input = R"(5
999999999 999999999 999999999 999999999 999999999
)";
    string output = R"(3999999996)";
    output.pop_back();
    setInput(input);
    Solver621A().run();
    EXPECT_EQ(output, getOutput());
}


