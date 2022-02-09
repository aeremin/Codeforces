#pragma once
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

#include "algo/sort_by.h"

// Slider should have following types defined:
// Slider::InType
// Slider::OutType
//
// and provide following methods:
// void push_back(Slider::InType), void pop_front(Slider::InType), void push_front(Slider::InType)
// Slider::OutType value()
// void reset()

using Query = std::pair<size_t, size_t>;

template <class Slider>
class MoQueryProccessor {
  public:
    MoQueryProccessor(const std::vector<typename Slider::InType>& data) : data_(data) {}

    std::vector<typename Slider::OutType> processQueries(const std::vector<Query>& queries, Slider slider = {}) const {
        std::vector<typename Slider::OutType> res(queries.size());
        auto bucketedQueries = separateQueriesByBucketsAndSort_(queries);
        for (auto& bucket : bucketedQueries) {
            if (bucket.empty())
                continue;
            slider.reset();
            size_t left = bucket[0].first.first;
            size_t right = bucket[0].first.first;
            for (auto& queryWithIndex : bucket) {
                while (right < queryWithIndex.first.second)
                    slider.push_back(data_[right++]);

                while (left < queryWithIndex.first.first)
                    slider.pop_front(data_[left++]);

                while (left > queryWithIndex.first.first)
                    slider.push_front(data_[--left]);

                res[queryWithIndex.second] = slider.value();
            }
        }
        return res;
    }

    using QueryWithOriginalIndex = std::pair<Query, size_t>;
    std::vector<std::vector<QueryWithOriginalIndex>> separateQueriesByBucketsAndSort_(
        const std::vector<Query>& queries) const {
        auto bucketSize = size_t(sqrt(data_.size() + 1.1));  // Add some constant here to be sure that bucketSize > 0

        std::vector<std::vector<QueryWithOriginalIndex>> result(data_.size() / bucketSize + 1);
        for (size_t iQuery = 0; iQuery < queries.size(); ++iQuery)
            result[queries[iQuery].first / bucketSize].push_back({queries[iQuery], iQuery});

        for (auto& bucket : result)
            sortBy(bucket, [](const QueryWithOriginalIndex& q) { return q.first.second; });

        return result;
    }

  private:
    const std::vector<typename Slider::InType>& data_;
};