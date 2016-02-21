#include <gtest/gtest.h>
#include "algo/query/MoQueryProcessor.hpp"
#include <numeric>
#include "algo/query/OrderIndependentSlider.hpp"

class SumCalculator
{
public:
    using OutType = int;
    using InType = int;
    
    void insert(int a) { sum_ += a; }
    void erase(int a) { sum_ -= a; }

    int value() const { return sum_; }

    void reset() { sum_ = 0; }

private:
    int sum_ = 0;
};

TEST(MoQueryProccessorTest, WorksOnRandomData)
{
    const size_t dataSize = 10000;
    std::vector<int> data(dataSize);
    for (auto& d : data)
        d = rand() % 1000;

    const size_t nQueries = 10000;
    std::vector<Query> queries(nQueries);
    for (auto& q : queries)
    {
        size_t l = rand() % dataSize;
        size_t r = rand() % dataSize;
        q = std::minmax(l, r);
    }
    
    // add some special cases manually
    queries.push_back({ 0, dataSize });
    queries.push_back({ 1, 1 });

    auto queriesResults = MoQueryProccessor<OrderIndependentSlider<SumCalculator>>(data).processQueries(queries);
    for (size_t i = 0; i < queries.size(); ++i)
    {
        int expectedSum = std::accumulate(begin(data) + queries[i].first, begin(data) + queries[i].second, 0);
        EXPECT_EQ(expectedSum, queriesResults[i]);
    }
}