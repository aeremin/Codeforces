#include <Solvers/pch.h>
#include "algo/query/MoQueryProcessor.hpp"
#include "algo/query/OrderIndependentSlider.hpp"
#include "algo/io/printvector.h"
#include "algo/io/readvector.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/617/problem/E
class Solver617E
{
public:
    void run();

    class GoodPairsCalculator
    {
    public:
        using InType = uint32_t;
        using OutType = int64_t;
        
        GoodPairsCalculator(uint32_t goodXOR) : goodXOR_(goodXOR), count_(1 << 20) {}

        void insert(uint32_t a)
        {
            value_ += count_[a ^ goodXOR_];
            ++count_[a];
        }

        void erase(uint32_t a)
        {
            --count_[a];
            value_ -= count_[a ^ goodXOR_];
        }

        int64_t value() const { return value_; }
        void reset() { fill(begin(count_), end(count_), 0); value_ = 0; }

    private:
        const uint32_t goodXOR_;
        vector<int> count_;
        int64_t value_ = 0;
    };
};

void Solver617E::run()
{
    size_t dataSize, nQueries, favXOR;
    cin >> dataSize >> nQueries >> favXOR;
    auto data = readVector<uint32_t>(dataSize);

    vector<uint32_t> prefixXOR = { 0 };
    partial_sum(begin(data), end(data), back_inserter(prefixXOR), bit_xor<uint32_t>());

    vector<Query> queries(nQueries);
    for (auto& q : queries)
    {
        cin >> q.first >> q.second;
        q.first--;
        q.second++;
    }

    auto res = MoQueryProccessor<OrderIndependentSlider<GoodPairsCalculator>>(prefixXOR).
        processQueries(queries, OrderIndependentSlider<GoodPairsCalculator>(GoodPairsCalculator(favXOR)));

    printVector(res, "\n");
}

class Solver617ETest : public ProblemTest
{
};

TEST_F( Solver617ETest, Example1 )
{
    setInput("5 3 1             1 1 1 1 1             1 5             2 4             1 3");
    Solver617E().run();
    EXPECT_EQ("9\n4\n4", getOutput());
}

TEST_F( Solver617ETest, Example2 )
{
    setInput("6 2 3             1 2 1 1 0 3             1 6             3 5");
    Solver617E().run();
    EXPECT_EQ("7\n0", getOutput());
}

TEST_F(Solver617ETest, Example3)
{
    setInput("6 1 0             1 2 1 1 0 3             1 3             3 5");
    Solver617E().run();
    EXPECT_EQ("0", getOutput());
}

TEST_F(Solver617ETest, RandomMaxTest)
{
    srand(6);
    int n = 100000;
    stringstream ss;
    ss << n << " " << n << " " << 123321 << " ";
    for (int i = 0; i < n; ++i)
        ss << (rand() % 1000000) << " ";
    
    for (int i = 0; i < n; ++i)
    {
        int l, r;
        tie(l, r) = minmax((rand() % (n / 10)) + 1, n);
        ss << l << " " << r << " ";
    }

    setInput(ss.str());
    Solver617E().run();
}
