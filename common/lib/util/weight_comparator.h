#pragma once

#include <utility>

template <class WeightFunctor>
class WeightComparator {
  public:
    WeightComparator(WeightFunctor f) : f_(std::move(f)) {}

    template <typename T>
    bool operator()(const T& lh, const T& rh) {
        return f_(lh) < f_(rh);
    }

  private:
    WeightFunctor f_;
};

template <class WeightFunctor>
WeightComparator<WeightFunctor> make_weight_comparator(WeightFunctor f) {
    return WeightComparator<WeightFunctor>(std::move(f));
}
