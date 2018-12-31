#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Residue.hpp"
using namespace std;

class Solver630L
{
public:
    void run();
};

void Solver630L::run()
{
    int n;
    cin >> n;
    vector<int> digits;
    while (n)
    {
        digits.push_back(n % 10);
        n /= 10;
    }

    n = 10000 * digits[4] + 1000 * digits[2] + 100 * digits[0] + 10 * digits[1] + digits[3];
    Residue<int64_t, 100000> nn = n;
    auto mm = nn * nn * nn * nn * nn;
    auto res = to_string(mm.rep());
    while (res.length() < 5) res = "0" + res;
    cout << res;
}

class Solver630LTest : public ProblemTest {};

TEST_F(Solver630LTest, Example1)
{
    string input = R"(12345
)";
    string output = R"(71232)";
    setInput(input);
    Solver630L().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


