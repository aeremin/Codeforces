#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"
#include "algo/numbertheory/Residue.hpp"
#include "math/quick_power.h"

using namespace std;


class Solver621E
{
public:
    void run();
  
    struct Distribution
    {
    public:
        Distribution(int size) : distr(size) {}
        
        friend Distribution operator*(const Distribution& a, const Distribution& b)
        {
            int sz = a.distr.size();
            auto res = Distribution(sz);
            res.decimalPower = (a.decimalPower * b.decimalPower) % sz;
            for (int i = 0; i < sz; ++i)
                for (int j = 0; j < sz; ++j)
                    res.distr[(i * b.decimalPower + j) % sz] += a.distr[i] * b.distr[j];
            return res;
        }

        const Distribution& operator*=(const Distribution& a)
        {
            *this = (*this * a);
            return *this;
        }


        static Distribution id(int size)
        {
            Distribution res(size);
            res.distr[0] = 1;
            res.decimalPower = 1;
            return res;
        }

        vector<CodeforcesResidue64> distr;
        int decimalPower = 1;
    };
};




void Solver621E::run()
{
    int blockLen, blockCount, res, modulo;
    cin >> blockLen >> blockCount >> res >> modulo;
    auto block = readVector<int>(blockLen);

    Distribution oneBlock(modulo);
    for (auto d : block)
        oneBlock.distr[d % modulo]++;
    oneBlock.decimalPower = 10;

    auto allBlocks = quick_power(oneBlock, blockCount, Distribution::id(modulo));
    cout << allBlocks.distr[res];
}

class Solver621ETest : public ProblemTest {};

TEST_F(Solver621ETest, Example1)
{
    string input = R"(12 1 5 10
3 5 6 7 8 9 5 1 1 1 1 5
)";
    string output = R"(3
)";
    setInput(input);
    Solver621E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver621ETest, Example2)
{
    string input = R"(3 2 1 2
6 2 2
)";
    string output = R"(0
)";
    setInput(input);
    Solver621E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver621ETest, Example3)
{
    string input = R"(3 2 1 2
3 1 2
)";
    string output = R"(6
)";
    setInput(input);
    Solver621E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


