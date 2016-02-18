#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "algo/range.hpp"
#include "algo/numbertheory/Coprimes.hpp"
using namespace std;

class Solver630K
{
public:
    void run();

    int64_t ans(int64_t n)
    {
        auto phi = getCoprimes(210).size();
        int64_t ans = (n / 210) * phi;
        for (auto i : range(n % 210 + 1))
            if (i % 2 != 0
                && i % 3 != 0
                && i % 5 != 0
                && i % 7 != 0)
                ans++;

        return ans;
    }
};

void Solver630K::run()
{
    cout << ans(read<int64_t>());
}

class Solver630KTest : public ProblemTest {};

TEST_F(Solver630KTest, Example1)
{
    string input = R"(12
)";
    string output = R"(2)";
    setInput(input);
    Solver630K().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver630KTest, Bruteforce)
{
    int64_t res = 0;
    for (int i : range(1, 1000))
    {
        bool div = false;
        for (int j : range(2, 11))
            div = div || (i % j == 0);

        if (!div)
            res++;
        
        ASSERT_EQ(res, Solver630K().ans(i)) << i;

    }
}


